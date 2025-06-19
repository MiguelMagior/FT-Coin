#ifndef ORACLE_DB_DAO_HPP
#define ORACLE_DB_DAO_HPP

#include <vector>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
using namespace std;

#include "Oracle.hpp"

class OracleDBDAO : public OracleDAO{
private:
    unique_ptr<sql::Connection> conn;

public:
    OracleDBDAO(const string& uri, const string& user, const string& password, const string& database);

    bool addOracleRecord(const string& date, double rate);
    optional<pair<string, double>> getOracleRecordByDate(const string& date) const;
    bool updateOracleRecord(const string& date, double rate);
    bool deleteOracleRecord(const string& date);
    vector<pair<string, double>> getAllOracleRecords() const;
};

#endif // ORACLE_DB_DAO_HPP
