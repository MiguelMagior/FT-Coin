#include "Utils.hpp"
#include <iostream>
#include <limits>
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
