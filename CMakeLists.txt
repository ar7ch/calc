cmake_minimum_required(VERSION 3.10)
project(Calculator)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Add source files
add_library(lexer_lib src/lexer.cpp)
add_executable(calc src/lexer.cpp src/calc.cpp)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executable
add_executable(lexer_tests tests/lexer_tests.cpp)
target_link_libraries(lexer_tests lexer_lib gtest_main)
target_include_directories(lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(lexer_tests)

# Add custom target to run tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS lexer_tests
)
