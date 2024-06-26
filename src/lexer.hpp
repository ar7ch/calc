#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

namespace calc {

class Lexer {
public:
    class Token {
    public:
        enum struct TokenType {
            NUMBER,
            LPAREN, RPAREN,
            LPAREN_BRACE, RPAREN_BRACE,
            LPAREN_CURLY, RPAREN_CURLY,
            PLUS, MINUS, MUL, DIV, POW, // binary arithmetic operators
            NEG, // unary arithmetic operators
            FUNCTION,
			VARIABLE,
            END // end of input
        };

        Token(TokenType type, const std::string& text = "", double value = 0)
            : type(type), text(text), value(value) {}

        TokenType type;
        std::string text;
        double value;
    };

    using tokenstream_t = std::vector<Token>;

    Lexer(const std::string& expression) : pos(0) {
		std::stringstream ss;
		for (const auto& c : expression) {
			if (std::isspace(c)) continue;
			ss << c;
		}
		this->expression = std::move(ss.str());
	}

    tokenstream_t tokenize();

private:
	static const char decimal_point = '.';
    std::string expression;
    size_t pos;

    static const std::unordered_map<char, Token::TokenType> char2tok;
    inline char getchar();
	inline void ungetchar();
	inline char peekchar() const;
    static bool is_function(const std::string& str);
};

} // namespace calc
