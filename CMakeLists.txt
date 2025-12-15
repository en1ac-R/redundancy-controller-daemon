cmake_minimum_required(VERSION 3.13)  

project(redundancy-controller-daemon)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/io/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests/sysroot_test)
