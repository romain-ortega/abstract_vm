#ifndef SYNTAX_H
#define SYNTAX_H
#include <boost/spirit/include/qi_core.hpp> // include files for boost spirit
class Syntax : public boost::spirit::grammar<Syntax>
{
private:

public:
	Syntax();
	Syntax(const Syntax &ref);
	virtual ~Syntax();
	Syntax & operator=(const Syntax &ref);
	template <typename ScannerT>
	boost::spirit::symbol<int> vars;
	boost::spirit::rule<ScannerT> base_expression, sep, instr, value, n, z;
	const boost::spirit::rule<ScannerT> &start() const { return base_expression; }
};
#endif /* SYNTAX_H */
