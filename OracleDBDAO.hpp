#ifndef ORACLE_DB_DAO_HPP
#define ORACLE_DB_DAO_HPP

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>

class OracleDBDAO {
private:
    std::unique_ptr<sql::Connection> conn;

public:
    OracleDBDAO(const std::string& uri, const std::string& user, const std::string& password, const std::string& database);

    bool addOracleRecord(const std::string& date, double rate);
    std::optional<std::pair<std::string, double>> getOracleRecordByDate(const std::string& date) const;
    bool updateOracleRecord(const std::string& date, double rate);
    bool deleteOracleRecord(const std::string& date);
    std::vector<std::pair<std::string, double>> getAllOracleRecords() const;
};

#endif // ORACLE_DB_DAO_HPP
