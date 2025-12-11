add_library(port_expander port_expander.cpp)

target_include_directories(port_expander PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories($ENV{HOME}/gpiod1/include)

link_directories($ENV{HOME}/gpiod1/lib)
target_link_libraries(myapp gpiod)
