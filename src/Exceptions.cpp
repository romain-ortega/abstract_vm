#include <iostream>
#include "../inc/Exceptions.hpp"

// Stack exceptions
StackException::StackException(std::string error_message)
	: _error_message(error_message) {}
StackException::StackException(const StackException & ref) { *this = ref; }
StackException::~StackException() throw() {}
StackException & StackException::operator=(const StackException &ref) {
	this->_error_message = ref.getError();
	return *this;
}
const char *StackException::what() const throw() {
	std::string *what = new std::string("Error: " + this->getError());
  return what->c_str();
}
std::string StackException::getError() const { return this->_error_message; }


// Entry exceptions
EntryException::EntryException(EntryExceptionReasons reason, std::string element, unsigned int line_number)
	: _element(element), _line_number(line_number) {
	if (reason == SyntaxError) {
		this->_error_message = "Syntax error line";
	} else if (reason == TypeExpected) { // element = type
		this->_error_message = "Type expected for `" + element + "` instruction";
	} else if (reason == ValueExpected) { // element = value
		this->_error_message = "Value expected for `" + element + "` instruction";
	} else if (reason == InstrExpected) { // element = value
		this->_error_message = "Instruction `" + element + "` expected";
	} else if (reason == UnexpectedIdentifier) { // element = instr
		this->_error_message = "Unexpected identifier for `" + element + "` instruction";
	} else if (reason == InvalidValue) { // element = value
		this->_error_message = "Value `" + element + "` could not be interpreted as type";
	} else {
		this->_error_message = "Invalid expression";
	}
}
EntryException::EntryException(const EntryException & ref) { *this = ref; }
EntryException & EntryException::operator=(const EntryException &ref) {
	this->_element = ref.getElement();
	this->_line_number = ref.getLineNumber();
	this->_error_message = ref.getError();
	return *this;
}
EntryException::~EntryException() throw() {}

const char *EntryException::what() const throw() {
	std::string *what = new std::string(
		this->getError() + " at line " + std::to_string(this->_line_number)
	);
  return what->c_str();
}
std::string EntryException::getError() const { return this->_error_message; }
std::string EntryException::getElement() const { return this->_element; }
unsigned int EntryException::getLineNumber() const { return this->_line_number; }
