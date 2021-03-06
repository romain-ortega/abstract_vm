#ifndef PARSER_H
# define PARSER_H
# include <string> // std::string
# include <list> // std::list
# include <boost/spirit/include/qi_core.hpp> // include files for boost spirit
# include <boost/config/warning_disable.hpp>
# include <boost/spirit/include/qi.hpp>
# include "Expression.hpp" // Expression struct
class Parser
{
private:
	std::list<std::string> _exprList; // contains all expressions
	std::vector<Expression> _parsed_expressions; // parsedn instr, type, value
	bool _verbose;

	eOperandType _getType(std::string type, std::string value);

public:
	Parser();
	Parser(std::string file);
	Parser(const Parser &ref);
	virtual ~Parser();
	Parser & operator=(const Parser &ref);

	void parseExprList(std::list<std::string>::const_iterator iter_begin,
std::list<std::string>::const_iterator iter_end);
	void semanticCheck();

	std::list<std::string> getExprList() const;
	std::vector<Expression> getParsedExpr() const;
	bool flagVerbose() const;
	void setVerbose(bool flag);
};
#endif /* PARSER_H */