#include <iostream> // std::cin
#include <sstream> // std::stringstream, rdbuf
#include <fstream> // std::ifstream
#include "../inc/Parser.hpp"
#include "../inc/Grammar.hpp"

using namespace boost::spirit;

Parser::Parser() {
	for(std::string line; std::getline(std::cin, line);) {
		if (!line.compare(";;"))
			break;
		this->_exprList.push_back(line + '\n');
	}
}
Parser::Parser(std::string file) {
	std::ifstream in(file);
	for (std::string line; std::getline(in, line);) {
		this->_exprList.push_back(line + '\n');
	}
}
Parser::Parser(const Parser & ref) { *this = ref; }
Parser::~Parser() {}
Parser & Parser::operator=(const Parser &ref) {
	this->_exprList = ref.getExprList();
	return *this;
}

bool Parser::parseExprList(std::list<std::string>::iterator iter_begin,
std::list<std::string>::iterator iter_end) {
	std::string entry;
	Grammar<std::string::iterator> syntax_parser;

	int i = 0;
	bool success = true;
	for (auto iter = iter_begin; iter != iter_end; iter++) {
		entry = *iter;
		i++;
		std::string::iterator begin = entry.begin();
		std::string::iterator end = entry.end();
	  if (!qi::phrase_parse(begin, end, syntax_parser, qi::blank, this->_instr_value_array)) {
			success = false;
			std::cout << "Syntax error line ";
			std::cout << i;
			std::cout << std::endl;
    }
	}
	std::cout << "found entries:" << std::endl;
	std::cout << "--------------------------------" << std::endl;
	pairs_t::iterator end = this->_instr_value_array.end();
	for (pairs_t::iterator it = this->_instr_value_array.begin(); it != end; ++it)
	{
		std::cout << (*it).first;
		if ((*it).second)
			std::cout << ": " << boost::get<std::string>((*it).second);
		std::cout << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
	return success;
}
std::list<std::string> Parser::getExprList() const { return this->_exprList; }