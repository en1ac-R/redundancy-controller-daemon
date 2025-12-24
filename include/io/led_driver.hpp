#pragma once

#include <cstdint>
#include <string>
#include "io/port_expander.hpp"

namespace led_driver{

typedef enum{
  GREEN,
  RED,
  ORANGE,
  NO
} color;

struct led_colors{
    uint8_t green_light_value_{};
    uint8_t red_light_value_{};
    uint8_t orange_light_value_{};
    uint8_t no_light_value_{};

    led_colors() = default;

    led_colors(uint8_t green, uint8_t red): 
      green_light_value_(green), red_light_value_(red), orange_light_value_(green|red), no_light_value_(~(green|red)){}

    led_colors(uint8_t green, uint8_t red, uint8_t orange, uint8_t no):
    green_light_value_(green), red_light_value_(red), orange_light_value_(orange), no_light_value_(no){}
};

class led{
  public:
    led(const std::string& name, port_expander_out* pe_out, const led_colors& colors);
    void set_color(color cl);
    color get_current_color() const;
    
  private:
    std::string name_;
    port_expander_out* pe_out_{nullptr};
    const led_colors colors_;    
    color current_color{NO};
};

}
