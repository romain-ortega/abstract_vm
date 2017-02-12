#include <iostream>
#include <list>
#include "../inc/Parser.hpp"
#include "../inc/Grammar.hpp"
#include "../inc/Skipper.hpp"

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
	std::list<std::string>::iterator iter_begin = list.begin();
	std::list<std::string>::iterator iter_end = list.end();
	// bool r = avm->parseInstructionList(iter_begin, iter_end, list);

	std::string entry;
	skipper<std::string::iterator> skip_parser;
	instrValue<std::string::iterator> parser;

	for (auto iter = iter_begin; iter != iter_end; iter++) {
		entry = *iter;
		std::string::iterator begin = entry.begin();
		std::string::iterator end = entry.end();
	  if (!qi::phrase_parse(begin, end, parser, skip_parser, parser.instr_value)) {
			std::cout << "-------------------------------- \n";
			std::cout << "Parsing failed\n";
			std::cout << "-------------------------------- \n";
    }
    else {
			std::cout << "-------------------------------- \n";
			std::cout << "Parsing succeeded, found entries:\n";
			pairs_type::iterator end = parser.instr_value.end();
			for (pairs_type::iterator it = parser.instr_value.begin(); it != end; ++it)
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