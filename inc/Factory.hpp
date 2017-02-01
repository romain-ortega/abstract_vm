#ifndef FACTORY_H
#define FACTORY_H
# include <iostream>
# include "IOperand.hpp"
# include "eOperandType.hpp"

class Factory
{
private:
	IOperand const * createInt8(std::string const & value) const;
	IOperand const * createInt16(std::string const & value) const;
	IOperand const * createInt32(std::string const & value) const;
	IOperand const * createFloat(std::string const & value) const;
	IOperand const * createDouble(std::string const & value) const;

public:
	Factory();
	Factory(const Factory &ref);
	virtual ~Factory();
	Factory & operator=(const Factory &ref);
	IOperand const * createOperand(eOperandType type, std::string const & value) const;
};

#endif /* FACTORY_H */