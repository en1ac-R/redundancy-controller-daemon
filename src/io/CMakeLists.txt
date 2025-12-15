add_library(pe STATIC ${CMAKE_CURRENT_SOURCE_DIR}/port_expander.cpp)
target_include_directories(pe PUBLIC ${CMAKE_SOURCE_DIR}/include)
