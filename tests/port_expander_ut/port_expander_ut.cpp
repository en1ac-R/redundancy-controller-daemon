#include "io/port_expander.hpp"

#include <cstdint>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class port_expander_in_test : public ::testing::Test{
  public:
};

class port_expander_out_test : public ::testing::Test{
  public:
};

TEST_F(port_expander_out_test, out_test){
  port_expander_out D1("/dev/i2c-4", 0x24);

  uint8_t all_green_leds_byte = 0x04 + 0x01 + 0x20 + 0x40;
  // uint8_t all_green_leds_byte = 0x00;

  D1.write_byte(all_green_leds_byte);

  ASSERT_EQ(D1.read_byte(), all_green_leds_byte);
}
