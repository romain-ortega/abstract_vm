#include <iostream>
#include <list>
#include "../inc/CallStack.hpp"
#include "../inc/Parser.hpp"
#include "../inc/Exceptions.hpp"

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

	try {
		parser->parseExprList(iter_begin, iter_end);
	} catch (EntryException e) {
		std::cerr << e.what() << std::endl;
		return 1; // syntax error
	}
	try {
		parser->semanticCheck();
	} catch (EntryException e) {
		std::cerr << e.what() << std::endl;
		return 2; // semantic error
	}

	CallStack call_stack(parser->Parser::getParsedExpr());
	try {
		call_stack.run();
	} catch (StackException e) {
		std::cerr << e.what() << std::endl;
	}

	delete parser;
	return 0;
}