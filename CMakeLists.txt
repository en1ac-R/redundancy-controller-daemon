cmake_minimum_required(VERSION 3.13)  

project(redundancy-controller-daemon)

# Build port expander driver
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/io/)

# Build Tests
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/sysroot_test)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/port_expander_ut)
