#include "io/port_expander.hpp"

#include <gpiod.h>
#include <iostream>
#include <sys/epoll.h>
#include <unistd.h>

enum{I2C_ADDR_PE_IN = 0x27};

int main(){
    port_expander_out pe_leds1{"/dev/i2c-4", 0x24};
    port_expander_out pe_leds2{"/dev/i2c-4", 0x22};
    port_expander_out pe_leds3{"/dev/i2c-4", 0x21};

    pe_leds1.write_byte(0xFE);
    pe_leds2.write_byte(0xFF);
    pe_leds3.write_byte(0xFF);

    if(pe_leds1.read_byte() == 0xFF){
        std::cout << "D1 = 0XFF " << std::endl;
    }
    std::cout << "Read_byte D1: " << pe_leds1.read_byte() << std::endl; 
    std::cout << "Read_byte D2: " << pe_leds2.read_byte() << std::endl;
    std::cout << "Read_byte D3: " << pe_leds3.read_byte() << std::endl;



    port_expander_in pe_buttons{"/dev/i2c-4", 0x26, "/dev/gpiochip1", 141};
    int gpio_fd = pe_buttons.get_gpio_event_fd();

    int epoll_fd = epoll_create1(0);

    epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.fd = gpio_fd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, gpio_fd, &ev);

     while (true) {
        epoll_event event{};
        int n = epoll_wait(epoll_fd, &event, 1, -1);
        if (n < 0) {
            perror("epoll_wait");
            break;
        }

        if (event.events & EPOLLIN) {
            gpiod_line_event gpio_event{};
            auto ret = gpiod_line_event_read((gpiod_line*)pe_buttons.get_gpio_line(), &gpio_event);
            if (ret < 0) {
                perror("gpiod_line_event_read");
                break;
            }
            usleep(100000);

            if (gpio_event.event_type == GPIOD_LINE_EVENT_FALLING_EDGE) {
                std::cout << "BUTTON PRESSED\n";

            } else if (gpio_event.event_type == GPIOD_LINE_EVENT_RISING_EDGE) {
                std::cout << "BUTTON RELEASED\n";
            }
        }
    }
  

    return 0;
}
