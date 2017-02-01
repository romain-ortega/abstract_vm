#include <iostream>
#include "../inc/Factory.hpp"
#include "../inc/TOperand.hpp"

Factory::Factory() {}
Factory::Factory(const Factory & ref) { *this = ref; }
Factory::~Factory() {}
Factory & Factory::operator=(const Factory &ref) {
	return *this;
}
IOperand const * Factory::createOperand(eOperandType type, std::string const & value) const {
}
IOperand const * Factory::createInt8(std::string const & value) const {
	return new Operand<int8_t>(eOperandType::Int8, value);
}
IOperand const * Factory::createInt16(std::string const & value) const {
	return new Operand<int16_t>(eOperandType::Int16, value);
}
IOperand const * Factory::createInt32(std::string const & value) const {
	return new Operand<int>(eOperandType::Int32, value);
}
IOperand const * Factory::createFloat(std::string const & value) const {
	return new Operand<float>(eOperandType::Float, value);
}
IOperand const * Factory::createDouble(std::string const & value) const {
	return new Operand<double>(eOperandType::Float, value);
}
