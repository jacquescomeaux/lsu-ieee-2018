#include <cstdlib>
#include <iostream>
#include <libusb-1.0/libusb.h>

union int_thing {
  unsigned char usb_data[4];
  uint32_t number;
};

void print_devs(libusb_device **devs) {
  libusb_device *dev;
  int i = 0

  ;
  while((dev = devs[i++]) != NULL) {
    struct libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0) {
      //fprintf(stderr, "failed to get device descriptor");
      return;
    }
    std::cout << libusb_get_bus_number(dev) << " woww" << libusb_get_device_address(dev) << std::endl;
    //printf("%04x:%04x (bus %d, device %d)\n",
    //desc.idVendor, desc.idProduct,
    //libusb_get_bus_number(dev), libusb_get_device_address(dev));
  }
}

void error(std::string s, int err) {
  std::cout << s << " Error: " << libusb_error_name(err) << std::endl;
  exit(err);
}

int main() {
  libusb_init(NULL);
  libusb_set_debug(NULL, LIBUSB_LOG_LEVEL_DEBUG);
  int transferred = 0;
  int err;
  libusb_device_handle* handy;
  handy = libusb_open_device_with_vid_pid(NULL, 0x2341, 0x0042);//ardy, &handy);
  if(handy == NULL) {std::cout << "wowowowowow" << std::endl; goto exiter;}
  libusb_set_auto_detach_kernel_driver(handy, 1);
  //libusb_detach_kernel_driver(handy, 0);
  err = libusb_claim_interface(handy, 1);
  err = libusb_claim_interface(handy, 0);
  if(err) error("claim", err);
  err = libusb_set_interface_alt_setting(handy, 1, 0);
  if(err) error("set alt serting", err);
  union int_thing number;
  //while(transferred != 4) 
  err = libusb_bulk_transfer(handy, 0x83, number.usb_data, sizeof(union int_thing), &transferred, 4000);
  //if(err) error("transger", err);
  //err = libusb_release_interface(handy, 1);
  //err = libusb_release_interface(handy, 0);
  //libusb_attach_kernel_driver(handy, 0);
  if(err) error("trealser", err);
  libusb_close(handy); 
  std::cout << transferred <<  "numbero" << number.number << std::endl;
  std::cout << "Hello World" << std::endl;
  libusb_exit(NULL);
  return 0;
exiter:
  libusb_exit(NULL);
  return -1;
}
