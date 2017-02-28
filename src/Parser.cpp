#include <iostream> // std::cin
#include <sstream> // std::stringstream, rdbuf
#include <fstream> // std::ifstream
#include <boost/lexical_cast.hpp>
#include "../inc/Exceptions.hpp"
#include "../inc/eOperandType.hpp"
#include "../inc/Parser.hpp"
#include "../inc/TGrammar.hpp"

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
	this->_parsed_expressions = ref.getParsedExpr();
	return *this;
}

void Parser::parseExprList(std::list<std::string>::const_iterator iter_begin,
std::list<std::string>::const_iterator iter_end) {
	Grammar<std::string::iterator> syntax_parser;
	std::string entry;
	int line_number = 0;
	tuples_t parsed_expressions; // vector of std::tuple(instr, value)

	for (auto iter = iter_begin; iter != iter_end; iter++) {
		entry = *iter;
		line_number++;
		std::string::iterator begin = entry.begin();
		std::string::iterator end = entry.end();
		if (!boost::spirit::qi::phrase_parse(begin, end, syntax_parser, boost::spirit::qi::blank, parsed_expressions))
			throw EntryException(EntryExceptionReasons::SyntaxError, std::string(), line_number);
	}
	for (tuples_t::iterator it = parsed_expressions.begin(); it != parsed_expressions.end(); it++) {
		std::string instr = std::get<0>(*it);
		std::string type = std::get<1>(*it) ? boost::get<std::string>(std::get<1>(*it)) : std::string();
		std::string value = std::get<2>(*it) ? boost::get<std::string>(std::get<2>(*it)) : std::string();

		eOperandType eType;
		try {
			eType = this->_getType(type, value);
		} catch (std::exception e) {
			// rethrow exception with a personnalised message
			throw EntryException(EntryExceptionReasons::InvalidValue, value, line_number);
		}
		this->_parsed_expressions.push_back(Expression(instr, eType, type, value));
	}
}

// return eOperandType associated with string `type`, throws error if wrong value
eOperandType Parser::_getType(std::string type, std::string value) {
	if (type == "int8") {
		int int8 = boost::lexical_cast<int>(value);
		if(int8 < std::numeric_limits<int8_t>::min()
				|| int8 > std::numeric_limits<int8_t>::max())
			throw std::length_error("Int8 value is out of range");
		return eOperandType::Int8;
	} else if (type == "int16") {
		boost::lexical_cast<short>(value);
		return eOperandType::Int16;
	} else if (type == "int32") {
		boost::lexical_cast<int>(value);
		return eOperandType::Int32;
	} else if (type == "float") {
		boost::lexical_cast<float>(value);
		return eOperandType::Float;
	} else if (type == "double") {
		boost::lexical_cast<double>(value);
	}
	return eOperandType::Double;
}

void Parser::semanticCheck() {
	int line_number = 0;
	int exit_instr_count = 0;
	std::vector<Expression>::iterator end = this->_parsed_expressions.end();

	if (this->flagVerbose()) {
		std::cout << "found entries:" << std::endl;
		std::cout << "--------------------------------" << std::endl;
	}
	for (std::vector<Expression>::iterator it = this->_parsed_expressions.begin(); it != end; ++it)
	{
		line_number++;
		std::string instr = (*it).getInstruction();
		std::string type = (*it).getStringType();
		std::string value = (*it).getValue();
		if (this->flagVerbose()) {
			std::cout << instr;
			if (!type.empty() && !value.empty())
				std::cout << ": " << type << " " << value;
			std::cout << std::endl;
		}
		if (instr == "exit")
			exit_instr_count++;
		// check unexpected value/type
		try {
			if ((instr.compare("push") != 0 && instr.compare("assert") != 0)
					&& (!type.empty() || !value.empty())) {
				throw EntryException(EntryExceptionReasons::UnexpectedIdentifier, instr, line_number);
			} else if (instr.compare("push") == 0 || instr.compare("assert") == 0) {
				// check for lack of type/value
				if (type.empty()) {
					throw EntryException(EntryExceptionReasons::TypeExpected, instr, line_number);
				} else if (value.empty()) {
					throw EntryException(EntryExceptionReasons::ValueExpected, value, line_number);
				}
			}
		} catch(const std::exception & e) {
			std::cerr << e.what() << std::endl;
		}
	}
	if (this->flagVerbose())
		std::cout << "--------------------------------" << std::endl;
	if (exit_instr_count < 1)
		throw EntryException(EntryExceptionReasons::InstrExpected, "exit", line_number);
	else if (exit_instr_count > 1)
		throw EntryException(EntryExceptionReasons::UnexpectedIdentifier, "exit", line_number);
}
std::list<std::string> Parser::getExprList() const { return this->_exprList; }
std::vector<Expression> Parser::getParsedExpr() const { return this->_parsed_expressions; }
bool Parser::flagVerbose() const { return this->_verbose; }
void Parser::setVerbose(bool flag) { this->_verbose = flag; }