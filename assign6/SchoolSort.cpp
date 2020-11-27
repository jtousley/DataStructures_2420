#include "DisjointSet.h"
#include <fstream>

using namespace std;

int main(){
	ifstream fin;
	int testCases, numberOfPeople, loopSize;
	int firstInput, secondInput;
	int firstInputFind, secondInputFind;
	char lineType = 'x';
	
	fin.open("highschool.txt");
	if(!fin.is_open()){
		exit(EXIT_FAILURE);
	}
	fin >> testCases;

	for(int i = 0; i < testCases; i++){
		cout<<"*** NEW TEST CASE ***\n";
		fin >> numberOfPeople;
		fin >> loopSize;

		DisjointSet SET(numberOfPeople);

		for(int j = 0; j < loopSize; j++){
			fin >> lineType;
			switch(lineType){
				case 'A':
					fin >> firstInput >> secondInput;

					firstInputFind = SET.Find(firstInput);
					secondInputFind = SET.Find(secondInput);
					cout << "People " << firstInput
						<< " and " << secondInput << ": ";
					
					if(firstInputFind == secondInputFind &&
						firstInputFind != -1 && secondInputFind != -1){
						cout << "Went to the same school\n"; 
					}
					else if(SET.Find(SET.getAntiValue(firstInput)) == secondInputFind ||
						cout<<"Went to different schools\n";
						firstInputFind == SET.Find(SET.getAntiValue(secondInput))){
					}					
					else{
						cout << "Not sure yet\n";
					}					
					break;

				case 'D':
					fin >> firstInput >> secondInput;

					if(SET.Find(firstInput) == SET.Find(secondInput) &&
						SET.Find(firstInput) != -1 && SET.Find(secondInput) != -1){
							cout << "BAD DATA\nProceeding without that information...\n\n";
					}
					if(SET.getAntiValue(firstInput) == -1){
						//set anti value
						SET.setAntiValue(firstInput, secondInput);
					}
					else{
						//union
						SET.Union( SET.getAntiValue(firstInput) , secondInput);
					}
					if(SET.getAntiValue(secondInput) == -1){
						//set anti value
						SET.setAntiValue(secondInput, firstInput);
					}
					else{
						//union
						SET.Union( SET.getAntiValue(secondInput) , firstInput);
					}

					break;
				default:
					cout<<"An error occurred. Please ensure correct spacing between inputs\n";
					exit(EXIT_FAILURE);
					break;
			}
		}
		cout << endl << endl;
	}
	fin.close();

	return 0;
}



