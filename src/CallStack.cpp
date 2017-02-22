#include <iostream>
#include "../inc/CallStack.hpp"

CallStack::CallStack(std::vector<Expression> to_run) : _expressions(to_run) {}
CallStack::CallStack(const CallStack & ref) { *this = ref; }
CallStack::~CallStack() {
	while (!this->_stack.empty())
		this->_stack.pop();
}
CallStack & CallStack::operator=(const CallStack &ref) {
	this->_stack = ref.getStack();
	return *this;
}


void CallStack::push(Expression const & value) {
    this->_stack.push_back(Factory::Factory().createOperand(value.getType(), value.getValue()));
}

void	CallStack::pop( void ) {
  if (this->_stack.empty())
    throw StackExceptions("Error: pop on empty stack !");
	this->_stack.pop();
}
std::stack<IOperand*> CallStack::getStack() const { return this->_stack; }
void CallStack::setFile(std::stack<IOperand*> stack) { this->_stack = stack; }
