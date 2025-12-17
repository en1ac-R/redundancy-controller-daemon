add_executable(led_driver_ut led_driver_ut.cpp)
target_link_libraries(led_driver_ut PUBLIC gtest gtest_main pthread led_driver)

target_include_directories(led_driver_ut PRIVATE ${CMAKE_SYSROOT}/usr/include)
target_include_directories(led_driver_ut PRIVATE ${CMAKE_SOURCE_DIR}/include)
