#ifndef GRAMMAR_H
#define GRAMMAR_H
# include <boost/spirit/include/qi.hpp>
# include <boost/fusion/include/std_pair.hpp>
# include <iostream>
# include <map>
namespace qi = boost::spirit::qi;

typedef std::pair<std::string, boost::optional<std::string> > pair_type;
typedef std::vector<pair_type> pairs_type;

template <typename Iterator>
struct instrValue
	: qi::grammar<Iterator, pairs_type()>
{
	instrValue()
		: instrValue::base_type(base_expression)
	{
		base_expression = pair >> *(qi::char_('\n') >> instr);
		pair            = instr >> -value;
		instr           = qi::lit("push") >> value
												^ qi::lit("pop")
												^ qi::lit("dump")
												^ qi::lit("assert") >> value
												^ qi::lit("add")
												^ qi::lit("sub")
												^ qi::lit("mul")
												^ qi::lit("div")
												^ qi::lit("mod")
												^ qi::lit("print")
												^ qi::lit("exit");
		value           = qi::lit("int8(") >> qi::int_ >> ')'
												^ qi::lit("int16(") >> qi::int_ >> ')'
												^ qi::lit("int32(") >> qi::int_ >> ')'
												^ qi::lit("float(") >> qi::float_ >> ')'
												^ qi::lit("double(") >> qi::float_ >> ')';
	}

	bool parseLine(Iterator begin, Iterator end) {
	  if (!qi::parse(begin, end, this, this->instr_value)) {
        std::cout << "-------------------------------- \n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------------- \n";
    }
    else {
        std::cout << "-------------------------------- \n";
        std::cout << "Parsing succeeded, found entries:\n";
        pairs_type::iterator end = instr_value.end();
        for (pairs_type::iterator it = instr_value.begin(); it != end; ++it)
        {
            std::cout << (*it).first;
            if ((*it).second)
                std::cout << "=" << boost::get<std::string>((*it).second);
            std::cout << std::endl;
        }
        std::cout << "---------------------------------\n";
    }
	}

	qi::rule<Iterator, pairs_type()> base_expression;
	qi::rule<Iterator, pair_type()> pair;
	qi::rule<Iterator, std::string()> instr, value;
	pairs_type instr_value;
	std::string line;
};
#endif /* GRAMMAR_H */
