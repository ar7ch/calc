#include "lexer.hpp"
#include <cctype>
#include <stdexcept>
#include <set>
#include <sstream>
#include <iostream>

namespace calc {

const std::unordered_map<char, Lexer::Token::TokenType> Lexer::char2tok = {
    {'+', Token::TokenType::PLUS},
    {'-', Token::TokenType::MINUS},
    {'*', Token::TokenType::MUL},
    {'/', Token::TokenType::DIV},
    {'(', Token::TokenType::LPAREN},
    {')', Token::TokenType::RPAREN},
    {'{', Token::TokenType::LPAREN_CURLY},
    {'}', Token::TokenType::RPAREN_CURLY},
    {'[', Token::TokenType::LPAREN_BRACE},
    {']', Token::TokenType::RPAREN_BRACE},
    {'!', Token::TokenType::NEG}
};

inline char Lexer::getchar() {
    if (pos < expression.size()) {
		return expression[pos++];
	} else {
		return '\0';
	}
}

inline void Lexer::ungetchar() {
	if (pos > 0) {
		--pos;
	}
}

inline char Lexer::peekchar() const {
	if (pos < expression.size()) {
		return expression[pos];
	} else {
		return '\0';
	}
}

Lexer::tokenstream_t Lexer::tokenize() {
    tokenstream_t tokens;
    char current_char;
    while ((current_char = getchar()) != '\0') {
        if (std::isdigit(current_char) || 
				(current_char == decimal_point && std::isdigit(peekchar()))) {
            std::stringstream number_str;
            bool got_point = (current_char == decimal_point);
            number_str << current_char;

            while ((current_char = getchar()) != '\0' && 
					(std::isdigit(current_char) || (current_char == decimal_point && !got_point))) {
                got_point = got_point || (current_char == decimal_point); // one way turning on
                number_str << current_char;
            }

            if (current_char == '.') {
                throw std::runtime_error("Invalid number format");
            }
			if (current_char != '\0' && !std::isdigit(current_char)) {
				ungetchar();
			}
            tokens.emplace_back(Token::TokenType::NUMBER, number_str.str(), std::stod(number_str.str()));
        } else if (std::isalpha(current_char)) {
            std::stringstream name;
            name << current_char;

            while ((current_char = getchar()) != '\0' && std::isalpha(current_char)) {
                name << current_char;
            }

			if (current_char != '\0' && !std::isalpha(current_char)) {
				ungetchar();
			}

            std::string name_str = name.str();
            if (is_function(name_str)) {
                tokens.emplace_back(Token::TokenType::FUNCTION, name_str);
            } else {
                tokens.emplace_back(Token::TokenType::VARIABLE, name_str);
            }
        } else {
            auto it = char2tok.find(current_char);
            if (it != char2tok.end()) {
                tokens.emplace_back(it->second);
            } else {
                throw std::runtime_error("Unexpected character in input: " + std::string(1, current_char));
            }
        }
    }

    tokens.emplace_back(Token::TokenType::END);
    return tokens;
}

bool Lexer::is_function(const std::string& str) {
    static const std::set<std::string> functions = { "sin", "cos", "tan", "log" };
    return functions.find(str) != functions.end();
}

} // namespace calc
