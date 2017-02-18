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
	pairs_t _instr_value_array; // vector of std::pair(instr, value)

public:
	Parser();
	Parser(std::string file);
	Parser(const Parser &ref);
	virtual ~Parser();
	Parser & operator=(const Parser &ref);

	bool parseExprList(std::list<std::string>::iterator iter_begin,
std::list<std::string>::iterator iter_end);
	std::list<std::string> getExprList() const;
};
#endif /* PARSER_H */