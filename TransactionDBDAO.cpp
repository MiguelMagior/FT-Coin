#include "TransactionDBDAO.hpp"
#include <iostream>

TransactionDBDAO::TransactionDBDAO(const std::string& uri, const std::string& user, const std::string& password, const std::string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = std::unique_ptr<sql::Connection>(driver->connect(uri, user, password));
        conn->setSchema(database);
    } catch (sql::SQLException& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        throw;
    }
}

bool TransactionDBDAO::addTransaction(int walletId, int transactionId, const std::string& date, char type, double amount) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO Transacao (carteira_id, id, data, tipo, valor) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setInt(1, walletId);
        pstmt->setInt(2, transactionId);
        pstmt->setString(3, date);
        pstmt->setString(4, std::string(1, type));
        pstmt->setDouble(5, amount);
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException& e) {
        std::cerr << "Insert error: " << e.what() << std::endl;
        return false;
    }
}

std::optional<std::tuple<int, int, std::string, char, double>> TransactionDBDAO::getTransaction(int walletId, int transactionId) const {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT carteira_id, id, data, tipo, valor FROM Transacao WHERE carteira_id = ? AND id = ?"));
        pstmt->setInt(1, walletId);
        pstmt->setInt(2, transactionId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            int wId = res->getInt("carteira_id");
            int tId = res->getInt("id");
            std::string date = std::string(res->getString("data").c_str());
            std::string typeStr = std::string(res->getString("tipo").c_str());
            char type = !typeStr.empty() ? typeStr[0] : ' ';
            double amount = res->getDouble("valor");
            return std::make_tuple(wId, tId, date, type, amount);
        }
        return std::nullopt;
    } catch (sql::SQLException& e) {
        std::cerr << "Query error: " << e.what() << std::endl;
        return std::nullopt;
    }
}

bool TransactionDBDAO::updateTransaction(int walletId, int transactionId, const std::string& date, char type, double amount) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("UPDATE Transacao SET data = ?, tipo = ?, valor = ? WHERE carteira_id = ? AND id = ?"));
        pstmt->setString(1, date);
        pstmt->setString(2, std::string(1, type));
        pstmt->setDouble(3, amount);
        pstmt->setInt(4, walletId);
        pstmt->setInt(5, transactionId);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        std::cerr << "Update error: " << e.what() << std::endl;
        return false;
    }
}

bool TransactionDBDAO::deleteTransaction(int walletId, int transactionId) {
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("DELETE FROM Transacao WHERE carteira_id = ? AND id = ?"));
        pstmt->setInt(1, walletId);
        pstmt->setInt(2, transactionId);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        std::cerr << "Delete error: " << e.what() << std::endl;
        return false;
    }
}

std::vector<std::tuple<int, int, std::string, char, double>> TransactionDBDAO::getAllTransactions(int walletId) const {
    std::vector<std::tuple<int, int, std::string, char, double>> transactions;
    try {
        std::unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT carteira_id, id, data, tipo, valor FROM Transacao WHERE carteira_id = ?"));
        pstmt->setInt(1, walletId);
        std::unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        while (res->next()) {
            int wId = res->getInt("carteira_id");
            int tId = res->getInt("id");
            std::string date = std::string(res->getString("data").c_str());
            std::string typeStr = std::string(res->getString("tipo").c_str());
            char type = !typeStr.empty() ? typeStr[0] : ' ';
            double amount = res->getDouble("valor");
            transactions.emplace_back(wId, tId, date, type, amount);
        }
    } catch (sql::SQLException& e) {
        std::cerr << "Select all error: " << e.what() << std::endl;
    }
    return transactions;
}
