#ifndef ORACLE_DB_DAO_HPP
#define ORACLE_DB_DAO_HPP

#include <vector>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
using namespace std;

#include "Oracle.hpp"
#include "OracleDAO.hpp"

class OracleDBDAO : public OracleDAO {
private:
    unique_ptr<sql::Connection> conn;

public:
    OracleDBDAO(const string& uri, const string& user, const string& password, const string& database);
    bool isOracleTableEmpty();

    bool addOracle(const Oracle& oracle);
    Oracle* getOracleByDate(const string& date);
    bool updateOracle(const Oracle& oracle);
    bool deleteOracle(const string& date);
    vector<Oracle> getAllOracles();

};

#endif // ORACLE_DB_DAO_HPP
