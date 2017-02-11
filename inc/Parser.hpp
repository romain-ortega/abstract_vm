#ifndef PARSER_H
# define PARSER_H
# include <string> // std::string
# include <list> // std::list
# include <boost/spirit/include/qi_core.hpp> // include files for boost spirit
# include <boost/config/warning_disable.hpp>
# include <boost/spirit/include/qi.hpp>
class Parser
{
private:
	std::list<std::string> _instrList;

public:
	Parser();
	Parser(std::string file);
	Parser(const Parser &ref);
	virtual ~Parser();
	Parser & operator=(const Parser &ref);

	bool parseInstructionList(std::list<std::string>::iterator first, std::list<std::string>::iterator last, std::list<std::string>& l);
	std::list<std::string> getInstructionsList() const;
};
#endif /* PARSER_H */