#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <gpiod.h>

class port_expander_device{
  protected:
    int i2c_dev_fd_{-1};
  public:
    port_expander_device() = delete;
    port_expander_device(const std::string& i2c_line, uint8_t i2c_addr);

    port_expander_device(const port_expander_device&) = delete;
    port_expander_device& operator=(const port_expander_device&) = delete;
    port_expander_device(port_expander_device&& right) noexcept;
    port_expander_device& operator=(port_expander_device&& right) noexcept;
    ~port_expander_device();

    uint8_t read_byte() const;
    
};

//port_expander with leds
class port_expander_out : public port_expander_device{
  public:
    port_expander_out() = delete;
    port_expander_out(const std::string& i2c_line, uint8_t i2c_addr);

    port_expander_out(const port_expander_out&) = delete;
    port_expander_out& operator=(const port_expander_out&) = delete;
    port_expander_out(port_expander_out&& right) noexcept;
    port_expander_out& operator=(port_expander_out&& right) noexcept;
    ~port_expander_out() = default;

    void write_byte(uint8_t byte) const noexcept(false);

};

//port_expander with buttons
class port_expander_in : public port_expander_device{
  public:
    port_expander_in() = delete;
    port_expander_in(const std::string& i2c_line, uint8_t i2c_addr, const std::string& gpio_chip_path, uint32_t gpio_line_num);
    port_expander_in(const port_expander_out&) = delete;
    port_expander_in& operator=(const port_expander_out&) = delete;
    port_expander_in(port_expander_out&& right) noexcept;
    port_expander_in& operator=(port_expander_out&& right) noexcept;
    ~port_expander_in();

    uint32_t get_gpiod_fd() const;

  private:
    gpiod_chip* gpio_chip_{nullptr};
    gpiod_line_settings* gpio_line_settings_{nullptr};
    gpiod_line_config* gpio_line_config_{nullptr};
    gpiod_line_request* gpio_request_{nullptr}; 
};

