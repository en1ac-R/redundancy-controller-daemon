cmake_minimum_required(VERSION 3.13)  

project(redundancy-controller-daemon)

# Build port expander driver
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/io/)

# Build Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/sysroot_test)


# Build led_driver test

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/led_driver_ut)
