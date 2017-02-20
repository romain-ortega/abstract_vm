#include <iostream>
#include <list>
#include "../inc/Parser.hpp"
#include "../inc/Grammar.hpp"

int main(int argc, char *argv[]) {
	Parser *parser;

	if (argc > 1) {
		if (argc > 2)
			std::cout << "Usage: ./abstract_vm [filanme (or read stdin)]" << std::endl;
		parser = new Parser(argv[1]); // expressions from file
	} else {
		parser = new Parser(); // expressions from stdin
	}

	std::list<std::string> expr_list = parser->getExprList();
	std::list<std::string>::const_iterator iter_begin = expr_list.begin();
	std::list<std::string>::const_iterator iter_end = expr_list.end();

	if (!parser->parseExprList(iter_begin, iter_end))
		return 1; // syntax error
	if (!parser->semanticCheck())
		return 2; // semantic error

	delete parser;
	return 0;
}