#include "calc.hpp"
#include <gtest/gtest.h>

TEST(CalculatorTest, EvaluateSimpleExpression) {
    using namespace calc;
    Calculator calculator;
    double result = calculator.evaluate("1 + 2");
    EXPECT_EQ(result, 3);
}

TEST(CalculatorTest, EvaluateWithVariables) {
    using namespace calc;
    Calculator calculator;
    Calculator::raw_variable_map_t variables = {{"x", "2"}, {"y", "3"}};
    double result = calculator.evaluate("x * y + 1", variables);
	EXPECT_EQ(result, 7);
}
