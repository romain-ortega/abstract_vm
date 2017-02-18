#ifndef PARSER_H
# define PARSER_H
# include <string> // std::string
# include <list> // std::list
# include <boost/spirit/include/qi_core.hpp> // include files for boost spirit
# include <boost/config/warning_disable.hpp>
# include <boost/spirit/include/qi.hpp>
# include "Grammar.hpp"
class Parser
{
private:
	std::list<std::string> _exprList; // contains all expressions

public:
	Parser();
	Parser(std::string file);
	Parser(const Parser &ref);
	virtual ~Parser();
	Parser & operator=(const Parser &ref);

	bool parseExprList(std::list<std::string>::iterator first, std::list<std::string>::iterator last, std::list<std::string>& l);
	std::list<std::string> getExprList() const;

	pairs_t instr_value_array;
};
#endif /* PARSER_H */