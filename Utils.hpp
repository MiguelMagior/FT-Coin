#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <string>
using namespace std;

int validInt();
template<typename Type> bool isDuplicated(vector<Type> vec, Type data){
	bool isDuplicated = false;
	for(int index = 0; index < vec.size(); index++){
		if(data == vec.at(index)){
			isDuplicated = true;
		}
	}
	return isDuplicated;
}
vector<string> sortAlphabetical(vector<string> vec);

#endif
