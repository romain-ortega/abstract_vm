#ifndef PARSER_H
#define PARSER_H
# include <string> // std::string
# include <list> // std::list
# include "Syntax.hpp" // _syntax
class Parser
{
private:
	std::list<std::string> _instrList;
	Syntax *_syntax;

public:
	Parser();
	Parser(std::string file);
	Parser(const Parser &ref);
	virtual ~Parser();
	Parser & operator=(const Parser &ref);

	bool parseLine(std::string line) const;
	std::list<std::string> getInstructionsList() const;
};
#endif /* PARSER_H */