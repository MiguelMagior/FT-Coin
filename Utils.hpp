#ifndef UTILS_HPP
#define UTILS_HPP
#include <vector>
#include <string>
using namespace std;

int validInt();
template<typename Type> bool isDuplicated(vector<Type> vec, Type data){
	bool isDuplicated = false;
	for(const auto& element : vec){
		if(data == element){
			isDuplicated = true;
		}
	}
	return isDuplicated;
}
vector<string> sortAlphabetical(vector<string> vec);
void printFile(string fileName);

#endif
