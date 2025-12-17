#include "io/led_driver.hpp"
#include <cstdint>
#include <stdexcept>

led_driver::led::led(const std::string& name, port_expander_out* pe_out, const led_colors& colors): name_(name), pe_out_(pe_out), colors_(colors){
  if(pe_out == nullptr)
    throw std::runtime_error("led_driver::led::led error: invalid port_expander_out object");
};

// void led_driver::led::set_color(color cl) const{
//   uint8_t cur = pe_out_->get_shadow();
//   uint8_t mask = colors_.green_light_value_ | colors_.red_light_value_;

//   switch(cl){
//     case GREEN:
//       pe_out_->write_byte(colors_.green_light_value_ | (cur & ~mask));
//       break;
//     case RED:
//       pe_out_->write_byte(colors_.red_light_value_ | (cur & ~mask));
//       break;
//     case ORANGE:
//       pe_out_->write_byte(colors_.orange_light_value_ | (cur & ~mask));
//       break;
//     case NO:
//       pe_out_->write_byte(cur | mask);
//       break;
//     default:
//       throw std::runtime_error("led_driver::led::set_color error: invalid color");
//   }
// }

// void led_driver::led::set_color(color cl) const {
//   uint8_t cur  = pe_out_->get_shadow();
//   uint8_t mask = colors_.green_light_value_ | colors_.red_light_value_;

//   switch (cl) {
//     case GREEN:
//       pe_out_->write_byte((cur & ~mask) | colors_.green_light_value_);
//       break;

//     case RED:
//       pe_out_->write_byte((cur & ~mask) | colors_.red_light_value_);
//       break;

//     case ORANGE:
//       pe_out_->write_byte(cur | mask);
//       break;

//     case NO:
//       pe_out_->write_byte(cur & ~mask);
//       break;

//     default:
//       throw std::runtime_error("invalid color");
//   }
// }

void led_driver::led::set_color(color cl) const{
  uint8_t read_byte = pe_out_->read_byte();
  switch (cl) {
    case GREEN:
      pe_out_->write_byte((read_byte & colors_.no_light_value_) | colors_.green_light_value_);
      break;

    case RED:
      pe_out_->write_byte((read_byte & colors_.no_light_value_) | colors_.red_light_value_);
      break;

    case ORANGE:
      pe_out_->write_byte((read_byte & colors_.no_light_value_) | colors_.orange_light_value_);
      break;

    case NO:
      pe_out_->write_byte(read_byte & colors_.no_light_value_);
      break;

    default:
      throw std::runtime_error("invalid color");
  }
}

led_driver::color led_driver::led::get_color() const{
  // uint8_t cl = pe_out_->read_byte();

  // if(colors_.green_light_value_){
  //   return GREEN;
  // } else if (cl == colors_.red_light_value_) {
  //   return RED;
  // } else if (cl == colors_.orange_light_value_) {
  //   return ORANGE;
  // } else if (cl == colors_.no_light_value_) {
  //   return NO;
  // } else{
  //   throw std::runtime_error("ERR_COLOR");
  // }

  return NO;
}
