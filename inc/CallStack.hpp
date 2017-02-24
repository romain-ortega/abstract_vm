#ifndef CALLSTACK_H
#define CALLSTACK_H
# include <vector>
# include <map>
# include <boost/function.hpp>
# include "eOperandType.hpp" // enum
# include "IOperand.hpp" // IOperand
# include "TOperand.hpp" // Operand
# include "Expression.hpp"
# include "Exceptions.hpp"
class CallStack
{
	private:
		std::vector<Expression> _expressions; // parsed instr, type, value
		std::vector<const IOperand*> _stack;

	public:
		CallStack(std::vector<Expression> to_run);
		CallStack(const CallStack &ref);
		virtual ~CallStack();
		CallStack & operator=(const CallStack &ref);

		void run();
		void push(Expression const & value);
		void pop();
		void dump();
		void asserte(Expression const & value);
		void add();
		void sub();
		void mul();
		void div();
		void mod();
		void print();
		void exit();

		std::vector<const IOperand*> getStack() const;
		std::vector<Expression> getExpressions() const;
};
#endif /* CALLSTACK_H */
