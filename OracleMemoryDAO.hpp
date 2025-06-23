#ifndef ORACLE_MEMORY_DAO_HPP
#define ORACLE_MEMORY_DAO_HPP

#include <vector>
#include <optional>
#include <string>
#include "Oracle.hpp"
#include "OracleMemoryDAO.hpp"
#include "OracleDAO.hpp"
using namespace std;

class OracleMemoryDAO : public OracleDAO{
private:
    vector<Oracle> oracles;

public:
    OracleMemoryDAO();

    bool addOracle(const Oracle& oracle);
    Oracle* getOracleByDate(const string& date);
    vector<Oracle> getAllOracles();
    bool updateOracle(const Oracle& oracle);
    bool deleteOracle(const string& date);
};

#endif // ORACLE_MEMORY_DAO_HPP
