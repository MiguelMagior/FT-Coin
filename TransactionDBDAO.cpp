#include "TransactionDBDAO.hpp"
#include <iostream>
using namespace std;

TransactionDBDAO::TransactionDBDAO(const string& uri, const string& user, const string& password, const string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = unique_ptr<sql::Connection>(driver->connect(uri, user, password));
        conn->setSchema(database);
    } catch (sql::SQLException& e) {
        cerr << "Connection error: " << e.what() << endl;
        throw;
    }
}

bool TransactionDBDAO::addTransaction(int walletId, int transactionId, const string& date, char type, double amount) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO Transacao (carteira_id, id, data, tipo, valor) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setInt(1, walletId);
        pstmt->setInt(2, transactionId);
        pstmt->setString(3, date);
        pstmt->setString(4, string(1, type));
        pstmt->setDouble(5, amount);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException& e) {
        cerr << "Insert error: " << e.what() << endl;
        return false;
    }
}

optional<tuple<int, int, string, char, double>> TransactionDBDAO::getTransaction(int walletId, int transactionId) const {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT carteira_id, id, data, tipo, valor FROM Transacao WHERE carteira_id = ? AND id = ?"));
        pstmt->setInt(1, walletId);
        pstmt->setInt(2, transactionId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            int wId = res->getInt("carteira_id");
            int tId = res->getInt("id");
            string date = string(res->getString("data").c_str());
            string typeStr = string(res->getString("tipo").c_str());
            char type = !typeStr.empty() ? typeStr[0] : ' ';
            double amount = res->getDouble("valor");
            return make_tuple(wId, tId, date, type, amount);
        }
        return nullopt;
    } catch (sql::SQLException& e) {
        cerr << "Query error: " << e.what() << endl;
        return nullopt;
    }
}

bool TransactionDBDAO::updateTransaction(int walletId, int transactionId, const string& date, char type, double amount) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("UPDATE Transacao SET data = ?, tipo = ?, valor = ? WHERE carteira_id = ? AND id = ?"));
        pstmt->setString(1, date);
        pstmt->setString(2, string(1, type));
        pstmt->setDouble(3, amount);
        pstmt->setInt(4, walletId);
        pstmt->setInt(5, transactionId);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        cerr << "Update error: " << e.what() << endl;
        return false;
    }
}

bool TransactionDBDAO::deleteTransaction(int walletId, int transactionId) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("DELETE FROM Transacao WHERE carteira_id = ? AND id = ?"));
        pstmt->setInt(1, walletId);
        pstmt->setInt(2, transactionId);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        cerr << "Delete error: " << e.what() << endl;
        return false;
    }
}

vector<tuple<int, int, string, char, double>> TransactionDBDAO::getAllTransactions(int walletId) const {
    vector<tuple<int, int, string, char, double>> transactions;
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT carteira_id, id, data, tipo, valor FROM Transacao WHERE carteira_id = ?"));
        pstmt->setInt(1, walletId);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            int wId = res->getInt("carteira_id");
            int tId = res->getInt("id");
            string date = string(res->getString("data").c_str());
            string typeStr = string(res->getString("tipo").c_str());
            char type = !typeStr.empty() ? typeStr[0] : ' ';
            double amount = res->getDouble("valor");
            transactions.emplace_back(wId, tId, date, type, amount);
        }
    } catch (sql::SQLException& e) {
        cerr << "Select all error: " << e.what() << endl;
    }
    return transactions;
}
