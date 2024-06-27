cmake_minimum_required(VERSION 3.10)
project(Calculator)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# Add source files
add_library(evaluator_lib src/evaluator.cpp)
add_library(lexer_lib src/lexer.cpp)
add_library(parser_lib src/parser.cpp)
add_executable(calc src/calc.cpp)
target_link_libraries(calc lexer_lib parser_lib evaluator_lib)

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
target_link_libraries(lexer_tests gtest_main lexer_lib)
target_include_directories(lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(parser_tests tests/parser_tests.cpp)
target_link_libraries(parser_tests gtest_main parser_lib lexer_lib)
target_include_directories(parser_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(evaluator_tests tests/evaluator_tests.cpp)
target_link_libraries(evaluator_tests gtest_main parser_lib lexer_lib evaluator_lib)
target_include_directories(evaluator_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(lexer_tests)
gtest_discover_tests(parser_tests)
gtest_discover_tests(evaluator_tests)

# Add custom target to run tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS lexer_tests
    DEPENDS parser_tests
    DEPENDS evaluator_tests
)
