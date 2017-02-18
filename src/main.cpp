#include <iostream>
#include <list>
#include "../inc/Parser.hpp"
#include "../inc/Grammar.hpp"

int main(int argc, char *argv[])
{
	Parser *avm;

	if (argc > 1) {
		if (argc > 2)
			std::cout << "Usage: ./abstract_vm [filanme (or read stdin)]" << std::endl;
		avm = new Parser(argv[1]);
	} else {
		avm = new Parser();
	}

	std::list<std::string> list = avm->getExprList();
	std::list<std::string>::iterator iter_begin = list.begin();
	std::list<std::string>::iterator iter_end = list.end();

	std::string entry;
	Grammar<std::string::iterator> syntax_parser;
	pairs_t instr_value_array;

	for (auto iter = iter_begin; iter != iter_end; iter++) {
		entry = *iter;
		std::string::iterator begin = entry.begin();
		std::string::iterator end = entry.end();
	  if (!qi::phrase_parse(begin, end, syntax_parser, qi::blank, instr_value_array)) {
			std::cout << "-------------------------------- \n";
			std::cout << "Parsing failed\n";
			std::cout << "-------------------------------- \n";
    }
    else {
			std::cout << "-------------------------------- \n";
			std::cout << "Parsing succeeded, found entries:\n";
			pairs_t::iterator end = instr_value_array.end();
			for (pairs_t::iterator it = instr_value_array.begin(); it != end; ++it)
			{
				std::cout << (*it).first;
				if ((*it).second)
					std::cout << "=" << boost::get<std::string>((*it).second);
				std::cout << std::endl;
			}
			std::cout << "---------------------------------\n";
		}
	}
	delete avm;
	return 0;
}