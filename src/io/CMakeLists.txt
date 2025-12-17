add_library(pe STATIC ${CMAKE_CURRENT_SOURCE_DIR}/port_expander.cpp)
target_include_directories(pe PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(pe PUBLIC gpiod)

add_library(led_driver STATIC ${CMAKE_CURRENT_SOURCE_DIR}/led_driver.cpp)
target_include_directories(pe PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(led_driver PUBLIC pe)

