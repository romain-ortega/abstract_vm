#include "../inc/Syntax.hpp"

Syntax::Syntax() {
	this->base_expression = instr > *(sep >> instr);
	this->instr = str_p("push") >> value
		| str_p("pop")
		| str_p("dump")
		| str_p("assert") >> value
		| str_p("add")
		| str_p("sub")
		| str_p("mul")
		| str_p("div")
		| str_p("mod")
		| str_p("print")
		| str_p("exit");
	this->sep = char_p('\n');
	this->value = str_p("int8(") >> n >> ')'
		| str_p("int16(") >> n >> ')'
		| str_p("int32(") >> n >> ')'
		| str_p("float(") >> z >> ')'
		| str_p("double(") >> z >> ')';
	this->n = boost::spirit::int_;
	this->z = boost::spirit::float_;
}
Syntax::Syntax(const Syntax & ref) {
	*this = ref;
}
Syntax & Syntax::operator=(const Syntax & ref) {
	*this = ref;
	return *this;
}
Syntax::~Syntax() {}
