.PHONY: all build_dir cmake tests calc_cli_only calc_cli cppcheck clang-tidy analyze check

all: tests

build_dir:
	mkdir -p build

cmake: build_dir
	cmake -S . -B build/ -DCMAKE_BUILD_TYPE=Debug

tests: cmake
	cmake --build build --target run_tests

calc_cli_only: cmake
	cmake --build build --target calc_cli

calc_cli: check calc_cli_only

cppcheck: cmake
	cppcheck --enable=all --inconclusive --std=c++20 --language=c++  \
		--suppress=missingIncludeSystem \
		--error-exitcode=1 \
		--suppress=noExplicitConstructor src/

clang-tidy: cmake
	clang-tidy -p build/ src/*.cpp -- -I src -I ./build/_deps/cli11-src/include/

analyze: build_dir cppcheck clang-tidy

check: analyze tests
