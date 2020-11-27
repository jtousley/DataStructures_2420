#include "SecondWord.h"

using namespace std;

//SecondWord's direct print function
string SecondWord::toString(){
	stringstream ss;
	ss << "'" << word2 << "'" << " occurs: " << occurenceCt << " times\n";

	return ss.str();
}

//SecondWord's indirect print function
std::ostream& operator<<(std::ostream& os, const SecondWord& rhs){
	os << "'" << rhs.word2 << "'" << " occurs: " << rhs.occurenceCt << " times\n";

	return os;		
}
