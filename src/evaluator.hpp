#pragma once

#include "parser.hpp"
#include <unordered_map>

namespace calc {

class Evaluator {
public:
    using variable_map_t = std::unordered_map<std::string, double>;

    double evaluate(const Parser::AST* node, const variable_map_t& variables = {});

private:
    double evaluate_number(const Parser::Number* node);
    double evaluate_variable(const Parser::Variable* node, const variable_map_t& variables);
    double evaluate_function(const Parser::Function* node, const variable_map_t& variables);
    double evaluate_binary_op(const Parser::BinaryOp* node, const variable_map_t& variables);
};

} // namespace calc
