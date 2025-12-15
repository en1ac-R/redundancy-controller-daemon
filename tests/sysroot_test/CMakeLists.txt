add_executable(sysroot_ut ${CMAKE_CURRENT_SOURCE_DIR}/sysroot_ut.cpp)
target_link_libraries(sysroot_ut gpiod pe)

target_include_directories(sysroot_ut PRIVATE ${CMAKE_SYSROOT}/usr/include)
target_include_directories(sysroot_ut PRIVATE ${CMAKE_SOURCE_DIR}/include)
