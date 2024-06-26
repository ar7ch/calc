#include <iostream>
#include "lexer.hpp"

int main()
{
	calc::Lexer lexer("1 + 2");
	auto tokens = lexer.tokenize();

	for (const auto& token : tokens) {
		std::cout << token.text << std::endl;
	}

	return 0;
}
