#include "OracleMemoryDAO.hpp"
#include "Oracle.hpp"
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <exception>
using namespace std;

OracleMemoryDAO::OracleMemoryDAO() {
	fstream file;
	string line, date;
	double rate;
	char separator = ' ';
	Oracle oracle;

	try{
		file.open("oracle.txt");
		while(getline(file,line)){
			date = line.substr(0,10);
			rate = stod(line.substr(11,7));
			oracle.setDate(date);
			oracle.setRate(rate);
			oracles.push_back(oracle);
		}
		file.close();
	}catch(exception e){
		cerr << " Error opening Oracle file: " << e.what() << endl;
	}

}

OracleMemoryDAO::~OracleMemoryDAO(){

}

bool OracleMemoryDAO::addOracle(const Oracle& oracle) {
    for (const auto& o : oracles) {
        if (o.getDate() == oracle.getDate()) {
            return false; // Entry for this date already exists
        }
    }
    oracles.push_back(oracle);
    return true;
}

Oracle* OracleMemoryDAO::getOracleByDate(const string& date){
	auto it = find_if(oracles.begin(), oracles.end(),[date](const Oracle& o) {return o.getDate() == date; });

	if (it != oracles.end()) {
		return &(*it);
	}
    return nullptr;
}

vector<Oracle> OracleMemoryDAO::getAllOracles()  {
    return oracles;
}

bool OracleMemoryDAO::updateOracle(const Oracle& oracle) {
    for (auto& o : oracles) {
        if (o.getDate() == oracle.getDate()) {
            o = oracle;
            return true;
        }
    }
    return false;
}

bool OracleMemoryDAO::deleteOracle(const string& date) {
    for (auto it = oracles.begin(); it != oracles.end(); ++it) {
        if (it->getDate() == date) {
            oracles.erase(it);
            return true;
        }
    }
    return false;
}
