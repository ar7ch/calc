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
    Evaluator evaluator{ast.get(), {}};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 42);
}

TEST(EvaluatorTest, EvaluateAddition) {
    using namespace calc;
    std::string input = "1+2";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator{ast.get(), {}};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 3);
}

TEST(EvaluatorTest, EvaluateMultiplication) {
    using namespace calc;
    std::string input = "2*3";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator{ast.get(), {}};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 6);
}

TEST(EvaluatorTest, EvaluateDivision) {
    using namespace calc;
    std::string input = "6/2";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator{ast.get(), {}};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 3);
}

TEST(EvaluatorTest, EvaluateFunction) {
    using namespace calc;
    std::string input = "sin(0)";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator evaluator{ast.get(), {}};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 0);
}

TEST(EvaluatorTest, EvaluateVariables) {
    using namespace calc;
    std::string input = "x + y";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator::raw_variable_map_t raw_variables = {{"x", "3"}, {"y", "4"}};
    Evaluator evaluator{ast.get(), raw_variables};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 7);
}

TEST(EvaluatorTest, EvaluateVariableDependencies) {
    using namespace calc;
    std::string input = "a + b";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator::raw_variable_map_t raw_variables = {{"a", "x"}, {"b", "y"}, {"x", "1"}, {"y", "2"}};
    Evaluator evaluator{ast.get(), raw_variables};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 3);
}

// TEST(EvaluatorTest, EvaluateCyclicDependency) {
//     using namespace calc;
//     std::string input = "a + b";
//     Lexer lexer{input};
//     auto tokens = lexer.tokenize();
//     Parser parser{tokens};
//     auto ast = parser.parse();
//     Evaluator::raw_variable_map_t raw_variables = {{"a", "b"}, {"b", "a"}};
//     EXPECT_THROW(Evaluator evaluator{ast.get(), raw_variables};evaluator.evaluate(), std::runtime_error);
// 	
// }

TEST(EvaluatorTest, EvaluateComplexExpressionWithVariables) {
    using namespace calc;
    std::string input = "2 * (x + 3) / y";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    Evaluator::raw_variable_map_t raw_variables = {{"x", "5"}, {"y", "4"}};
    Evaluator evaluator{ast.get(), raw_variables};
    double result = evaluator.evaluate();
    EXPECT_EQ(result, 4);
}

