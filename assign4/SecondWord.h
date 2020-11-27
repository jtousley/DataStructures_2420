#ifndef SECONDWORD_H
#define SECONDWORD_H

#include <iostream>
#include <string>
#include <cstring>
#include <sstream>

struct SecondWord{
	std::string word2;
	int occurenceCt;

	SecondWord(){ word2=""; occurenceCt=0; }
	SecondWord(std::string nWord){ word2=nWord; occurenceCt=1; }
	//SecondWord's direct print function
	std::string toString();

	//SecondWord's indirect print function
	friend std::ostream& operator<<(std::ostream& stream, const SecondWord& rhs);
};

#endif