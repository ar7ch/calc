#pragma once

#include "evaluator.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <string>

namespace calc {

class Calculator {
public:
    using variable_map_t = Evaluator::variable_map_t;

    static double evaluate(const std::string& expression, const variable_map_t& variables = {});
};

} // namespace calc
