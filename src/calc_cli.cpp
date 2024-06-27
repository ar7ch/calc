#include "calc.hpp"
#include <CLI/CLI.hpp>
#include <iostream>
#include <unordered_map>
#include <string>

int main(int argc, char** argv) {
    CLI::App app{"Calculator"};

    std::string expression;
    app.add_option("expression", expression, "Arithmetic expression")->required();

    std::vector<std::string> variables;
    app.add_option("--var", variables, "Variables in the form key=value");

    CLI11_PARSE(app, argc, argv);

    calc::Calculator calculator;
    calc::Calculator::raw_variable_map_t raw_var_map;

    for (const auto& var : variables) {
        auto pos = var.find('=');
        if (pos != std::string::npos) {
            std::string key = var.substr(0, pos);
            std::string value_str = var.substr(pos + 1);
            raw_var_map[key] = value_str;
        }
    }

    try {
        double result = calculator.evaluate(expression, raw_var_map);
        std::cout << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
