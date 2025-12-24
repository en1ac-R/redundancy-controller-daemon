cmake_minimum_required(VERSION 3.13)  

project(redundancy-controller-daemon)

# Build port expander driver
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/io/)

# Build sysroot test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/sysroot_test)

# Build port_expander test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/port_expander_ut)

# Build led_driver test
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/led_driver_ut)

# Build buttons_driver test

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/buttons_ut)
