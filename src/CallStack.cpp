#include <iostream>
#include <boost/function.hpp>
#include "../inc/CallStack.hpp"
#include "../inc/Exceptions.hpp"
#include "../inc/Factory.hpp"
typedef void (CallStack::*FP)();
std::map <std::string, FP> CallStack::fmap;

CallStack::CallStack(std::vector<Expression> to_run) : _expressions(to_run) {
	if (CallStack::fmap.empty()) {
		CallStack::fmap.insert(std::make_pair("add", &CallStack::add));
		CallStack::fmap.insert(std::make_pair("div", &CallStack::div));
		CallStack::fmap.insert(std::make_pair("dump", &CallStack::dump));
		CallStack::fmap.insert(std::make_pair("exit", &CallStack::exit));
		CallStack::fmap.insert(std::make_pair("mul", &CallStack::mod));
		CallStack::fmap.insert(std::make_pair("pop", &CallStack::pop));
		CallStack::fmap.insert(std::make_pair("print", &CallStack::print));
		CallStack::fmap.insert(std::make_pair("sub", &CallStack::sub));
	}
}
CallStack::CallStack(const CallStack & ref) { *this = ref; }
CallStack::~CallStack() {
	while (!this->_stack.empty())
		this->_stack.pop_back();
}
CallStack & CallStack::operator=(const CallStack &ref) {
	this->_stack = ref.getStack();
	this->_expressions = ref.getExpressions();
	return *this;
}

void CallStack::run() {
	if (this->_expressions[this->_expressions.size() - 1].getInstruction() != "exit")
		throw StackException("Exit is not the last instruction");

	for (std::vector<Expression>::iterator i = this->_expressions.begin(); i != this->_expressions.end(); ++i) {
		if ((*i).getInstruction() == "push") {
			this->push((*i));
		} else if  ((*i).getInstruction() == "assert") {
			this->asserte((*i));
		} else {
			FP fp = CallStack::fmap[(*i).getInstruction()];
			(this->*fp)();
		}
	}
}

void CallStack::push(Expression const & value) {
	const IOperand *operand = Factory::getInstance().createOperand(value.getType(), value.getValue());
	this->_stack.push_back(operand);
}

void CallStack::pop() {
	if (this->_stack.empty())
		throw StackException("pop on empty stack !");
	this->_stack.pop_back();
}
void CallStack::dump() {
	if (!this->_stack.empty())
		for (std::vector<const IOperand*>::iterator i = this->_stack.begin(); i < this->_stack.end(); ++i) {
			std::cout << (*i)->toString() << std::endl;
		}
}
void CallStack::asserte(Expression const & value) {
	const IOperand *tmp = Factory::getInstance().createOperand(value.getType(), value.getValue());

	if (this->_stack.empty())
		throw StackException("assert on empty stack !");
	if (this->_stack.back()->getType() != tmp->getType())
		throw StackException("assert on different type !");
	if (stod(this->_stack.back()->toString()) != stod(tmp->toString()))
		throw StackException("assert between " + this->_stack.back()->toString() + " and " + tmp->toString() + " is false !");
}
void CallStack::add() {
	const IOperand *tmp;

	if (this->_stack.size() < 2)
		throw StackException("add: less than 2 values in the stack");
	tmp = *(this->_stack[this->_stack.size() - 2]) + *(this->_stack[this->_stack.size() - 1]);
	delete this->_stack[this->_stack.size() - 1];
	delete this->_stack[this->_stack.size() - 2];
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(tmp);
}
void CallStack::sub() {
	const IOperand *tmp;

	if (this->_stack.size() < 2)
		throw StackException("sub: less than 2 values in the stack");
	tmp = *(this->_stack[this->_stack.size() - 2]) - *(this->_stack[this->_stack.size() - 1]);
	delete this->_stack[this->_stack.size() - 1];
	delete this->_stack[this->_stack.size() - 2];
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(tmp);
}
void CallStack::mul() {
	const IOperand *tmp;

	if (this->_stack.size() < 2)
		throw StackException("mul: less than 2 values in the stack");
	tmp = (*this->_stack[this->_stack.size() - 2]) * (*this->_stack[this->_stack.size() - 1]);
	delete this->_stack[this->_stack.size() - 1];
	delete this->_stack[this->_stack.size() - 2];
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(tmp);
}
void CallStack::div() {
	const IOperand *tmp;

	if (this->_stack.size() < 2)
		throw StackException("div: less than 2 values in the stack");
	tmp = *(this->_stack[this->_stack.size() - 2]) / *(this->_stack[this->_stack.size() - 1]);
	delete this->_stack[this->_stack.size() - 1];
	delete this->_stack[this->_stack.size() - 2];
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(tmp);
}
void CallStack::mod() {
	const IOperand *tmp;

	if (this->_stack.size() < 2)
		throw StackException("mod: less than 2 values in the stack");
	tmp = *(this->_stack[this->_stack.size() - 2]) % *(this->_stack[this->_stack.size() - 1]);
	delete this->_stack[this->_stack.size() - 1];
	delete this->_stack[this->_stack.size() - 2];
	this->_stack.pop_back();
	this->_stack.pop_back();
	this->_stack.push_back(tmp);
}
void CallStack::print() {
  if (this->_stack.size() < 1)
    throw StackException("print: Empty stack");
  if (this->_stack.back()->getType() != eOperandType::Int8)
    throw StackException("print: The last stack value is not an 8-bit integer");
  if (!std::isprint(std::stoi(this->_stack.back()->toString())))
    throw StackException("print: Value is not printable");
  std::cout << static_cast<char>(std::stoi(this->_stack.back()->toString())) << std::endl;
}
void CallStack::exit() {
	while (!this->_stack.empty())
		this->_stack.pop_back();
}

std::vector<const IOperand*> CallStack::getStack() const { return this->_stack; }
std::vector<Expression> CallStack::getExpressions() const { return this->_expressions; }
