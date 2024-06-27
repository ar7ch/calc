#pragma once

#include "evaluator.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <string>

namespace calc {

class Calculator {
public:
    using raw_variable_map_t = Evaluator::raw_variable_map_t;

    static double evaluate(const std::string& expression, const raw_variable_map_t& variables = {});
};

} // namespace calc
