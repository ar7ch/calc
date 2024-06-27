#include "evaluator.hpp"
#include "parser.hpp"
#include "lexer.hpp"
#include <gtest/gtest.h>

TEST(EvaluatorTest, EvaluateSingleNumber) {
    using namespace calc;
    std::string input = "42";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    double result = evaluator.evaluate(ast.get());
    EXPECT_EQ(result, 42);
}

TEST(EvaluatorTest, EvaluateAddition) {
    using namespace calc;
    std::string input = "1+2";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    double result = evaluator.evaluate(ast.get());
    EXPECT_EQ(result, 3);
}

TEST(EvaluatorTest, EvaluateMultiplication) {
    using namespace calc;
    std::string input = "2*3";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    double result = evaluator.evaluate(ast.get());
    EXPECT_EQ(result, 6);
}

TEST(EvaluatorTest, EvaluateDivision) {
    using namespace calc;
    std::string input = "6/2";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    double result = evaluator.evaluate(ast.get());
    EXPECT_EQ(result, 3);
}

TEST(EvaluatorTest, EvaluateFunction) {
    using namespace calc;
    std::string input = "sin(0)";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    double result = evaluator.evaluate(ast.get());
    EXPECT_EQ(result, 0);
}

TEST(EvaluatorTest, EvaluateVariables) {
    using namespace calc;
    std::string input = "x + y";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    Evaluator::variable_map_t variables = {{"x", 3}, {"y", 4}};
    double result = evaluator.evaluate(ast.get(), variables);
    EXPECT_EQ(result, 7);
}

TEST(EvaluatorTest, EvaluateComplexExpression) {
    using namespace calc;
    std::string input = "2 * (3 + 4) / {0.5 * 4}";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator;
    double result = evaluator.evaluate(ast.get());
    EXPECT_EQ(result, 7);
}
