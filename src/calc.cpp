#include "calc.hpp"

namespace calc {

double Calculator::evaluate(const std::string& expression, const variable_map_t& variables) {
    Lexer lexer(expression);
    auto tokens = lexer.tokenize();
    Parser parser(tokens);
    auto ast = parser.parse();
    Evaluator evaluator;
    return evaluator.evaluate(ast.get(), variables);
}

} // namespace calc
