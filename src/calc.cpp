#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

int main()
{
	std::string input = "1 + 2";
	calc::Lexer lexer(input);
	auto tokens = lexer.tokenize();
	calc::Parser parser{tokens};
	parser.parse();

	for (const auto& token : tokens) {
		std::cout << token.value << std::endl;
	}

	return 0;
}
