#ifndef EXPRESSION_H
#define EXPRESSION_H
# include <iostream>
# include "eOperandType.hpp"
class Expression
{
private:
	std::string _instr;
	eOperandType _type;
	std::string _strType;
	std::string _value;

public:
	Expression(std::string instr, eOperandType type, std::string strType, std::string value);
	Expression(const Expression &ref);
	virtual ~Expression();
	Expression & operator=(const Expression &ref);

	std::string getInstruction() const;
	eOperandType getType() const;
	std::string getStringType() const;
	std::string getValue() const;
};

#endif /* EXPRESSION_H */
