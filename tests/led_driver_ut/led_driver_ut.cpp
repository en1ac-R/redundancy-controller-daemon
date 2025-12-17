#include <gtest/gtest.h>
#include "io/led_driver.hpp"
#include "io/port_expander.hpp"

#include <vector>

class led_driver_test : public ::testing::Test{
};

std::vector<led_driver::led> init_leds_1(port_expander_out* D1){
  std::vector<led_driver::led> ret;

  ret.push_back(led_driver::led("H1", D1, {0X04, 0x08}));
  ret.push_back(led_driver::led("H2", D1, {0x01, 0x02}));
  ret.push_back(led_driver::led("H3", D1, {0x20, 0x10}));
  ret.push_back(led_driver::led("H4", D1, {0x40, 0x80}));

  return ret;
}

std::vector<led_driver::led> init_leds_2(port_expander_out* D2){
  std::vector<led_driver::led> ret;

  ret.push_back(led_driver::led("H5", D2, {0X04, 0x08}));
  ret.push_back(led_driver::led("H6", D2, {0x02, 0x01}));
  ret.push_back(led_driver::led("H7", D2, {0x10, 0x20}));
  ret.push_back(led_driver::led("H8", D2, {0x40, 0x80}));

  return ret;
}

std::vector<led_driver::led> init_leds_4(port_expander_out* D4){
  std::vector<led_driver::led> ret;

  ret.push_back(led_driver::led("H9", D4, {0X10, 0x20}));
  ret.push_back(led_driver::led("H10", D4, {0x08, 0x04}));
  ret.push_back(led_driver::led("H11", D4, {0x02, 0x01}));
  ret.push_back(led_driver::led("H12", D4, {0x40, 0x80}));

  return ret;
}


TEST_F(led_driver_test, simple1){
  port_expander_out D1("/dev/i2c-4", 0x24);
  port_expander_out D2("/dev/i2c-4", 0x22);
  port_expander_out D4("/dev/i2c-4", 0x21);
  
  std::vector<led_driver::led> led_D1 = init_leds_1(&D1);
  std::vector<led_driver::led> led_D2 = init_leds_2(&D2);
  std::vector<led_driver::led> led_D4 = init_leds_4(&D4);


  for(auto i : led_D1){
    i.set_color(led_driver::ORANGE);
  }
  led_D1[0].set_color(led_driver::GREEN);
  led_D1[1].set_color(led_driver::RED);
  led_D1[2].set_color(led_driver::NO);
  led_D1[3].set_color(led_driver::ORANGE);


  for(auto i : led_D2){
    i.set_color(led_driver::ORANGE);
  }
  led_D2[0].set_color(led_driver::GREEN);
  led_D2[1].set_color(led_driver::RED);
  led_D2[2].set_color(led_driver::NO);
  led_D2[3].set_color(led_driver::ORANGE);

  for(auto i : led_D4){
    i.set_color(led_driver::NO);
  }
  led_D4[0].set_color(led_driver::GREEN);
  led_D4[1].set_color(led_driver::RED);
  led_D4[2].set_color(led_driver::NO);
  led_D4[3].set_color(led_driver::ORANGE);
  


}
