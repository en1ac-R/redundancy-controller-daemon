#pragma once

#include <cstdint>
#include <string>

#if defined(__x86_64__)
  #include "../../lib/gpiod1/include/gpiod.h"
#else 
  #include <gpiod.h>
#endif

/// \class port_expander_device
/// \brief Base class for working with PCF8574 port expanders.
/// \details Copying is prohibited; only move semantics are supported.
class port_expander_device {
public:
    /// \brief Default constructor deleted.
    port_expander_device() = delete;

    /// \brief Main constructor.
    /// \param i2c_line Path to the I2C device, e.g., "/dev/i2c-4".
    /// \param i2c_addr Address of the device on the I2C bus, e.g., 0x24.
    port_expander_device(const std::string& i2c_line, uint8_t i2c_addr);
    
    /// \brief Copy constructor deleted.
    port_expander_device(const port_expander_device&) = delete;

    /// \brief Copy assignment operator deleted.
    port_expander_device& operator=(const port_expander_device&) = delete;

    /// \brief Move constructor.
    port_expander_device(port_expander_device&& right) noexcept;

    /// \brief Move assignment operator.
    port_expander_device& operator=(port_expander_device&& right) noexcept;

    /// \brief Destructor.
    ~port_expander_device();
    
    /// \brief Reads a byte from the I2C device buffer.
    /// \return Byte value read from the I2C device.
    uint8_t read_byte() const;

protected:
    /// \brief File descriptor of the I2C device.
    int i2c_dev_fd_{-1}; 
};

/// \class port_expander_out
/// \brief Derived class for controlling output (LEDs) on a PCF8574 port expander.
/// \details Inherits from port_expander_device. Provides functionality to write a byte
///          to the I2C device to control outputs such as LEDs. Read operations are
///          still available via the base class.
class port_expander_out : public port_expander_device {
public:
    /// \brief Default constructor deleted.
    port_expander_out() = delete;

    /// \brief Constructor for initializing the output device.
    /// \param i2c_line Path to the I2C device, e.g., "/dev/i2c-4".
    /// \param i2c_addr Address of the device on the I2C bus, e.g., 0x24.
    port_expander_out(const std::string& i2c_line, uint8_t i2c_addr);

    /// \brief Copy constructor deleted.
    port_expander_out(const port_expander_out&) = delete;

    /// \brief Copy assignment operator deleted.
    port_expander_out& operator=(const port_expander_out&) = delete;

    /// \brief Move constructor.
    port_expander_out(port_expander_out&& right) noexcept;

    /// \brief Move assignment operator.
    port_expander_out& operator=(port_expander_out&& right) noexcept;

    /// \brief Destructor.
    ~port_expander_out() = default;

    /// \brief Writes a byte to the output device (e.g., to set LEDs).
    /// \param byte Byte to write to the I2C device.
    void write_byte(uint8_t byte) const noexcept(false);
};


/// \class port_expander_in
/// \brief Derived class for working with input pins (buttons) of the PCF8574 port expander.
/// \details Inherits from port_expander_device. Provides functionality for handling GPIO lines,
///          including obtaining an event file descriptor for use with epoll.
///          Copying is disabled; only move operations are supported.
class port_expander_in : public port_expander_device {
public:
    /// \brief Default constructor deleted.
    port_expander_in() = delete;

    /// \brief Constructor for initializing an input device.
    /// \param i2c_line Path to the I2C device, e.g., "/dev/i2c-4".
    /// \param i2c_addr Address of the device on the I2C bus, e.g., 0x24.
    /// \param gpio_chip_path Path to the GPIO chip, e.g., "/dev/gpiochip0".
    /// \param gpio_line_num Number of the GPIO line to use for the button.
    port_expander_in(const std::string& i2c_line, uint8_t i2c_addr, 
                     const std::string& gpio_chip_path, uint32_t gpio_line_num);

    /// \brief Copy constructor deleted.
    port_expander_in(const port_expander_in&) = delete;

    /// \brief Copy assignment operator deleted.
    port_expander_in& operator=(const port_expander_in&) = delete;

    /// \brief Move constructor.
    port_expander_in(port_expander_in&& right) noexcept;

    /// \brief Move assignment operator.
    port_expander_in& operator=(port_expander_in&& right) noexcept;

    /// \brief Destructor. Releases GPIO resources.
    ~port_expander_in();

    /// \brief Gets the GPIO event file descriptor for use with epoll.
    /// \return File descriptor of the GPIO line event.
    uint32_t get_gpio_event_fd() const;

private:
    /// \brief Pointer to the opened GPIO chip.
    gpiod_chip* gpio_chip_ = nullptr;

    /// \brief Pointer to the GPIO line used for the button.
    gpiod_line* gpio_line_ = nullptr;

    /// \brief File descriptor for the GPIO event.
    int gpio_event_fd_{-1};
};


