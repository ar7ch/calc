#include "evaluator.hpp"
#include <cmath>
#include <stdexcept>

namespace calc {

double Evaluator::evaluate(const Parser::AST* node, const variable_map_t& variables) {
    if (auto number = dynamic_cast<const Parser::Number*>(node)) {
        return evaluate_number(number);
    } else if (auto variable = dynamic_cast<const Parser::Variable*>(node)) {
        return evaluate_variable(variable, variables);
    } else if (auto function = dynamic_cast<const Parser::Function*>(node)) {
        return evaluate_function(function, variables);
    } else if (auto binary_op = dynamic_cast<const Parser::BinaryOp*>(node)) {
        return evaluate_binary_op(binary_op, variables);
    }
    throw std::runtime_error("Unknown AST node type");
}

double Evaluator::evaluate_number(const Parser::Number* node) {
    return node->value;
}

double Evaluator::evaluate_variable(const Parser::Variable* node, const variable_map_t& variables) {
    auto it = variables.find(node->name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined variable: " + node->name);
}

double Evaluator::evaluate_function(const Parser::Function* node, const variable_map_t& variables) {
    double arg_value = evaluate(node->arg.get(), variables);
    if (node->name == "sin") {
        return std::sin(arg_value);
    } else if (node->name == "cos") {
        return std::cos(arg_value);
    } else if (node->name == "tan") {
        return std::tan(arg_value);
    } else if (node->name == "log") {
        return std::log(arg_value);
    }
    throw std::runtime_error("Unknown function: " + node->name);
}

double Evaluator::evaluate_binary_op(const Parser::BinaryOp* node, const variable_map_t& variables) {
    double left_value = evaluate(node->left.get(), variables);
    double right_value = evaluate(node->right.get(), variables);

    switch (node->op) {
        case Lexer::Token::TokenType::PLUS:
            return left_value + right_value;
        case Lexer::Token::TokenType::MINUS:
            return left_value - right_value;
        case Lexer::Token::TokenType::MUL:
            return left_value * right_value;
        case Lexer::Token::TokenType::DIV:
            if (right_value == 0) {
                throw std::runtime_error("Division by zero");
            }
            return left_value / right_value;
        default:
            throw std::runtime_error("Unknown binary operator");
    }
}

} // namespace calc
