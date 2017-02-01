#ifndef LEXER_H
#define LEXER_H
# include <iostream>

class Lexer
{
private:
	std::string _file;

public:
	Lexer();
	Lexer(std::string file);
	Lexer(const Lexer &ref);
	virtual ~Lexer();
	Lexer & operator=(const Lexer &ref);

	std::string getFile() const;
	void setFile(std::string file);
};

#endif /* LEXER_H */