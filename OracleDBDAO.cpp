#include "OracleDBDAO.hpp"
#include <iostream>
#include <fstream>
using namespace std;

OracleDBDAO::OracleDBDAO(const string& uri, const string& user, const string& password, const string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = unique_ptr<sql::Connection>(driver->connect(uri, user, password));
        conn->setSchema(database);

        if (isOracleTableEmpty()) {
            fstream file;
            string line, date;
            double rate;
            Oracle oracle;

            file.open("oracle.txt");
            if (!file.is_open()) {
                throw runtime_error("Failed to open oracle.txt");
            }

            while (getline(file, line)) {
                date = line.substr(0, 10);
                rate = stod(line.substr(11, 7));
                oracle.setDate(date);
                oracle.setRate(rate);
                addOracle(oracle);
            }
            file.close();
        }
    } catch (sql::SQLException& e) {
        cerr << "SQL Error: " << e.what() << endl;
        throw;
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        throw;
    }
}

bool OracleDBDAO::isOracleTableEmpty() {
    unique_ptr<sql::Statement> stmt(conn->createStatement());
    unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT COUNT(*) FROM oracle_rates"));
    res->next();
    return (res->getInt(1) == 0);
}

bool OracleDBDAO::addOracle(const Oracle& oracle) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO Oracle (Data, Taxa) VALUES (?, ?)"));
        pstmt->setString(1, oracle.getDate());
        pstmt->setDouble(2, oracle.getRate());
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException& e) {
        cerr << "Insert error: " << e.what() << endl;
        return false;
    }
}

Oracle* OracleDBDAO::getOracleByDate(const string& date){
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT Data, Taxa FROM Oracle WHERE Data = ?"));
        pstmt->setString(1, date);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            string d(res->getString("Data").c_str());
            double rate = res->getDouble("Taxa");
            Oracle* oracle = new Oracle(d, rate);
            return oracle;
        }
        return nullptr;
    } catch (sql::SQLException& e) {
        cerr << "Query error: " << e.what() << endl;
        return nullptr;
    }
}

bool OracleDBDAO::updateOracle(const Oracle& oracle) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("UPDATE Oracle SET Taxa = ? WHERE Data = ?"));
        pstmt->setDouble(1, oracle.getRate());
        pstmt->setString(2, oracle.getDate());
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        cerr << "Update error: " << e.what() << endl;
        return false;
    }
}

bool OracleDBDAO::deleteOracle(const string& date) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("DELETE FROM Oracle WHERE Data = ?"));
        pstmt->setString(1, date);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        cerr << "Delete error: " << e.what() << endl;
        return false;
    }
}

vector<Oracle> OracleDBDAO::getAllOracles(){
    vector<Oracle> records;
    try {
        unique_ptr<sql::Statement> stmt(conn->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT Data, Taxa FROM Oracle"));

        while (res->next()) {
            string d(res->getString("Data").c_str());
            double rate = res->getDouble("Taxa");
            records.emplace_back(d, rate);
        }
    } catch (sql::SQLException& e) {
        cerr << "Select all error: " << e.what() << endl;
    }
    return records;
}
