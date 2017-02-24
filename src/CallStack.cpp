#include <iostream>
#include <boost/function.hpp>
#include "../inc/CallStack.hpp"
#include "../inc/Exceptions.hpp"
#include "../inc/Factory.hpp"
CallStack::CallStack(std::vector<Expression> to_run) : _expressions(to_run) {}
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
	// static std::map<std::string, void (CallStack::*)() const> table {
	//   {"add", &CallStack::add},
	//   // {"assert", &CallStack::asserte},
	//   {"div", &CallStack::div},
	//   {"dump", &CallStack::dump},
	//   {"exit", &CallStack::exit},
	//   {"mod", &CallStack::mod},
	//   {"mul", &CallStack::mul},
	//   {"pop", &CallStack::pop},
	//   {"print", &CallStack::print},
	//   // {"push", &CallStack::push},
	//   {"sub", &CallStack::sub}
	// };
	if (this->_expressions[this->_expressions.size() - 1].getInstruction() != "exit") {
		std::cout << this->_expressions.end()->getInstruction() << std::endl;
		throw StackException("Exit is not the last instruction");
	}
	for (std::vector<Expression>::iterator i = this->_expressions.begin(); i != this->_expressions.end(); ++i) {
		// temporary if forest
		if ((*i).getInstruction() == "push") {
			this->push((*i));
		} else if  ((*i).getInstruction() == "assert") {
			this->asserte((*i));
		} else if  ((*i).getInstruction() == "pop") {
			this->pop();
		} else if  ((*i).getInstruction() == "dump") {
			this->dump();
		} else if  ((*i).getInstruction() == "add") {
			this->add();
		} else if  ((*i).getInstruction() == "sub") {
			this->sub();
		} else if  ((*i).getInstruction() == "mul") {
			this->mul();
		} else if  ((*i).getInstruction() == "div") {
			this->div();
		} else if  ((*i).getInstruction() == "mod") {
			this->mod();
		} else if  ((*i).getInstruction() == "print") {
			this->print();
		} else if  ((*i).getInstruction() == "exit") {
			this->exit();
		} else {
			throw StackException("Wrong instruction: " + (*i).getInstruction());
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
    throw StackException("Error: print on empty stack");
  if (this->_stack.back()->getType() != Int8)
    throw StackException("The last stack value is not an Int8");
  if (!std::isprint(std::stoi(this->_stack.back()->toString())))
    throw StackException("Character not printable");
  std::cout << static_cast<char>(std::stoi(this->_stack.back()->toString())) << std::endl;
}
void CallStack::exit() {
  // std::cout << this->_output.str();
  for ( int i = (this->_stack.size() - 1); i >= 0; i--) {
    delete this->_stack[i];
    this->_stack.pop_back();
  }
}

std::vector<const IOperand*> CallStack::getStack() const { return this->_stack; }
std::vector<Expression> CallStack::getExpressions() const { return this->_expressions; }
