#ifndef TOPERAND_H
#define TOPERAND_H
# include <iostream>
# include "IOperand.hpp"
# include "EOperandType.hpp"
template <typename T>
class Operand : IOperand
{
private:
	eOperandType _type;
	unsigned int _precision;
	T            _value;
	std::string  _stringValue;


public:
	Operand<T>(eOperandType, std::string const & value) {
	};
	Operand<T>(const Operand &ref) {
		*this = ref;
	};
	virtual ~Operand<T>() {};
	Operand<T> & operator=(const Operand &ref) {
		this->_type = ref.getType();
	};

	IOperand const * operator+(IOperand const & rhs) {}
	IOperand const * operator-(IOperand const & rhs) {}
	IOperand const * operator*(IOperand const & rhs) {}
	IOperand const * operator/(IOperand const & rhs) {}
	IOperand const * operator%(IOperand const & rhs) {}

	std::string const & toString(void) {
		return this->_stringValue;
	}
	eOperandType getType(void) {
		return this->_type;
	}
	T getValue() const {
		return this->_value;
	}
};
#endif /* TOPERAND_H */