add_executable(buttons_ut buttons_ut.cpp)
target_link_libraries(buttons_ut PUBLIC gtest gtest_main pthread buttons_driver)

target_include_directories(buttons_ut PRIVATE ${CMAKE_SYSROOT}/usr/include)
target_include_directories(buttons_ut PRIVATE ${CMAKE_SOURCE_DIR}/include)
