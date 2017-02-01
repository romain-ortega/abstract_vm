#ifndef LEXER_H
#define LEXER_H
# include <string> // std::string
# include <list> // std::list
class Lexer
{
private:
	std::list<std::string> _instrList;

public:
	Lexer();
	Lexer(std::string file);
	Lexer(const Lexer &ref);
	virtual ~Lexer();
	Lexer & operator=(const Lexer &ref);

	std::list<std::string> getInstructionsList() const;
};
#endif /* LEXER_H */