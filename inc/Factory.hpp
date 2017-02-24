#ifndef FACTORY_H
#define FACTORY_H
# include <iostream>
# include "IOperand.hpp"
# include "eOperandType.hpp"

class Factory
{
private:
	Factory() {}
	IOperand const *createInt8(std::string const & value) const;
	IOperand const *createInt16(std::string const & value) const;
	IOperand const *createInt32(std::string const & value) const;
	IOperand const *createFloat(std::string const & value) const;
	IOperand const *createDouble(std::string const & value) const;

public:
	virtual ~Factory() {}
	Factory(Factory const &rhs) = delete;
	Factory & operator=(const Factory &ref) = delete;

	IOperand const * createOperand(eOperandType type, std::string const & value) const;
	typedef IOperand const*(Factory::*FP[5])(std::string const &) const;
	static FP create;

	static Factory & getInstance() {
		static Factory instance;
		return instance;
	}
};

#endif /* FACTORY_H */