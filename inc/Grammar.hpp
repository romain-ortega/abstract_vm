#ifndef GRAMMAR_H
#define GRAMMAR_H
# include <boost/spirit/include/qi.hpp>
# include <boost/fusion/include/std_tuple.hpp>
# include <iostream>
# include "Parser.hpp"
namespace qi = boost::spirit::qi;

// instr (type) (value)
typedef std::tuple<std::string, boost::optional<std::string>, boost::optional<std::string> > tuple_t;
typedef std::vector<tuple_t> tuples_t;

template <typename Iterator, typename Skipper = qi::blank_type >
struct Grammar
	: qi::grammar<Iterator, tuples_t(), Skipper>
{
	Grammar()
		: Grammar::base_type(base_expression)
	{
		base_expression  = qi::eol | qi::lit(';') | tuple;
		tuple            = instr >> -(type) >> -(value)
												>> (qi::lit('\n')
													| (qi::lit(';') >> *(qi::char_)));
		instr            = (qi::string("push")
												| qi::string("pop")
												| qi::string("dump")
												| qi::string("assert")
												| qi::string("add")
												| qi::string("sub")
												| qi::string("mul")
												| qi::string("div")
												| qi::string("mod")
												| qi::string("print")
												| qi::string("exit"));
		type             = qi::string("int8")
												| qi::string("int16")
												| qi::string("int32")
												| qi::string("float")
												| qi::string("double");
		value            = '(' >> z >> ')'
												|| '(' >> n >> ')';
		n = -qi::char_('-') >> +qi::char_("0-9");
		z = -qi::char_('-') >> +qi::char_("0-9") >> (qi::char_('.') >> +qi::char_("0-9"));
	}

	private:
		qi::rule<Iterator, tuples_t(), Skipper> base_expression;
		qi::rule<Iterator, tuple_t(), Skipper> tuple;
		qi::rule<Iterator, std::string(), Skipper> instr, type, value, n, z;
};
#endif /* GRAMMAR_H */
