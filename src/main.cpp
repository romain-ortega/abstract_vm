#include <boost/program_options.hpp>
#include <iostream>
#include <list>
#include "../inc/CallStack.hpp"
#include "../inc/Parser.hpp"
#include "../inc/Exceptions.hpp"

namespace po = boost::program_options;
static Parser *parse_opt(int argc, char *argv[]) {
	std::string file;
	bool verbose = false;
	Parser *parser;

	try {
		po::options_description desc("Allowed options");
		desc.add_options() //option, parameter, description
			("help,h", "print usage message")
			("file,f", po::value(&file), "pathname of avm file")
			("verbose,v", po::bool_switch(&verbose), "verbose execution")
		;

		po::variables_map vm;
		po::store(po::parse_command_line(argc, argv, desc), vm);
		po::notify(vm);

		if (vm.count("help")) {
			std::cout << desc;
			exit(0);
		}
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
		exit(1);
	}
	if (file.empty())
		parser = new Parser();
	else {
		parser = new Parser(file);
	}
	parser->setVerbose(verbose);
	return parser;
}

int main(int argc, char *argv[]) {
	Parser *parser = parse_opt(argc, argv);

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

	CallStack call_stack(parser->getParsedExpr());
	try {
		call_stack.run();
	} catch (StackException e) {
		std::cerr << e.what() << std::endl;
	}

	delete parser;
	return 0;
}