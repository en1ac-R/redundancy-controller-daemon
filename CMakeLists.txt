cmake_minimum_required(VERSION 3.13)  

project(redundancy-controller-daemon)

add_executable(sysroot_ut ${CMAKE_CURRNET_SOURCE_DIR}tests/sysroot_test/sysroot_ut.cpp)
target_link_libraries(sysroot_ut gpiod)
