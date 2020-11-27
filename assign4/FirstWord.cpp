#include "FirstWord.h"

using namespace std;

//adds word2 to keyword's successor list (succList)
void FirstWord::addToSuccessor(string word2){
	word2 = simplifyString(word2);
	for(int i=0; i < succList.size(); i++){
		if(succList[i].word2 == word2){ 
			succList[i].occurenceCt++; 	
			occurenceCt++;
			return; 
		}
	}

	SecondWord temp(word2);
	succList.push_back(temp);
	occurenceCt++;
}

//finds a random word that succeeds keyword
string FirstWord::findSuccessor(){
	int increment = rand() % occurenceCt;
	int i=0, j=-1;

	while(i <= increment){
		j++;
		i += succList[j].occurenceCt;
	}
	return succList[j].word2;
}

//returns word without punctuation, capitals, or spaces
string simplifyString(string word){
	for(int i = 0; i < word.size();){
		if(isalpha(word[i])){ word[i] = tolower(word[i]); i++; }
		else{ word.erase(i, 1); }
	}
	return word;
}

//FirstWord's direct print function
string FirstWord::toString(){
	stringstream ss;
	ss << "'" << keyword << "'" << " occurs: " << occurenceCt << " times\n"
		<< "\tFollowing words: \n";
	for(int i=0; i < succList.size(); i++){
		ss << '\t' << '\t'  << succList[i]<<endl;
	}

	return ss.str();
}

//FirstWord's indirect print function
ostream& operator<<(ostream& os, const FirstWord& rhs ){
	os << "'" << rhs.keyword << "'" << " occurs: " << rhs.occurenceCt << " times\n";
	for(int i=0; i < rhs.succList.size(); i++){
		os << rhs.succList[i]<<endl;
	}
	return os;
}
