#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "evaluator.hpp"

int main()
{
	std::string input = "1 + 2";
	calc::Lexer lexer(input);
	auto tokens = lexer.tokenize();
	calc::Parser parser{tokens};
	auto ast = parser.parse();

	for (const auto& token : tokens) {
		std::cout << token.value << std::endl;
	}
	calc::Evaluator evaluator;
	double result = evaluator.evaluate(ast.get());
	std::cout << result << std::endl;

	return 0;
}
