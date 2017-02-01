#include <iostream> // std::cin
#include <sstream> // std::stringstream, rdbuf
#include <fstream> // std::ifstream

#include "../inc/Lexer.hpp"

Lexer::Lexer() {
	for(std::string line; std::getline(std::cin, line);) {
		if (!line.compare(";;")) {
			break;
		}
		this->_instrList.push_back(line);
	}
}
Lexer::Lexer(std::string file) {
	std::ifstream in(file);
	for (std::string line; std::getline(in, line);) {
		this->_instrList.push_back(line);
	}
}
Lexer::Lexer(const Lexer & ref) { *this = ref; }
Lexer::~Lexer() {}
Lexer & Lexer::operator=(const Lexer &ref) {
	this->_instrList = ref.getInstructionsList();
	return *this;
}



// std::string Lexer::getRawInstructions() const { return this->_rawInstr; }
// void Lexer::setRawInstructions(std::string instr) { this->_rawInstr = instr; }
std::list<std::string> Lexer::getInstructionsList() const { return this->_instrList; }