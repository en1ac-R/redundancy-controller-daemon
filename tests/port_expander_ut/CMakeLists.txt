add_executable(port_expander_ut port_expander_ut.cpp)

target_link_libraries(port_expander_ut PUBLIC gtest gtest_main pthread pe)
target_include_directories(port_expander_ut PRIVATE ${CMAKE_SYSROOT}/usr/include)
target_include_directories(port_expander_ut PRIVATE ${CMAKE_SOURCE_DIR}/include)
