#include <iostream>
#include "../inc/Expression.hpp"

Expression::Expression(std::string instr, eOperandType type, std::string strType, std::string value)
	: _instr(instr), _type(type), _strType(strType), _value(value) {}
Expression::Expression(const Expression & ref) { *this = ref; }
Expression::~Expression() {}
Expression & Expression::operator=(const Expression &ref) {
	this->_instr = ref.getInstruction();
	this->_type = ref.getType();
	this->_strType = ref.getStringType();
	this->_value = ref.getValue();
	return *this;
}

std::string Expression::getInstruction() const { return this->_instr; }
eOperandType Expression::getType() const { return this->_type; }
std::string Expression::getStringType() const { return this->_strType; }
std::string Expression::getValue() const { return this->_value; }
