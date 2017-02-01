#include <iostream>
#include "../inc/Lexer.hpp"

Lexer::Lexer() {
}
Lexer::Lexer(std::string file) : _file(file) {}
Lexer::Lexer(const Lexer & ref) { *this = ref; }
Lexer::~Lexer() {}
Lexer & Lexer::operator=(const Lexer &ref) {
	this->_file = ref.getFile();
	return *this;
}

std::string Lexer::getFile() const { return this->_file; }
void Lexer::setFile(std::string file) { this->_file = file; }