cmake_minimum_required(VERSION 3.20)
project(cpp_log_analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(loganalyzer_core STATIC
        src/parser.cpp
        src/analyzer.cpp
        src/exporter.cpp
        src/app.cpp
        src/cli.cpp
)

target_include_directories(loganalyzer_core PUBLIC include)
if(MSVC)
    target_compile_options(loganalyzer_core PRIVATE /W4)
else()
    target_compile_options(loganalyzer_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(loganalyzer_app src/main.cpp)
target_link_libraries(loganalyzer_app PRIVATE loganalyzer_core)

include(FetchContent)
FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()
add_executable(tests
        tests/test_parser.cpp
        tests/test_analyzer.cpp
        tests/test_exporter.cpp
        tests/test_cli.cpp
)
target_link_libraries(tests PRIVATE loganalyzer_core Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
catch_discover_tests(tests)