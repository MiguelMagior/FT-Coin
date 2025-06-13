#include "OracleDBDAO.hpp"
#include <iostream>

OracleDBDAO::OracleDBDAO(const std::string& uri, const std::string& user, const std::string& password, const std::string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = std::unique_ptr<sql::Connection>(driver->connect(uri, user, password));
        conn->setSchema(database);
    } catch (sql::SQLException& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        throw;
    }
}

bool OracleDBDAO::addOracleRecord(const std::string& date, double rate) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO Oracle (Data, Taxa) VALUES (?, ?)"));
        pstmt->setString(1, date);
        pstmt->setDouble(2, rate);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "Insert error: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::pair<std::string, double>> OracleDBDAO::getOracleRecordByDate(const std::string& date) const {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT Data, Taxa FROM Oracle WHERE Data = ?"));
        pstmt->setString(1, date);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            std::string d(res->getString("Data").c_str());
            double rate = res->getDouble("Taxa");
            return std::make_pair(d, rate);
        }
        return std::nullopt;
    } catch (sql::SQLException& e) {
        std::cerr << "Query error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool OracleDBDAO::updateOracleRecord(const std::string& date, double rate) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("UPDATE Oracle SET Taxa = ? WHERE Data = ?"));
        pstmt->setDouble(1, rate);
        pstmt->setString(2, date);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        std::cerr << "Update error: " << e.what() << std::endl;
        return false;
    }
}

bool OracleDBDAO::deleteOracleRecord(const std::string& date) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("DELETE FROM Oracle WHERE Data = ?"));
        pstmt->setString(1, date);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        std::cerr << "Delete error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::pair<std::string, double>> OracleDBDAO::getAllOracleRecords() const {
    std::vector<std::pair<std::string, double>> records;
    try {
        std::unique_ptr<sql::Statement> stmt(conn->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT Data, Taxa FROM Oracle"));

        while (res->next()) {
            std::string d(res->getString("Data").c_str());
            double rate = res->getDouble("Taxa");
            records.emplace_back(d, rate);
        }
    } catch (sql::SQLException& e) {
        std::cerr << "Select all error: " << e.what() << std::endl;
    }
    return records;
}
