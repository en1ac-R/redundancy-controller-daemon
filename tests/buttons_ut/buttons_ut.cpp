#include <io/buttons.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class buttons_test : public ::testing::Test{
  public:
};



TEST_F(buttons_test, output_test){

  std::vector <button> buttons{{"S1", 0xF7}, {"S2", 0xFB}, {"S3", 0xFD}, {"S4", 0xFE}, {"S5", 0x7F}};
  port_expander_in pe_in("/dev/i2c-4", 0x26, "/dev/gpiochip1", 141);

  std::vector <button> ret = buttons_polling::start_polling(buttons, &pe_in);

  // for(auto i : ret){
  //   std::cout << i.name << " + "; 
  // }
  
  while(true){
    std::vector <button> ret = buttons_polling::start_polling(buttons, &pe_in);

    for(auto i : ret){
      std::cout << i.name << " + "; 
    }
    std::cout << std::endl;
  }
  
}

