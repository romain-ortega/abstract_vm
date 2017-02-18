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

std::list<std::string> Parser::getExprList() const { return this->_exprList; }