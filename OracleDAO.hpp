#ifndef ORACLEDAO_HPP
#define ORACLEDAO_HPP

#include <vector>
#include <string>
using namespace std;

#include "Oracle.hpp"

class OracleDAO{
public:
	OracleDAO();
	virtual ~OracleDAO();

	virtual bool addOracle(const Oracle& oracle) = 0;
	virtual Oracle* getOracleByDate(const string& date) = 0;
	virtual vector<Oracle> getAllOracles() const = 0;
	virtual bool updateOracle(const Oracle& oracle) = 0;
	virtual bool deleteOracle(const string& date) = 0;
};
#endif
