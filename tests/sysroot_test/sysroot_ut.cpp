#include "io/port_expander.hpp"

#include <gpiod.h>
#include <iostream>
#include <thread>
#include <chrono>

enum{I2C_ADDR_PE_IN = 0x27};

int main(){
    const char* chip_path = "/dev/gpiochip1";
    unsigned int line_offset = 141;
    port_expander_in pe_buttons("/dev/i2c-4", I2C_ADDR_PE_IN, chip_path, line_offset);

    auto event_fd = pe_buttons.get_gpio_event_fd();
    auto byte = pe_buttons.read_byte();

    
    // 1. Открываем чип
    gpiod_chip* chip = gpiod_chip_open(chip_path);
    if (!chip) {
        std::cerr << "Failed to open chip: " << chip_path << std::endl;
        return 1;
    }

    // 2. Получаем линию
    gpiod_line* line = gpiod_chip_get_line(chip, line_offset);
    if (!line) {
        std::cerr << "Failed to get line " << line_offset << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    // 3. Запрашиваем линию как вход
    if (gpiod_line_request_input(line, "gpiod-test") < 0) {
        std::cerr << "Failed to request line as input" << std::endl;
        gpiod_chip_close(chip);
        return 1;
    }

    std::cout << "Monitoring GPIO line " << line_offset
              << " on " << chip_path << " (press Ctrl+C to stop)\n";

    // 4. Бесконечный цикл чтения состояния
    while (true) {
        int value = gpiod_line_get_value(line);
        if (value < 0) {
            std::cerr << "Failed to read value\n";
        } else {
            std::cout << "GPIO value: " << value << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }

    // Никогда не дойдет сюда, но по правилам:
    gpiod_line_release(line);
    gpiod_chip_close(chip);

    return 0;
}
