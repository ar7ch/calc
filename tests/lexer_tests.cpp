#include "lexer.hpp"  // Include the lexer header file
#include <gtest/gtest.h>

TEST(LexerTest, TokenizeSingleNumber) {
    using namespace calc;
    std::string token_str = "42";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "42", 42},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 2);  // One for the number, one for the END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeFloatingPointNumber) {
    using namespace calc;
    std::string token_str = "3.14";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "3.14", 3.14},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 2);  // One for the number, one for the END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeInvalidNumber) {
    using namespace calc;
    std::string token_str = "1.23.45";
    Lexer lexer{token_str};
    EXPECT_THROW(lexer.tokenize(), std::runtime_error);
}

TEST(LexerTest, TokenizeSimpleAddition) {
    using namespace calc;
    std::string token_str = "1+2";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 4);  // Two numbers, one plus, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeSimpleSubtraction) {
    using namespace calc;
    std::string token_str = "1-2";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::MINUS},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 4);  // Two numbers, one minus, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeSimpleMultiplication) {
    using namespace calc;
    std::string token_str = "1*2";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::MUL},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 4);  // Two numbers, one times, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeSimpleDivision) {
    using namespace calc;
    std::string token_str = "1/2";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::DIV},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 4);  // Two numbers, one divide, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeFunction) {
    using namespace calc;
    std::string token_str = "sin(x)";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::FUNCTION, "sin"},
        {Lexer::Token::TokenType::LPAREN},
        {Lexer::Token::TokenType::VARIABLE, "x"},
        {Lexer::Token::TokenType::RPAREN},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 5);  // Four tokens for the function call, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeCurlyBraces) {
    using namespace calc;
    std::string token_str = "{1+2}";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::LPAREN_CURLY},
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::RPAREN_CURLY},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 6);  // Five tokens for the expression, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeSquareBrackets) {
    using namespace calc;
    std::string token_str = "[1+2]";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::LPAREN_BRACE},
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::RPAREN_BRACE},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 6);  // Five tokens for the expression, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeParentheses) {
    using namespace calc;
    std::string token_str = "(1+2)";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::LPAREN},
        {Lexer::Token::TokenType::NUMBER, "1", 1},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::RPAREN},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 6);  // Five tokens for the expression, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeComplexExpression) {
    using namespace calc;
    std::string token_str = "2 * (3 + 4) / 5";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::MUL},
        {Lexer::Token::TokenType::LPAREN},
        {Lexer::Token::TokenType::NUMBER, "3", 3},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "4", 4},
        {Lexer::Token::TokenType::RPAREN},
        {Lexer::Token::TokenType::DIV},
        {Lexer::Token::TokenType::NUMBER, "5", 5},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 10);  // Nine tokens for the expression, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeComplexExpressionWithCurlyBraces) {
    using namespace calc;
    std::string token_str = "2 * (3 + 4) / {5+9}";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::NUMBER, "2", 2},
        {Lexer::Token::TokenType::MUL},
        {Lexer::Token::TokenType::LPAREN},
        {Lexer::Token::TokenType::NUMBER, "3", 3},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "4", 4},
        {Lexer::Token::TokenType::RPAREN},
        {Lexer::Token::TokenType::DIV},
        {Lexer::Token::TokenType::LPAREN_CURLY},
        {Lexer::Token::TokenType::NUMBER, "5", 5},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::NUMBER, "9", 9},
        {Lexer::Token::TokenType::RPAREN_CURLY},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 14);  // Thirteen tokens for the expression, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}

TEST(LexerTest, TokenizeComplexFunctionExpressions) {
    using namespace calc;
    std::string token_str = "sin(x) + cos(y)";
    Lexer lexer{token_str};
    Lexer::tokenstream_t tokens = lexer.tokenize();
    Lexer::tokenstream_t expected_tokenization{
        {Lexer::Token::TokenType::FUNCTION, "sin"},
        {Lexer::Token::TokenType::LPAREN},
        {Lexer::Token::TokenType::VARIABLE, "x"},
        {Lexer::Token::TokenType::RPAREN},
        {Lexer::Token::TokenType::PLUS},
        {Lexer::Token::TokenType::FUNCTION, "cos"},
        {Lexer::Token::TokenType::LPAREN},
        {Lexer::Token::TokenType::VARIABLE, "y"},
        {Lexer::Token::TokenType::RPAREN},
        {Lexer::Token::TokenType::END}
    };
    ASSERT_EQ(tokens.size(), 10);  // Nine tokens for the expression, one END token
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].type, expected_tokenization[i].type);
        EXPECT_EQ(tokens[i].text, expected_tokenization[i].text);
        EXPECT_EQ(tokens[i].value, expected_tokenization[i].value);
    }
}
