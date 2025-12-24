#pragma once

#include "io/port_expander.hpp"
#include <cstdint>
#include <string>
#include <vector>

struct button{
  std::string name;
  uint8_t button_byte{};

  button(const std::string& name, uint8_t button_byte): name(name), button_byte(button_byte){}
};

class buttons_polling{
  
  public:
    static void set_pe_in(port_expander_in* pe_in); 
    static std::vector<button> start_polling(std::vector<button> buttons, port_expander_in* pe_in);
};



