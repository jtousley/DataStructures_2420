w#ifndef FIRSTWORD_H
#define FIRSTWORD_H

#include "SecondWord.h"
#include <string>
#include <iostream>
#include <vector>

struct FirstWord{
	std::string keyword;
	int occurenceCt;
	std::vector<SecondWord> succList;

	FirstWord(){ keyword = ""; occurenceCt = 0; }
	FirstWord(std::string nKeyword){ keyword = nKeyword; occurenceCt = 0; }
	//adds word2 to keyword's successor list (succList)
	void addToSuccessor(std::string word2);
	//finds a random word that succeeds keyword
	std::string findSuccessor();
	//FirstWord's direct print function
	std::string toString();

	//FirstWord's indirect print function
	friend std::ostream& operator<<(std::ostream& stream, const FirstWord& rhs );
};

//returns word without punctuation, capitals, or spaces
std::string simplifyString(std::string word);

#endif