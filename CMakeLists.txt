cmake_minimum_required(VERSION 3.20)

project(cpp_log_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(cpp_log_analyzer
        src/main.cpp
        src/parser.cpp
        src/analyzer.cpp
        src/exporter.cpp
        src/cli.cpp
)


find_package(Catch2 REQUIRED)
add_executable(tests
        tests/test_parser.cpp
        tests/test_analyzer.cpp
        tests/test_exporter.cpp
        src/parser.cpp
        src/analyzer.cpp
        src/exporter.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2)
target_include_directories(tests PRIVATE include)

target_include_directories(cpp_log_analyzer PRIVATE include)

target_compile_options(cpp_log_analyzer PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)