#include "../../include/io/port_expander.hpp"
#include <cstddef>
#include <cstdint>
#include <gpiod.h>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdexcept>
#include <linux/i2c-dev.h>

// ---------------------------------------------------------------------------------------
// PORT_EXPANDER_DEIVCE

port_expander_device::port_expander_device(const std::string& i2c_line, uint8_t i2c_addr){
  i2c_dev_fd_ = open(i2c_line.c_str(), O_RDWR);
  if(i2c_dev_fd_ < 0){
    throw std::runtime_error("port_expander_device constructor error : open i2c device error");
  }

  if(ioctl(i2c_dev_fd_, I2C_SLAVE, i2c_addr) < 0){
    close(i2c_dev_fd_);
    throw std::runtime_error("port_expander_device constructor error : set addr i2c device error");
  }
}

port_expander_device::port_expander_device(port_expander_device&& right) noexcept{
  i2c_dev_fd_ = right.i2c_dev_fd_;
  right.i2c_dev_fd_ = -1;
}

port_expander_device& port_expander_device::operator=(port_expander_device&& right) noexcept{
  if(this != &right){
    if(i2c_dev_fd_ != -1) close(i2c_dev_fd_);
    i2c_dev_fd_ = right.i2c_dev_fd_;
    right.i2c_dev_fd_ = -1;
  }  
  return *this;
}

port_expander_device::~port_expander_device(){
  if(i2c_dev_fd_ != -1) close(i2c_dev_fd_);
}

uint8_t port_expander_device::read_byte() const{
  uint8_t value{};
  if(read(i2c_dev_fd_, &value, sizeof(value)) != sizeof(value)){
    throw std::runtime_error("port_expander_out::read_byte() error: i2c read error");
  }
  return value;
}


// ---------------------------------------------------------------------------------------
// PORT_EXPANDER_OUT



port_expander_out::port_expander_out(const std::string& i2c_line, uint8_t i2c_addr): port_expander_device(i2c_line, i2c_addr){
  write_byte(0x00);
}

port_expander_out::port_expander_out(port_expander_out&& right) noexcept : port_expander_device(std::move(right)){

}

port_expander_out& port_expander_out::operator=(port_expander_out&& right) noexcept{
  if(this != &right){
    port_expander_device::operator=(std::move(right));
  }
  return *this;
}

void port_expander_out::write_byte(uint8_t byte) const noexcept(false){
  if(write(i2c_dev_fd_, &byte, sizeof(byte)) != 1){
    throw std::runtime_error("port_expander_out::write_byte(uint8_t byte) error : I2C write error");
  }
}


// ---------------------------------------------------------------------------------------
// PORT_EXPANDER_IN

port_expander_in::port_expander_in(const std::string& i2c_line, uint8_t i2c_addr, const std::string& gpio_chip_path, uint32_t gpio_line_num): port_expander_device(i2c_line, i2c_addr){
  gpio_chip_ = gpiod_chip_open(gpio_chip_path.c_str());
  if(gpio_chip_ == NULL) throw std::runtime_error("port_expander_in error: failed to open gpio chip: " + gpio_chip_path);
 
  gpio_line_ = gpiod_chip_get_line(gpio_chip_, gpio_line_num);
  if(gpio_line_ == NULL){
    gpiod_chip_close(gpio_chip_);  
    throw std::runtime_error("port_expander_in error: failed to get gpiod line" + std::to_string(gpio_line_num));
  } 

  if(gpiod_line_request_both_edges_events(gpio_line_, "port_expander_in driver") == -1){
    gpiod_chip_close(gpio_chip_);
    throw std::runtime_error("port_expander_in error: failed to get request both events" + gpio_chip_path);
  }  
  
  gpio_event_fd_ = gpiod_line_event_get_fd(gpio_line_);
  if(gpio_event_fd_ == -1){
    gpiod_line_release(gpio_line_);
    gpiod_chip_close(gpio_chip_);
    throw std::runtime_error("port_expander_in error: failed to get event fd" + gpio_chip_path);
  }
}

port_expander_in::port_expander_in(port_expander_in&& right) noexcept : port_expander_device(std::move(right)){
  gpio_chip_ = right.gpio_chip_;
  gpio_line_ = right.gpio_line_;
  gpio_event_fd_ = right.gpio_event_fd_;

  right.gpio_chip_ = nullptr;
  right.gpio_line_ = nullptr;
  right.gpio_event_fd_ = -1;

}

port_expander_in& port_expander_in::operator=(port_expander_in&& right) noexcept {
  if(this != &right){
    if(gpio_line_ != nullptr)
      gpiod_line_release(gpio_line_);
    if(gpio_chip_ != nullptr)
      gpiod_chip_close(gpio_chip_);

    gpio_chip_ = right.gpio_chip_;
    gpio_line_ = right.gpio_line_;
    gpio_event_fd_ = right.gpio_event_fd_;

    right.gpio_chip_ = nullptr;
    right.gpio_line_ = nullptr;
    right.gpio_event_fd_ = -1;
  }

  return *this;
}

uint32_t port_expander_in::get_gpio_event_fd() const{ return gpio_event_fd_; }

port_expander_in::~port_expander_in(){
  if(gpio_line_ != nullptr)
    gpiod_line_release(gpio_line_);
  if(gpio_chip_ != nullptr)
    gpiod_chip_close(gpio_chip_);
}


