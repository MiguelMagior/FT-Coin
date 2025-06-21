#include "Utils.hpp"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
using namespace std;

int validInt(){
	int num;
	while(!(cin >> num)){
		cout << " Invalid entry. Please, try again: ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	};
	return num;
}
vector<string> sortAlphabetical(vector<string> vec){
	string aux;
	int size = vec.size();
	for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (vec[j] > vec[j + 1]){
                aux = vec[j];
                vec[j] = vec[j+1];
                vec[j+1] = aux;
            }
        }
	}
	return vec;
}
void printFile(string fileName){
	fstream file;
	string line;

	file.exceptions(fstream::failbit | fstream::badbit);

	try{
		file.open(fileName);
		while(getline(file,line)){
			cout << line << endl;
		}
		file.close();
	}
	catch(const exception& e){
		if(file.is_open()){
			file.close();
		}
		cerr << " Error acessing File " << fileName << ": "
			<< e.what() << endl;
	}
}
