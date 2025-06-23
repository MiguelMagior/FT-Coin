#include "OracleMemoryDAO.hpp"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

OracleMemoryDAO::OracleMemoryDAO() {}

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
