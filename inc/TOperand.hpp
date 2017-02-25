#ifndef TOPERAND_H
#define TOPERAND_H
# include <iostream>
# include <sstream>
# include <math.h> // fmod
# include "IOperand.hpp"
# include "EOperandType.hpp"
# include "Exceptions.hpp"
# include "Factory.hpp"
# include <boost/lexical_cast.hpp>
template <typename T>
class Operand : virtual public IOperand
{
private:
	eOperandType _type;
	unsigned int _precision;
	T            _value;
	std::string  _stringValue;

public:
	bool needInt(eOperandType aType, eOperandType bType) const {
		int aIntType = static_cast<int>(aType);
		int bIntType = static_cast<int>(bType);
		int cIntType = (aIntType > bIntType) ? aIntType : bIntType;
		int compType = static_cast<int>(eOperandType::Float);

		return (!(cIntType >= compType));
	}
	T cast(eOperandType type, std::string const & value) {
		if (type == eOperandType::Int8) {
			int int8 = boost::lexical_cast<int>(value);
			if(int8 < std::numeric_limits<int8_t>::min()
					|| int8 > std::numeric_limits<int8_t>::max())
				throw StackException("Int8 value is out of range");
			return int8;
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
		this->_precision = type; // int value (0 -> 4)
		try {
			this->_value = cast(type, value);
		} catch(boost::bad_lexical_cast&) {
			throw StackException("Out of range value");
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
		eOperandType mostAccurate;
		std::stringstream stream;
		double val;

		if (this->getPrecision() > rhs.getPrecision())
			mostAccurate = this->getType();
		else
			mostAccurate = rhs.getType();

		stream.str(rhs.toString());
		stream >> val;

		val += this->_value;

		stream.str();
		stream.clear();
		if (this->needInt(this->getType(), rhs.getType()))
			stream << static_cast<int>(val);
		else
			stream << val;

		Factory &f = Factory::getInstance();
		const IOperand * io = f.createOperand(mostAccurate, stream.str());

		return io;
	}
	IOperand const *operator-(IOperand const & rhs) const {
		eOperandType mostAccurate;
		std::stringstream stream;
		double val;

		if (this->getPrecision() > rhs.getPrecision())
			mostAccurate = this->getType();
		else
			mostAccurate = rhs.getType();

		stream.str(rhs.toString());
		stream >> val;

		val -= this->_value;

		stream.str();
		stream.clear();
		if (this->needInt(this->getType(), rhs.getType()))
			stream << static_cast<int>(val);
		else
			stream << val;

		Factory &f = Factory::getInstance();
		const IOperand * io = f.createOperand(mostAccurate, stream.str());

		return io;
	}
	IOperand const *operator*(IOperand const & rhs) const {
		eOperandType mostAccurate;
		std::stringstream stream;
		double val;

		if (this->getPrecision() > rhs.getPrecision())
			mostAccurate = this->getType();
		else
			mostAccurate = rhs.getType();

		stream.str(rhs.toString());
		stream >> val;

		val *= this->_value;

		stream.str();
		stream.clear();
		if (this->needInt(this->getType(), rhs.getType()))
			stream << static_cast<int>(val);
		else
			stream << val;

		Factory &f = Factory::getInstance();
		const IOperand * io = f.createOperand(mostAccurate, stream.str());

		return io;
	}
	IOperand const *operator/(IOperand const & rhs) const {
		eOperandType mostAccurate;
		std::stringstream stream;
		double val;

		if (this->getPrecision() > rhs.getPrecision())
			mostAccurate = this->getType();
		else
			mostAccurate = rhs.getType();

		stream.str(rhs.toString());
		stream >> val;

		if (this->getValue() == 0)
			throw StackException("Divide by zero");

		val /= this->_value;

		stream.str();
		stream.clear();
		if (this->needInt(this->getType(), rhs.getType()))
			stream << static_cast<int>(val);
		else
			stream << val;

		Factory &f = Factory::getInstance();
		const IOperand * io = f.createOperand(mostAccurate, stream.str());

		return io;
	}
	IOperand const *operator%(IOperand const & rhs) const {
		eOperandType mostAccurate;
		std::stringstream stream;
		double val;

		try {
			val = boost::lexical_cast<double>(rhs.toString());
		} catch (boost::bad_lexical_cast e) {
			std::cerr << e.what() << std::endl;
		}
		if (val == 0)
			throw StackException("Modulo by zero");

		if (this->getPrecision() > rhs.getPrecision())
			mostAccurate = this->getType();
		else
			mostAccurate = rhs.getType();

		stream.str(rhs.toString());
		stream >> val;

		val = fmod(val, this->_value);

		stream.str();
		stream.clear();
		if (this->needInt(this->getType(), rhs.getType()))
			stream << static_cast<int>(val);
		else
			stream << val;

		Factory &f = Factory::getInstance();
		const IOperand * io = f.createOperand(mostAccurate, stream.str());

		return io;
	}

	std::string const & toString(void) const { return this->_stringValue; }
	eOperandType getType() const { return this->_type; }
	int getPrecision(void) const { return this->_precision; }
	T getValue() const { return this->_value; }
};
#endif /* TOPERAND_H */