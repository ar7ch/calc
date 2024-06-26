#include "parser.hpp"
#include <stdexcept>

namespace calc {

Lexer::Token::TokenType Parser::getTokenType() const {
    if (currentToken != tokens.end()) {
        return currentToken->type;
    }
    return Lexer::Token::TokenType::END;
}

void Parser::advance() {
    if (currentToken != tokens.end()) {
        ++currentToken;
    }
}

bool Parser::match(Lexer::Token::TokenType type) {
    if (getTokenType() == type) {
		savedToken = currentToken;
		advance();
        return true;
    }
    return false;
}

void Parser::expect(Lexer::Token::TokenType type) {
    if (!match(type)) {
        throw std::runtime_error("Unexpected token");
    }
}

std::unique_ptr<Parser::AST> Parser::parse() {
    return parse_expression();
}

std::unique_ptr<Parser::AST> Parser::parse_expression() {
    auto left = parse_term();
    while (getTokenType() == Lexer::Token::TokenType::PLUS || getTokenType() == Lexer::Token::TokenType::MINUS) {
        auto op = getTokenType();
        advance();
        auto right = parse_term();
        left = std::make_unique<BinaryOp>(std::move(left), std::move(right), op);
    }
    return left;
}

std::unique_ptr<Parser::AST> Parser::parse_term() {
    auto left = parse_factor();
    while (getTokenType() == Lexer::Token::TokenType::MUL || getTokenType() == Lexer::Token::TokenType::DIV) {
        auto op = getTokenType();
        advance();
        auto right = parse_factor();
        left = std::make_unique<BinaryOp>(std::move(left), std::move(right), op);
    }
    return left;
}

std::unique_ptr<Parser::AST> Parser::parse_factor() {
    if (match(Lexer::Token::TokenType::NEG)) {
        auto factor = parse_factor();
        return std::make_unique<BinaryOp>(std::make_unique<Number>(0), std::move(factor), Lexer::Token::TokenType::MINUS);
    } else if (match(Lexer::Token::TokenType::NUMBER)) {
		return std::make_unique<Number>(savedToken->value);
    } else if (match(Lexer::Token::TokenType::VARIABLE)) {
        return std::make_unique<Variable>(savedToken->text);
    } else if (match(Lexer::Token::TokenType::FUNCTION)) {
        auto func_name = savedToken->text;
        expect(Lexer::Token::TokenType::LPAREN);
        auto arg = parse_expression();
        expect(Lexer::Token::TokenType::RPAREN);
        return std::make_unique<Function>(func_name, std::move(arg));
    } else if (match(Lexer::Token::TokenType::LPAREN)) {
        auto expr = parse_expression();
        expect(Lexer::Token::TokenType::RPAREN);
        return expr;
    } else if (match(Lexer::Token::TokenType::LPAREN_CURLY)) {
        auto expr = parse_expression();
        expect(Lexer::Token::TokenType::RPAREN_CURLY);
        return expr;
    } else if (match(Lexer::Token::TokenType::LPAREN_BRACE)) {
        auto expr = parse_expression();
        expect(Lexer::Token::TokenType::RPAREN_BRACE);
        return expr;
    }
    throw std::runtime_error("Unexpected token");
}

} // namespace calc
