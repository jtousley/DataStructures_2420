#include "HashTable.h"
#include "FirstWord.h"
#include <fstream>

using namespace std;

//reads in a file and puts the words in hash table T
void textToHash(ifstream& fin, HashTable<string, FirstWord>& T);
//generates a poem using the words in hash table T, starting with startWord of poemLength length
string generatePoem(HashTable<string, FirstWord>& T, string startWord, int poemLength);

int main(){
	HashTable<string, FirstWord> TABLE;
	ifstream fin;
	string ERROR;
	srand(time(NULL));

	try{
	fin.open("green.txt");
	if(!fin.is_open()){
		ERROR = "Error reading file 'green.txt'\n";
		throw ERROR;
	}
	textToHash(fin, TABLE);
	fin.close();

	cout<<generatePoem(TABLE, "sam", 20)<<endl;
	cout<<TABLE.toString()<<endl;
	TABLE.makeEmpty();

	cout<<"Table empty\n";
	fin.open("clown.txt");
	if(!fin.is_open()){
		ERROR = "Error reading file 'clown.txt'\n";
		throw ERROR;
	}
	textToHash(fin, TABLE);
	fin.close();

	cout<<generatePoem(TABLE, "go", 20) << endl;
	cout<<TABLE.toString()<<endl;
	TABLE.makeEmpty();

	fin.open("inch.txt");
	if(!fin.is_open()){
		ERROR = "Error reading file 'inch.txt'\n";
		throw ERROR;
	}
	textToHash(fin, TABLE);
	fin.close();

	cout << generatePoem(TABLE, "computer", 50) << endl;
	TABLE.makeEmpty();

	fin.open("poe.txt");
	if(!fin.is_open()){
		ERROR = "Error reading file 'poe.txt'\n";
		throw ERROR;
	}
	textToHash(fin, TABLE);
	fin.close();
	
	cout << generatePoem(TABLE, "nevermore", 50) <<endl;
	TABLE.makeEmpty();

	fin.open("suess.txt");
	if(!fin.is_open()){
		ERROR = "Error reading file 'suess.txt'\n";
		throw ERROR;
	}
	textToHash(fin, TABLE);
	fin.close();

	cout << generatePoem(TABLE, "mordecai", 50);
	TABLE.makeEmpty();
	}
	catch(string errorMessage){
		cout<<errorMessage<<endl;
	}

	return 0;
}

//generates a poem using the words in hash table T, starting with startWord of poemLength length
string generatePoem(HashTable<string, FirstWord>& TABLE, string startWord, int poemLength){
	stringstream ss;
	FirstWord *location;
	string first, second;

	first = startWord;

	for(int i = 0; i < poemLength; i++){
		location = TABLE.find(first);
		if(location == NULL) { throw "That word does not exist in the hash table!\n"; }
		ss << first << " ";
		first = location->findSuccessor();
		if(!(i % 5) && i){ ss << endl; }
	}
	ss << endl;
	return ss.str();
}

//reads in a file and puts the words in hash table T
void textToHash(ifstream& fin, HashTable<string, FirstWord>& TABLE){
	string first, second;
	FirstWord *location;

	fin>>first;
	first = simplifyString(first);
	fin.ignore();
	while( fin>>second ){
		fin.ignore();
		second = simplifyString(second);

		location = TABLE.find(first);

		if(location == NULL){
			location = new FirstWord(first);
			location->addToSuccessor(second);
			TABLE.insert(first, location);
		}
		else{
			location->addToSuccessor(second);
		}
		first=second;
	}
}
