#ifndef TRANSACTION_DB_DAO_HPP
#define TRANSACTION_DB_DAO_HPP

#include <vector>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
using namespace std;

class TransactionDBDAO {
private:
    unique_ptr<sql::Connection> conn;

public:
    TransactionDBDAO(const string& uri, const string& user, const string& password, const string& database);

    bool addWallet(const Wallet& wallet);
    Wallet* getWalletById(int id);
    bool updateWallet(const Wallet& wallet);
    bool deleteWallet(int id);
    vector<Wallet> getAllWallets();
};

#endif // TRANSACTION_DB_DAO_HPP
