# Calculator Project

![main pipeline](https://github.com/ar7ch/calc/actions/workflows/main.yml/badge.svg)

This project is a calculator application that can evaluate arithmetic expressions with support for variables and functions. It works by tokenizing the input expression, parsing the tokens into an abstract syntax tree (AST), and evaluating the AST to compute the result.

It has a modular structure: aforementioned functionalities are represented by Lexer, Parser and Evaluator classes, respectively. I use recursive descent parsing to build the AST.
Each part can be used separately using generated libraries: `liblexer`, `libparser`, `libevaluator`. There is a facading `libcalc` library that combines all of them.
Executable `calc_cli` is a command line interface that uses `libcalc` to evaluate expressions.

The calculator can be extended by adding new operators, functions, and variables.

## Features

- Supports basic arithmetic operations: addition, subtraction, multiplication, division;
- Supports parentheses for grouping: `()`, `{}`, `[]`;
- Supports functions: `sin`, `cos`, `tan`, `log`;
- Supports variable substitution.

## Limitations

- The calculator does not support expressions with variables in the function arguments;
- In parsing errors, the calculator does not provide detailed information about the error location.

## Prerequisites

- CMake (version 3.10 or higher)
- g++

## Getting Started

### Using Docker

You can:
- build a Docker image using the provided Dockerfile;
- use the [pre-built image from Docker Hub](https://hub.docker.com/repository/docker/ar7ch/calc):
    ```sh
    docker run -it ar7ch/calc
    ```

Limitations of Docker do not allow passing quoted arguments to the container (at list without ugly escaping), so you can invoke calculator from the container shell:
```sh
$ calc_cli -h
$ calc -h # docker version has this symlink
```

### Building Natively

I provide a Makefile with shortcuts for building the project:

```sh
make calc_cli
```

Alternatively, you can use CMake directly:

```sh
mkdir build
cmake -S . -B build
cmake --build build --target calc_cli
```

### Running Tests

GTest is used as a testing framework. To run the tests:

```sh
make tests
```


### Static analysis

To run static analysis (clang-tidy and cppcheck, you need to have binaries installed on your system):

```sh
make analyze
```


## Using the Calculator

The calculator accepts an arithmetic expression and variables via command line:

### Example Usage

1. **Evaluate an expression:**
   ```sh
   calc_cli "2 + 3 * (4 - 1)"
   ```

2. **Evaluate an expression with variables:**
   ```sh
   calc_cli "x + y" --var x=5 --var y=10
   ```

3. **Evaluate an expression with variable dependencies _(expressions with variables not supported)_:**
   ```sh
   calc_cli "(1 + x) / y" --var x=5 --var y=x
   ```
4. Use builtin aliases (currently `PI` and `E` are available, see [evaluator.cpp](src/evaluator.cpp) to add more):
   ```sh
   calc_cli "sin(PI/6)"
   ```

## Extending the Calculator

### Adding New Operators

To add a new operator, follow these steps:

1. **Modify the Lexer:**
   - Update the `char2tok` map in [lexer.cpp](src/lexer.cpp) to include the new operator.

2. **Update the Parser:**
   - According to grammar described in [parser.hpp](src/parser.hpp), modify the `parse_expression`, `parse_term`, and `parse_factor` functions in `parser.cpp` to handle the new operator.

3. **Update the Evaluator:**
   - Extend the `evaluate_*` function in [evaluator.cpp](src/evaluator.cpp) to perform the operation.

## License

Licensed under GNU General Public License v3.0. See [LICENSE](LICENSE) for more information.
