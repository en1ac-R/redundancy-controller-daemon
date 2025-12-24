#include <io/buttons.hpp>
// #include <iostream>
// #include <ostream>
#include <stdexcept>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/timerfd.h>

std::vector<button> buttons_polling::start_polling(std::vector<button> buttons, port_expander_in* pe_in){
  enum{MAX_EVENTS = 1};

  struct gpiod_line_event gev;

  timespec ts{0, 0};
  while (gpiod_line_event_wait(const_cast<gpiod_line*>(pe_in->get_gpio_line()), &ts) == 1) {
    gpiod_line_event_read(
        const_cast<gpiod_line*>(pe_in->get_gpio_line()), &gev);
  }

  if(pe_in == nullptr) throw std::runtime_error("buttons_polling::start_polling error: port_expander in not valide or not declarayed");
  
  auto pe_event_fd = pe_in->get_gpio_event_fd();

  int epoll_fd = epoll_create1(0);
  
  struct epoll_event ev;
  ev.events = EPOLLIN;
  ev.data.fd = pe_event_fd; 

  epoll_ctl(epoll_fd, EPOLL_CTL_ADD, pe_event_fd, &ev);

  pe_in->read_byte();
  epoll_wait(epoll_fd, &ev, MAX_EVENTS, -1);

  usleep(10000);

  gpiod_line_event_read(const_cast<gpiod_line *>(pe_in->get_gpio_line()), &gev);
  auto buttons_byte = pe_in->read_byte(); 
  
  std::vector<button> ret{};

  for(auto& i : buttons){
    if(((~i.button_byte) & buttons_byte) == 0){
      ret.push_back(i);
    }
  }
  
  return ret;
}
