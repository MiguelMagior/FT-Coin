#include "TransactionDBDAO.hpp"
#include <iostream>
#include <vector>
using namespace std;

TransactionDBDAO::TransactionDBDAO(const string& uri, const string& user, const string& password, const string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = unique_ptr<sql::Connection>(driver->connect(uri, user, password));
        conn->setSchema(database);
    } catch (sql::SQLException& e) {
        cerr << "Connectvector<tuple<int, int, string, char, double>>ion error: " << e.what() << endl;
        throw;
    }
}

bool TransactionDBDAO::addTransaction(const Transaction& transaction) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO Transacao (carteira_id, id, data, tipo, valor) VALUES (?, ?, ?, ?, ?)"));
        pstmt->setInt(1, transaction.getWalletId());
        pstmt->setInt(2, transaction.getTransactionId());
        pstmt->setString(3, transaction.getDate());
        pstmt->setString(4, string(1, transaction.getType()));
        pstmt->setDouble(5, transaction.getAmount());
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException& e) {
        cerr << "Insert error: " << e.what() << endl;
        return false;
    }
}

Transaction* TransactionDBDAO::getTransactionById(int id){
    try {
    	unique_ptr<sql::PreparedStatement> pstmt(
    	            conn->prepareStatement("SELECT carteira_id, id, data, tipo, valor FROM Transacao WHERE id = ?"));
    	pstmt->setInt(1, id);
    	unique_ptr<sql::ResultSet> res(pstmt->executeQuery());
        if (res->next()) {
            int wId = res->getInt("carteira_id");
            int tId = res->getInt("id");
            string date = string(res->getString("data").c_str());
            string typeStr = string(res->getString("tipo").c_str());
            char type = !typeStr.empty() ? typeStr[0] : ' ';
            double amount = res->getDouble("valor");
            Transaction* transaction = new Transaction(wId, tId, date, type, amount);
            return transaction;
        }
        return nullptr;
    } catch (sql::SQLException& e) {
        cerr << "Query error: " << e.what() << endl;
        return nullptr;
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

bool TransactionDBDAO::deleteTransaction(int id) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("DELETE FROM Transacao WHERE id = ?"));
        pstmt->setInt(1, id);
        int rowsAffected = pstmt->executeUpdate();
        return (rowsAffected > 0);
    } catch (sql::SQLException& e) {
        cerr << "Delete error: " << e.what() << endl;
        return false;
    }
}
vector<Transaction> TransactionDBDAO::getAllTransactions() {
    vector<Transaction> transactions;
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT carteira_id, id, data, tipo, valor FROM Transacao"));
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
        cerr << "Error getting all transactions: " << e.what() << endl;
    }
    return transactions;
}

vector<Transaction> TransactionDBDAO::getTransactionsByWalletId(int walletId) {
	vector<Transaction> transactions;
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
