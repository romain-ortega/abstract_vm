#include <iostream>
#include <list>
#include "../inc/Parser.hpp"

int main(int argc, char *argv[])
{
	Parser *avm;

	if (argc > 1) {
		if (argc > 2)
			std::cout << "Usage: ./abstract_vm [filanme (or read stdin)]" << std::endl << std::endl;
		avm = new Parser(argv[1]);
	} else {
		avm = new Parser();
	}

	std::list<std::string> list = avm->getInstructionsList();
	for (std::list<std::string>::iterator iter = list.begin(); iter != list.end(); iter++) {
		std::cout << *iter << std::endl;
		if (!avm->parseLine(*iter))
			break;
	}

	delete avm;
	return 0;
}