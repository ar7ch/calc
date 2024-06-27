#pragma once

#include "parser.hpp"
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <numbers>
#include <cmath>

namespace calc {

class Evaluator {
public:
    using variable_map_t = std::unordered_map<std::string, double>;
    using raw_variable_map_t = std::unordered_map<std::string, std::string>;

    Evaluator(const Parser::AST* ast, const raw_variable_map_t& raw_variables);

    double evaluate();
    double evaluate(const Parser::AST* node);

private:
    const Parser::AST* ast;
    variable_map_t variables;
	variable_map_t builtins = {
		{"PI", M_PI},
		{"E", M_E}
	};

    void resolve_variables(const raw_variable_map_t& raw_variables);
    double resolve_variable(const std::string& var, const raw_variable_map_t& raw_variables, std::unordered_set<std::string>& resolving);

    static double evaluate_number(const Parser::Number* node);
    double evaluate_variable(const Parser::Variable* node);
    double evaluate_function(const Parser::Function* node);
    double evaluate_binary_op(const Parser::BinaryOp* node);
};

} // namespace calc
