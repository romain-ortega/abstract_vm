#include <iostream> // std::cin
#include <sstream> // std::stringstream, rdbuf
#include <fstream> // std::ifstream
#include "../inc/Parser.hpp"
#include "../inc/Grammar.hpp"

using namespace boost::spirit;

Parser::Parser() {
	for(std::string line; std::getline(std::cin, line);) {
		if (!line.compare(";;")) {
			break;
		}
		this->_instrList.push_back(line);
	}
}
Parser::Parser(std::string file) {
	std::ifstream in(file);
	for (std::string line; std::getline(in, line);) {
		this->_instrList.push_back(line);
	}
}
Parser::Parser(const Parser & ref) { *this = ref; }
Parser::~Parser() {}
Parser & Parser::operator=(const Parser &ref) {
	this->_instrList = ref.getInstructionsList();
	return *this;
}

std::list<std::string> Parser::getInstructionsList() const { return this->_instrList; }