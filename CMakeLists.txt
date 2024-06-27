cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(Calculator)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

add_library(evaluator_lib SHARED src/evaluator.cpp)
add_library(lexer_lib SHARED src/lexer.cpp)
add_library(parser_lib SHARED src/parser.cpp)
add_library(calc_lib SHARED src/calc.cpp)
target_link_libraries(calc_lib lexer_lib parser_lib evaluator_lib)

# cli executable
add_executable(calc_cli src/calc_cli.cpp)
target_link_libraries(calc_cli calc_lib CLI11::CLI11)

# Add CLI11
include(FetchContent)
FetchContent_Declare(
    cli11
    GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
    GIT_TAG v2.4.2
)
FetchContent_MakeAvailable(cli11)

# Add GoogleTest
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test executables
add_executable(lexer_tests tests/lexer_tests.cpp)
target_link_libraries(lexer_tests gtest_main lexer_lib)
target_include_directories(lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(parser_tests tests/parser_tests.cpp)
target_link_libraries(parser_tests gtest_main parser_lib lexer_lib)
target_include_directories(parser_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(evaluator_tests tests/evaluator_tests.cpp)
target_link_libraries(evaluator_tests gtest_main parser_lib lexer_lib evaluator_lib)
target_include_directories(evaluator_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_executable(calc_tests tests/calc_tests.cpp)
target_link_libraries(calc_tests gtest_main calc_lib)
target_include_directories(calc_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)

include(GoogleTest)
gtest_discover_tests(lexer_tests)
gtest_discover_tests(parser_tests)
gtest_discover_tests(evaluator_tests)
gtest_discover_tests(calc_tests)

# Add custom target to run tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS lexer_tests
    DEPENDS parser_tests
    DEPENDS evaluator_tests
    DEPENDS calc_tests
)
