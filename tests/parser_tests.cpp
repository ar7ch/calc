#include "parser.hpp"
#include "lexer.hpp"
#include <gtest/gtest.h>

TEST(ParserTest, ParseSingleNumber) {
    using namespace calc;
    std::string input = "42";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    ASSERT_TRUE(dynamic_cast<Parser::Number*>(ast.get()) != nullptr);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(ast.get())->value, 42);
}

TEST(ParserTest, ParseAddition) {
    using namespace calc;
    std::string input = "1+2";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    ASSERT_TRUE(dynamic_cast<Parser::BinaryOp*>(ast.get()) != nullptr);
    auto bin_op = dynamic_cast<Parser::BinaryOp*>(ast.get());
    ASSERT_TRUE(dynamic_cast<Parser::Number*>(bin_op->left.get()) != nullptr);
    ASSERT_TRUE(dynamic_cast<Parser::Number*>(bin_op->right.get()) != nullptr);
    EXPECT_EQ(bin_op->op, Lexer::Token::TokenType::PLUS);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(bin_op->left.get())->value, 1);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(bin_op->right.get())->value, 2);
}

TEST(ParserTest, ParseMultiplication) {
    using namespace calc;
    std::string input = "2*3";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    ASSERT_TRUE(dynamic_cast<Parser::BinaryOp*>(ast.get()) != nullptr);
    auto bin_op = dynamic_cast<Parser::BinaryOp*>(ast.get());
    ASSERT_TRUE(dynamic_cast<Parser::Number*>(bin_op->left.get()) != nullptr);
    ASSERT_TRUE(dynamic_cast<Parser::Number*>(bin_op->right.get()) != nullptr);
    EXPECT_EQ(bin_op->op, Lexer::Token::TokenType::MUL);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(bin_op->left.get())->value, 2);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(bin_op->right.get())->value, 3);
}

TEST(ParserTest, ParseParentheses) {
    using namespace calc;
    std::string input = "(1+2)*3";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    ASSERT_TRUE(dynamic_cast<Parser::BinaryOp*>(ast.get()) != nullptr);
    auto bin_op = dynamic_cast<Parser::BinaryOp*>(ast.get());
    EXPECT_EQ(bin_op->op, Lexer::Token::TokenType::MUL);

    ASSERT_TRUE(dynamic_cast<Parser::BinaryOp*>(bin_op->left.get()) != nullptr);
    auto left_op = dynamic_cast<Parser::BinaryOp*>(bin_op->left.get());
    EXPECT_EQ(left_op->op, Lexer::Token::TokenType::PLUS);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(left_op->left.get())->value, 1);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(left_op->right.get())->value, 2);

    ASSERT_TRUE(dynamic_cast<Parser::Number*>(bin_op->right.get()) != nullptr);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(bin_op->right.get())->value, 3);
}

TEST(ParserTest, ParseFunction) {
    using namespace calc;
    std::string input = "sin(45)";
    Lexer lexer{input};
    auto tokens = lexer.tokenize();
    Parser parser{tokens};
    auto ast = parser.parse();
    ASSERT_TRUE(dynamic_cast<Parser::Function*>(ast.get()) != nullptr);
    auto func = dynamic_cast<Parser::Function*>(ast.get());
    EXPECT_EQ(func->name, "sin");
    ASSERT_TRUE(dynamic_cast<Parser::Number*>(func->arg.get()) != nullptr);
    EXPECT_EQ(dynamic_cast<Parser::Number*>(func->arg.get())->value, 45);
}
