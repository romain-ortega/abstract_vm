#ifndef TOPERAND_H
#define TOPERAND_H
# include <iostream>
# include <sstream>
# include <math.h> // fmod
# include "IOperand.hpp"
# include "eOperandType.hpp"
# include "Exceptions.hpp"
# include "Factory.hpp"
# include <boost/lexical_cast.hpp>
template <typename T>
class Operand : virtual public IOperand
{
private:
	eOperandType _type;
	unsigned int _precision;
	T            _value = 0;
	std::string  _stringValue;

public:
	bool hasTypeInt(eOperandType first_type, eOperandType second_type) const {
		int max_type = (first_type > second_type) ? first_type : second_type;
		return (!(max_type >= eOperandType::Float));
	}

	T cast(eOperandType type, std::string const & value) {
		if (type == eOperandType::Int8) {
			return boost::numeric_cast<int8_t>(boost::lexical_cast<int>(value));
		} else if (type == eOperandType::Int16) {
			return boost::lexical_cast<short>(value);
		} else if (type == eOperandType::Int32) {
			return boost::lexical_cast<int>(value);
		} else if (type == eOperandType::Float) {
			return boost::lexical_cast<float>(value);
		} else {
			return boost::lexical_cast<double>(value);
		}
	}

	Operand<T>(eOperandType type, std::string const & value)
	: _type(type), _stringValue(value) {
		std::string s = value;
		this->_precision = type; // int value (0 -> 4)

		// remove trailing 0
		s.erase(s.find_last_not_of('0') + 1, std::string::npos);
		// remove trailing point
		if (s.back() == '.')
			s.pop_back();
		if (s.empty())
			s = "0";

		try {
			this->_value = cast(type, s.c_str());
		} catch(boost::bad_lexical_cast&) {
			throw StackException("out of range value");
		}
	};
	Operand<T>(const Operand &ref) {
		*this = ref;
	};
	virtual ~Operand<T>() {};
	Operand<T> & operator=(const Operand &ref) {
		this->_type = ref.getType();
		this->_precision = ref.getPrecision();
		this->_value = ref.getValue();
		this->_stringValue = ref.toString();
	};

	IOperand const *operator+(IOperand const & rhs) const {
		double result = static_cast<double>(stod(rhs.toString())) + this->_value;
		eOperandType precision = (rhs.getPrecision() > static_cast<int>(this->_precision)) ?
			rhs.getType() : this->_type;
		return Factory::getInstance().createOperand(precision, std::to_string(result));
	}
	IOperand const *operator-(IOperand const & rhs) const {
		double result = static_cast<double>(stod(rhs.toString())) - this->_value;
		eOperandType precision = (rhs.getPrecision() > static_cast<int>(this->_precision)) ?
			rhs.getType() : this->_type;
		return Factory::getInstance().createOperand(precision, std::to_string(result));
	}
	IOperand const *operator*(IOperand const & rhs) const {
		double result = static_cast<double>(stod(rhs.toString())) * this->_value;
		eOperandType precision = (rhs.getPrecision() > static_cast<int>(this->_precision)) ?
			rhs.getType() : this->_type;
		return Factory::getInstance().createOperand(precision, std::to_string(result));
	}
	IOperand const *operator/(IOperand const & rhs) const {
		double val = 0;
		try {
			val = boost::lexical_cast<double>(rhs.toString());
		} catch (boost::bad_lexical_cast e) {
			throw StackException("out of range value");
		}
		if (!val)
			throw StackException("Divide by zero");

		if (!this->_value)
			return Factory::getInstance().createOperand(eOperandType::Int8, std::string("0"));
		double result = static_cast<double>(stod(rhs.toString())) / this->_value;
		eOperandType precision = (rhs.getPrecision() > static_cast<int>(this->_precision)) ?
			rhs.getType() : this->_type;
		return Factory::getInstance().createOperand(precision, std::to_string(result));
	}
	IOperand const *operator%(IOperand const & rhs) const {
		if (!this->_value)
			throw StackException("Modulo by zero");

		double result = fmod(static_cast<double>(stod(rhs.toString())), this->_value);
		eOperandType precision = (rhs.getPrecision() > static_cast<int>(this->_precision)) ?
			rhs.getType() : this->_type;
		return Factory::getInstance().createOperand(precision, std::to_string(result));
	}

	std::string const & toString(void) const { return this->_stringValue; }
	eOperandType getType() const { return this->_type; }
	int getPrecision(void) const { return this->_precision; }
	T getValue() const { return this->_value; }
};
#endif /* TOPERAND_H */