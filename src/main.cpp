#include <iostream>
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

	delete avm;
	return 0;
}