#include <cstdlib>
#include <iostream>
#include <libusb-1.0/libusb.h>

union int_thing {
  unsigned char usb_data[4];
  uint32_t number;
};

void error(std::string s, int err) {
  std::cout << s << " Error: " << libusb_error_name(err) << std::endl;
  exit(err);
}

int main() {
  
  libusb_init(NULL);
  
  libusb_device_handle* handy = libusb_open_device_with_vid_pid(NULL, 0x2341, 0x0042);
  
  if(handy == NULL) {
    std::cout << "wowowowowow" << std::endl;
    libusb_exit(NULL);
    return -1;
  }
 
  libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_DEBUG);

  libusb_set_auto_detach_kernel_driver(handy, 1);
  
  int err;
  
  err = libusb_claim_interface(handy, 1);
  if(err) error("claim", err);
  
  err = libusb_set_interface_alt_setting(handy, 1, 0);
  if(err) error("set alt setting", err);
  
  union int_thing number;
 
  std::cout << "enter number: ";
  std::cin >> number.number;
  while(number.number != 0) {

    int bytes_sent, bytes_received;
    
    err = libusb_bulk_transfer(handy, LIBUSB_ENDPOINT_OUT | 0x04, number.usb_data, sizeof(union int_thing), &bytes_sent, 1000);
    if(err) error("transmit", err);

    std::cout << bytes_sent << " bytes sent" << std::endl;

    err = libusb_bulk_transfer(handy, LIBUSB_ENDPOINT_IN | 0x03, number.usb_data, sizeof(union int_thing), &bytes_received, 4000);
    if(err) error("receive", err);
    
    std::cout << bytes_received << " bytes received" << std::endl;

    std::cout << "result: " << number.number << std::endl << "enter number: ";
    std::cin >> number.number;
  } 
  
  err = libusb_release_interface(handy, 1);
  libusb_attach_kernel_driver(handy, 0);
  if(err) error("release", err);
    
  libusb_close(handy); 
    
  libusb_exit(NULL);
  
  return 0;
}
