#include <iostream> // std::cin
#include <sstream> // std::stringstream, rdbuf
#include <fstream> // std::ifstream
#include <stdint.h>
#include <boost/lexical_cast.hpp>
#include <map>
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

bool Parser::parseExprList(std::list<std::string>::const_iterator iter_begin,
std::list<std::string>::const_iterator iter_end) {
	std::string entry;
	Grammar<std::string::iterator> syntax_parser;

	int line_number = 0;
	bool success = true;
	for (auto iter = iter_begin; iter != iter_end; iter++) {
		entry = *iter;
		line_number++;
		std::string::iterator begin = entry.begin();
		std::string::iterator end = entry.end();
	  if (!qi::phrase_parse(begin, end, syntax_parser, qi::blank, this->_instr_value_array)) {
			success = false;
			std::cout << "Syntax error line ";
			std::cout << line_number;
			std::cout << std::endl;
    }
	}
	std::cout << "found entries:" << std::endl;
	std::cout << "--------------------------------" << std::endl;
	tuples_t::const_iterator end = this->_instr_value_array.end();
	for (tuples_t::const_iterator it = this->_instr_value_array.begin(); it != end; ++it)
	{
		std::cout << std::get<0>(*it);
		if (std::get<1>(*it)) {
			std::cout << ": " << boost::get<std::string>(std::get<1>(*it)) << " " << boost::get<std::string>(std::get<2>(*it));
		}
		std::cout << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
	return success;
}

bool Parser::_checkValue(std::string type, std::string value) {
	bool success = true;

	if (type == "int8") {
		try {
			boost::lexical_cast<int8_t>(value);
		} catch (const boost::bad_lexical_cast &e) {
			success = false;
		}
	} else if (type == "int16") {
		try {
			boost::lexical_cast<short>(value);
		} catch (const boost::bad_lexical_cast &e) {
			success = false;
		}
	} else if (type == "int32") {
		try {
			boost::lexical_cast<int>(value);
		} catch (const boost::bad_lexical_cast &e) {
			success = false;
		}
	} else if (type == "float") {
		try {
			boost::lexical_cast<float>(value);
		} catch (const boost::bad_lexical_cast &e) {
			success = false;
		}
	} else if (type == "double") {
		try {
			boost::lexical_cast<double>(value);
		} catch (const boost::bad_lexical_cast &e) {
			success = false;
		}
	}
	return success;
}

bool Parser::semanticCheck() {
	int line_number = 0;
	bool success = true;

	tuples_t::iterator end = this->_instr_value_array.end();
	for (tuples_t::iterator it = this->_instr_value_array.begin(); it != end; ++it)
	{
		line_number++;

		// check unexpected value/type
		if ((std::get<0>(*it).compare("push") != 0 && std::get<0>(*it).compare("assert") != 0)
		&& (std::get<1>(*it) || std::get<2>(*it))) {
			std::cout << "Unexpected value for `" << std::get<0>(*it) << "` instruction at line ";
			std::cout << line_number;
			std::cout << std::endl;
			success = false;
		} else if (std::get<0>(*it).compare("push") == 0 || std::get<0>(*it).compare("assert") == 0) {
			// check for lack of type/value
			if (!std::get<1>(*it)) {
				success = false;
				std::cout << "Type expected for `" << std::get<0>(*it) << "` instruction at line " << std::endl;
				std::cout << line_number;
				std::cout << std::endl;
			} else if (!std::get<2>(*it)) {
				success = false;
				std::cout << "Value expected for `" << std::get<0>(*it) << "` instruction at line " << std::endl;
				std::cout << line_number;
				std::cout << std::endl;
			}

			// check for value's rightness and overflow/underflow
			std::string type = boost::get<std::string>(std::get<1>(*it));
			std::string value = boost::get<std::string>(std::get<2>(*it));
			if (!this->_checkValue(type, value)) {
				success = false;
				std::cout << "Value `" << value << "` could not be interpreted as type at line ";
				std::cout << line_number;
				std::cout << std::endl;
			}
		}
	}
	return success;
}
std::list<std::string> Parser::getExprList() const { return this->_exprList; }