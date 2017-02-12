#ifndef GRAMMAR_H
#define GRAMMAR_H
# include <boost/spirit/include/qi.hpp>
# include <boost/fusion/include/std_pair.hpp>
# include <boost/fusion/include/boost_tuple.hpp>
# include <iostream>
# include <map>
# include "Skipper.hpp"
namespace qi = boost::spirit::qi;

typedef std::pair<std::string, boost::optional<std::string> > pair_type;
typedef std::vector<pair_type> pairs_type;

template <typename Iterator, typename Skipper = skipper<std::string::iterator> >
struct instrValue
	: qi::grammar<Iterator, pairs_type(), Skipper>
{
	instrValue()
		: instrValue::base_type(base_expression)
	{
		base_expression = pair % (*~qi::char_("\r\n") >> qi::eol);
		pair            = instr >> *(value);
		instr           = *(boost::spirit::ascii::blank) >>
												(qi::lit("push") >> value
												^ qi::lit("pop")
												^ qi::lit("dump")
												^ qi::lit("assert") >> value
												^ qi::lit("add")
												^ qi::lit("sub")
												^ qi::lit("mul")
												^ qi::lit("div")
												^ qi::lit("mod")
												^ qi::lit("print")
												^ qi::lit("exit"))
												>> *(boost::spirit::ascii::blank);
		value           = *(boost::spirit::ascii::blank) >>
												(qi::lit("int8(") >> qi::int_ >> ')'
												^ qi::lit("int16(") >> qi::int_ >> ')'
												^ qi::lit("int32(") >> qi::int_ >> ')'
												^ qi::lit("float(") >> qi::float_ >> ')'
												^ qi::lit("double(") >> qi::float_ >> ')')
												>> *(boost::spirit::ascii::blank);
	}

	qi::rule<Iterator, pairs_type(), Skipper> base_expression;
	qi::rule<Iterator, pair_type(), Skipper> pair;
	qi::rule<Iterator, std::string(), Skipper> instr, value;
	pairs_type instr_value;
	std::string line;
};
#endif /* GRAMMAR_H */
