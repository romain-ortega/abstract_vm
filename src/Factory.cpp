#include <iostream>
#include "../inc/Factory.hpp"
#include "../inc/TOperand.hpp"
Factory::FP Factory::create = {
	&Factory::createInt8,
	&Factory::createInt16,
	&Factory::createInt32,
	&Factory::createFloat,
	&Factory::createDouble
};
IOperand const *Factory::createOperand(eOperandType type, std::string const & value) const {
	return (this->*create[type])(value);
}
IOperand const *Factory::createInt8(std::string const & value) const {
	return new Operand<int8_t>(eOperandType::Int8, value);
}
IOperand const *Factory::createInt16(std::string const & value) const {
	return new Operand<int16_t>(eOperandType::Int16, value);
}
IOperand const *Factory::createInt32(std::string const & value) const {
	return new Operand<int>(eOperandType::Int32, value);
}
IOperand const *Factory::createFloat(std::string const & value) const {
	return new Operand<float>(eOperandType::Float, value);
}
IOperand const *Factory::createDouble(std::string const & value) const {
	return new Operand<double>(eOperandType::Float, value);
}
