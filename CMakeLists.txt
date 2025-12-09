cmake_minimum_required(VERSION 3.15)
project(redundancy-controller-daemon LANGUAGES CXX)

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем include/ как публичный путь для всех модулей
include_directories(${PROJECT_SOURCE_DIR}/include)

# Добавляем поддиректории
add_subdirectory(src/core)
add_subdirectory(src/io)
add_subdirectory(src/utils)
add_subdirectory(src/commands)
add_subdirectory(src/snmp)
add_subdirectory(src/app)

# Основной исполняемый файл (main)
add_executable(rcd src/main.cpp)

# Линкуем всё к приложению
target_link_libraries(rcd
    core
    io
    utils
    commands
    snmp
    app
)
