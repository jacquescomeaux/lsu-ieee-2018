#include <cstdlib>
#include <iostream>
#include <libusb-1.0/libusb.h>
#include <chrono>
#include <thread>

static const int VID = 0x2341;
static const int PID = 0x0042;

static const uint16_t ACM_CTRL_DTR = 0x01;
static const uint16_t ACM_CTRL_RTS = 0x02;

static const uint8_t ACM_SET_CONTROL_LINE_STATE = 0x22;
static const uint8_t ACM_SET_LINE_CODING = 0x20;

static libusb_device_handle* dev_handle;

static const int endpoint_in = 0x03;
static const int endpoint_out = 0x04;

union int_thing {
  unsigned char usb_data[4];
  uint32_t number;
};

void error(std::string s, int err) {
  std::cout << err << s << " Error: " << libusb_error_name(err) << std::endl;
  exit(err);
}

void writeChar(unsigned char c) {
  int transferred, err;
  err = libusb_bulk_transfer(dev_handle, LIBUSB_ENDPOINT_OUT | endpoint_out, &c, 1, &transferred, 0);
  if(err < 0) error("writeChar error", err);
}

int readChars(unsigned char* buf, int size) {
  int transferred, err;
  err = libusb_bulk_transfer(dev_handle, LIBUSB_ENDPOINT_IN | endpoint_in, buf, size, &transferred, 1000);
  if(err < 0) error("readChars error", err);
  return transferred;
}

int main() {
  
  int err;
  
  err = libusb_init(NULL);
  if(err < 0) error("init", err);
  
  libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_DEBUG);

  dev_handle = libusb_open_device_with_vid_pid(NULL, VID, PID);
  if(dev_handle == NULL) error("handle", 0);
 
  libusb_set_auto_detach_kernel_driver(dev_handle, 1);
  
  for(int i = 0; i < 2; i++) {
    err = libusb_claim_interface(dev_handle, i);
    if(err) error("claim", err);
  }
  
  uint8_t request_type = 0x21;//LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR | LIBUSB_RECIPIENT_INTERFACE;
  err = libusb_control_transfer(dev_handle, request_type, ACM_SET_CONTROL_LINE_STATE, ACM_CTRL_DTR | ACM_CTRL_RTS, 0, NULL, 0, 1000);
  if(err < 0) error("set line state", err);
  
  unsigned char encoding[] = {0x80, 0x25, 0x00, 0x00, 0x00, 0x00, 0x08};
  err = libusb_control_transfer(dev_handle, request_type, ACM_SET_LINE_CODING, 0, 0, encoding, sizeof(encoding), 1000);
  if(err < 0) error("set line coding", err);

  union int_thing number;
 
  std::cout << "enter number: ";
  std::cin >> number.number;
  while(number.number != 0) {

    int bytes_sent, bytes_received;
    
    err = libusb_bulk_transfer(dev_handle, LIBUSB_ENDPOINT_OUT | endpoint_out, number.usb_data, sizeof(union int_thing), &bytes_sent, 1000);
    if(err < 0) error("transmit", err);

    std::cout << bytes_sent << " bytes sent" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(400));

    number.number = 0;
    //number.usb_data[1] = 0x00;
    //number.usb_data[2] = 0x00;
    //number.usb_data[3] = 0x00;
    
    bytes_received = 0;
    //err = libusb_bulk_transfer(dev_handle, LIBUSB_ENDPOINT_IN | endpoint_in, number.usb_data, 1, &bytes_received, 1000);
    //if(err < 0) error("receive", err);
    while(bytes_received != 4) {
      bytes_received += readChars(number.usb_data, sizeof(union int_thing));
      //libusb_clear_halt(dev_handle, LIBUSB_ENDPOINT_IN | endpoint_in);
    }
    std::cout << bytes_received << " bytes received" << std::endl;

    std::cout << "result: " << number.number << std::endl << "enter number: ";
    std::cin >> number.number;
  } 
  
  err = libusb_release_interface(dev_handle, 1);
  if(err < 0) error("release", err);
  
  err = libusb_release_interface(dev_handle, 0);
  if(err < 0) error("release", err);
  //libusb_attach_kernel_driver(handy, 0);
    
  libusb_close(dev_handle); 
    
  libusb_exit(NULL);
  
  return 0;
}
