#include "WalletDBDAO.hpp"
#include <iostream>
#include <vector>
#include <memory>
using namespace std;

WalletDBDAO::WalletDBDAO() {
    string host = "143.106.234.64";
    string user = "Pool_25_A03";
    string password = "SwNWcvIM94";
    string database = "Pool_25_A03";

    // Declara driver como variável local aqui
    sql::Driver* driver = sql::mariadb::get_driver_instance();
    conn = unique_ptr<sql::Connection>(driver->connect(host, user, password));
    conn->setSchema(database);
}

WalletDBDAO::WalletDBDAO(const string& uri, const string& user, const string& password, const string& database) {
    try {
        sql::Driver* driver = sql::mariadb::get_driver_instance();
        conn = unique_ptr<sql::Connection>(driver->connect(uri, user, password));
        conn->setSchema(database);
    } catch (sql::SQLException& e) {
        cerr << "Connection error: " << e.what() << endl;
        throw;
    }
}

WalletDBDAO::~WalletDBDAO() {
    if (conn) {
        conn->close();
    }
}

bool WalletDBDAO::addWallet(const Wallet& wallet) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("INSERT INTO Carteira (Identificador, Nome_do_titular, Corretora) VALUES (?, ?, ?)"));
        pstmt->setInt(1, wallet.getId());
        pstmt->setString(2, wallet.getHolderName());
        pstmt->setString(3, wallet.getBroker());
        pstmt->executeUpdate();
        return true;
    } catch (sql::SQLException& e) {
        cerr << "Insert error: " << e.what() << endl;
        return false;
    }
}

Wallet* WalletDBDAO::getWalletById(int id){
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("SELECT Identificador, Nome_do_titular, Corretora FROM Carteira WHERE Identificador = ?"));
        pstmt->setInt(1, id);
        unique_ptr<sql::ResultSet> res(pstmt->executeQuery());

        if (res->next()) {
            Wallet* wallet = new Wallet();
            wallet->setId(res->getInt("Identificador"));

            string holderName = res->getString("Nome_do_titular").c_str();
            string broker = res->getString("Corretora").c_str();

            wallet->setHolderName(holderName);
            wallet->setBroker(broker);

            return wallet;
        }
        return nullptr;
    } catch (sql::SQLException& e) {
        cerr << "Query error: " << e.what() << endl;
        return nullptr;
    }
}

bool WalletDBDAO::updateWallet(const Wallet& wallet) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("UPDATE Carteira SET Nome_do_titular = ?, Corretora = ? WHERE Identificador = ?"));
        pstmt->setString(1, wallet.getHolderName());
        pstmt->setString(2, wallet.getBroker());
        pstmt->setInt(3, wallet.getId());
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        cerr << "Update error: " << e.what() << endl;
        return false;
    }
}

bool WalletDBDAO::deleteWallet(int id) {
    try {
        unique_ptr<sql::PreparedStatement> pstmt(
            conn->prepareStatement("DELETE FROM Carteira WHERE Identificador = ?"));
        pstmt->setInt(1, id);
        int affectedRows = pstmt->executeUpdate();
        return affectedRows > 0;
    } catch (sql::SQLException& e) {
        cerr << "Delete error: " << e.what() << endl;
        return false;
    }
}

vector<Wallet> WalletDBDAO::getAllWallets(){
    vector<Wallet> wallets;
    try {
        unique_ptr<sql::Statement> stmt(conn->createStatement());
        unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT Identificador, Nome_do_titular, Corretora FROM Carteira"));

        while (res->next()) {
            Wallet wallet;
            wallet.setId(res->getInt("Identificador"));

            string holderName = res->getString("Nome_do_titular").c_str();
            string broker = res->getString("Corretora").c_str();

            wallet.setHolderName(holderName);
            wallet.setBroker(broker);
            wallets.push_back(wallet);
        }
    } catch (sql::SQLException& e) {
        cerr << "Select all error: " << e.what() << endl;
    }
    return wallets;
}
