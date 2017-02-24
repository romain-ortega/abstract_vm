#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
# include <iostream>
# include <exception>
class StackException : public std::exception
{
protected:
	std::string _error_message;

public:
	StackException(std::string error_message);
	StackException(const StackException &ref);
	~StackException() throw();
	StackException & operator=(const StackException &ref);
	virtual const char  *what( void ) const throw();

	std::string getError() const;
};

// EntryException
enum EntryExceptionReasons {
	SyntaxError,
	TypeExpected,
	ValueExpected,
	InstrExpected,
	UnexpectedIdentifier,
	InvalidValue
};
class EntryException : public std::exception
{
protected:
	std::string _element; // instr or type or value
	unsigned int _line_number;
	std::string _error_message;

public:
	EntryException(EntryExceptionReasons reason, std::string element, unsigned int line_number);
	EntryException(const EntryException &ref);
	~EntryException() throw();
	EntryException & operator=(const EntryException &ref);
	virtual const char *what() const throw();

	std::string getError() const;
	std::string getElement() const;
	unsigned int getLineNumber() const;
};

#endif /* EXCEPTIONS_H */
