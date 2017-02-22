#ifndef CALLSTACK_H
#define CALLSTACK_H
# include <stack>
# include <vector>
# include "eOperandType.hpp" // enum
# include "IOperand.hpp" // IOperand
# include "TOperand.hpp" // Operand
# include "Expression.hpp"

class CallStack
{
private:
	std::vector<Expression> _expressions; // parsed instr, type, value
	std::stack<IOperand*> _stack;

public:
	CallStack(std::vector<Expression> to_run);
	CallStack(const CallStack &ref);
	virtual ~CallStack();
	CallStack & operator=(const CallStack &ref);

	void push(Expression const & value);
	void pop(void);
	void dump(void);
	void assert(Expression const & value);
	void add(void);
	void sub(void);
	void mul(void);
	void div(void);
	void mod(void);
	void print(void);
	void exit(void);

	std::stack<IOperand*> getStack() const;
	void setStack(std::stack<IOperand*> stack);
};
#endif /* CALLSTACK_H */
