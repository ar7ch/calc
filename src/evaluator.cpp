#include "evaluator.hpp"
#include <cmath>
#include <stdexcept>

namespace calc {

Evaluator::Evaluator(const Parser::AST* ast, const raw_variable_map_t& raw_variables) : ast(ast) {
    resolve_variables(raw_variables);
}

void Evaluator::resolve_variables(const raw_variable_map_t& raw_variables) {
    std::unordered_set<std::string> resolving;
    for (const auto& kv : raw_variables) {
        resolve_variable(kv.first, raw_variables, resolving);
    }
	for (const auto& kv : builtins) {
		variables[kv.first] = kv.second;
	}
}

double Evaluator::resolve_variable(const std::string& var, const raw_variable_map_t& raw_variables, std::unordered_set<std::string>& resolving) {
    if (variables.find(var) != variables.end()) {
        return variables[var];
    }

    if (resolving.find(var) != resolving.end()) {
        throw std::runtime_error("Cyclic dependency detected for variable: " + var);
    }

    resolving.insert(var);

    auto it = raw_variables.find(var);
    if (it == raw_variables.end()) {
        throw std::runtime_error("Undefined variable: " + var);
    }

    std::string value_str = it->second;
    try {
        double value = std::stod(value_str);
        variables[var] = value;
    } catch (const std::invalid_argument&) {
        double value = resolve_variable(value_str, raw_variables, resolving);
        variables[var] = value;
    }

    resolving.erase(var);
    return variables[var];
}

double Evaluator::evaluate() {
    return evaluate(ast);
}

double Evaluator::evaluate(const Parser::AST* node) {
    if (auto number = dynamic_cast<const Parser::Number*>(node)) {
        return evaluate_number(number);
    } else if (auto variable = dynamic_cast<const Parser::Variable*>(node)) {
        return evaluate_variable(variable);
    } else if (auto function = dynamic_cast<const Parser::Function*>(node)) {
        return evaluate_function(function);
    } else if (auto binary_op = dynamic_cast<const Parser::BinaryOp*>(node)) {
        return evaluate_binary_op(binary_op);
    }
    throw std::runtime_error("Unknown AST node type");
}

double Evaluator::evaluate_number(const Parser::Number* node) {
    return node->value;
}

double Evaluator::evaluate_variable(const Parser::Variable* node) {
    auto it = variables.find(node->name);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Undefined variable: " + node->name);
}

double Evaluator::evaluate_function(const Parser::Function* node) {
    double arg_value = evaluate(node->arg.get());
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

double Evaluator::evaluate_binary_op(const Parser::BinaryOp* node) {
    double left_value = evaluate(node->left.get());
    double right_value = evaluate(node->right.get());

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
