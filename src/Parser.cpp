#include <iostream> // std::cin
#include <sstream> // std::stringstream, rdbuf
#include <fstream> // std::ifstream
#include <boost/spirit/include/qi_core.hpp>
#include "../inc/Parser.hpp"
#include "../inc/Syntax.hpp"

using namespace boost::spirit;

Parser::Parser() {
	for(std::string line; std::getline(std::cin, line);) {
		if (!line.compare(";;")) {
			break;
		}
		this->_instrList.push_back(line);
	}
	this->_syntax = new Syntax();
}
Parser::Parser(std::string file) {
	std::ifstream in(file);
	for (std::string line; std::getline(in, line);) {
		this->_instrList.push_back(line);
	}
	this->_syntax = new Syntax();
}
Parser::Parser(const Parser & ref) { *this = ref; }
Parser::~Parser() {}
Parser & Parser::operator=(const Parser &ref) {
	this->_instrList = ref.getInstructionsList();
	return *this;
}

bool Parser::parseLine(std::string line) const {
	boost::spirit::parse_info<> info;
	try
	{
		info = boost::spirit::parse(line.c_str(), *_syntax, boost::spirit::blank_p);
	}
	catch( exception &e )
	{
		// TODO: Handle the error properly
		TRACE( e.what() );
		TRACE( "\n" );
	}
	return info.full;
}
std::list<std::string> Parser::getInstructionsList() const { return this->_instrList; }