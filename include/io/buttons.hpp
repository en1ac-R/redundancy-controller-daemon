#pragma once

#include "io/port_expander.hpp"
#include <string>

class Button{
  public:
    
  private:
    std::string name_;
    static inline port_expander_in* pe_in_{nullptr};
        
};
