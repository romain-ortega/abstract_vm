#include <iostream>
#include <list>
#include "../inc/Parser.hpp"
#include "../inc/Grammar.hpp"

int main(int argc, char *argv[]) {
	Parser *avm;
	int error = 0;

	if (argc > 1) {
		if (argc > 2)
			std::cout << "Usage: ./abstract_vm [filanme (or read stdin)]" << std::endl;
		avm = new Parser(argv[1]);
	} else {
		avm = new Parser();
	}

	std::list<std::string> expr_list = avm->getExprList();
	std::list<std::string>::iterator iter_begin = expr_list.begin();
	std::list<std::string>::iterator iter_end = expr_list.end();

	if (!avm->parseExprList(iter_begin, iter_end))
		error += 1;

	delete avm;
	return error;
}