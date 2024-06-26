#pragma once

#include "lexer.hpp"
#include <memory>

/*
	BNF grammar for Calculator:
	<expression> ::= <term> | <term> "+" <expression> | <term> "-" <expression>
	<term>       ::= <factor> | "!" <factor> | <factor> "*" <term> | <factor> "/" <term>
	<factor>     ::= <number> | <variable> | <function> | <paren-open> <expression> <paren-close>
	<function>   ::= <fun-identifier> <paren-open> <expression> <paren-close>
	<fun-identifier> ::= "sin" | "cos" 
	<number>     ::= NUMBER
	<paren-open> ::= PAREN_OPEN | PAREN_BRACE_OPEN | PAREN_CURLY_OPEN
	<paren-close> ::= PAREN_CLOSE | PAREN_BRACE_CLOSE | PAREN_CURLY_CLOSE
*/

namespace calc {

class Parser {
public:
    class AST {
    public:
        virtual ~AST() = default;
    };

    class Number : public AST {
    public:
        double value;
        explicit Number(double value) : value(value) {}
    };

    class Variable : public AST {
    public:
        std::string name;
        explicit Variable(const std::string& name) : name(name) {}
    };

    class Function : public AST {
    public:
        std::string name;
        std::unique_ptr<AST> arg;
        Function(const std::string& name, std::unique_ptr<AST> arg) : name(name), arg(std::move(arg)) {}
    };

    class BinaryOp : public AST {
    public:
        std::unique_ptr<AST> left;
        std::unique_ptr<AST> right;
        Lexer::Token::TokenType op;
        BinaryOp(std::unique_ptr<AST> left, std::unique_ptr<AST> right, Lexer::Token::TokenType op)
            : left(std::move(left)), right(std::move(right)), op(op) {}
    };

    explicit Parser(const std::vector<Lexer::Token>& tokens) : tokens(tokens), currentToken(tokens.begin()) {}

    std::unique_ptr<AST> parse();

private:
    const std::vector<Lexer::Token>& tokens;
	using tokenIt_t = std::vector<Lexer::Token>::const_iterator;
    tokenIt_t currentToken;
    tokenIt_t savedToken;

    std::unique_ptr<AST> parse_expression();
    std::unique_ptr<AST> parse_term();
    std::unique_ptr<AST> parse_factor();

    Lexer::Token::TokenType getTokenType() const;
    void advance();
    bool match(Lexer::Token::TokenType type);
    void expect(Lexer::Token::TokenType type);
};

} // namespace calc
