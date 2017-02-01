#include <iostream>
#include <list>
#include "../inc/Lexer.hpp"

int main(int argc, char *argv[])
{
	Lexer *avm;

	if (argc > 1) {
		if (argc > 2)
			std::cout << "Usage: ./abstract_vm [filanme (or read stdin)]" << std::endl << std::endl;
		avm = new Lexer(argv[1]);
	} else {
		avm = new Lexer();
	}

	std::list<std::string> list = avm->getInstructionsList();
	for (std::list<std::string>::iterator iter = list.begin(); iter != list.end(); iter++)
		std::cout << *iter << std::endl;

	delete avm;
	return 0;
}