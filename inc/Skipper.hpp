#ifndef SKIPPER_H
#define SKIPPER_H
# include <boost/spirit/include/qi.hpp>
# include <iostream>
namespace qi = boost::spirit::qi;

template<typename Iterator>
struct skipper : public qi::grammar<Iterator> {

    skipper() : skipper::base_type(skip) {
				skip = *(boost::spirit::ascii::blank) >>
								((qi::char_(';') | qi::char_('\0'))) >>
								*(qi::char_);
    }
    qi::rule<Iterator> skip;
};
#endif /* SKIPPER_H */