#ifndef GRAMMAR_H
#define GRAMMAR_H
# include <boost/spirit/include/qi.hpp>
# include <boost/fusion/include/std_pair.hpp>
# include <boost/variant.hpp>
# include <iostream>
# include "Skipper.hpp"
# include "Parser.hpp"
namespace qi = boost::spirit::qi;

typedef std::pair<std::string, boost::optional<std::string> > pair_t;
typedef std::vector<pair_t> pairs_t;
#define BOOST_SPIRIT_DEBUG

template <typename Iterator, typename Skipper = qi::blank_type >
struct Grammar
	: qi::grammar<Iterator, pairs_t(), Skipper>
{
	Grammar()
		: Grammar::base_type(base_expression)
	{
		base_expression  = qi::eol | qi::lit(';') | pair;
		pair             = instr >> -(value)
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
		value            = (qi::string("int8")
													>> qi::char_('(') >> n >> qi::char_(')')
												| qi::string("int16")
													>> qi::char_('(') >> n >> qi::char_(')')
												| qi::string("int32")
													>> qi::char_('(') >> n >> qi::char_(')')
												| qi::string("float")
													>> qi::char_('(') >> z >> qi::char_(')')
												| qi::string("double")
													>> qi::char_('(') >> z >> qi::char_(')'));
		n = -qi::char_('-') >> +qi::char_("0-9");
		z = -qi::char_('-') >> +qi::char_("0-9") >> -(qi::char_('.') >> +qi::char_("0-9"));
		BOOST_SPIRIT_DEBUG_NODES((base_expression)(pair)(instr)(value))
	}

	private:
		qi::rule<Iterator, pairs_t(), Skipper> base_expression;
		qi::rule<Iterator, pair_t(), Skipper> pair;
		qi::rule<Iterator, std::string(), Skipper> instr, value, n, z;
};
#endif /* GRAMMAR_H */
