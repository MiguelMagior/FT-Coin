#ifndef WALLET_DB_DAO_HPP
#define WALLET_DB_DAO_HPP

#include <vector>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
#include "Wallet.hpp"
#include "WalletDAO.hpp"
using namespace std;

class WalletDBDAO : public WalletDAO{
private:
    unique_ptr<sql::Connection> conn;

public:
    WalletDBDAO();  //Construtor padrão
    WalletDBDAO(const string& uri, const string& user, const string& password, const string& database);
    ~WalletDBDAO();

    bool addWallet(const Wallet& wallet);
    Wallet* getWalletById(int id);
    bool updateWallet(const Wallet& wallet);
    bool deleteWallet(int id);
    vector<Wallet> getAllWallets();
};

#endif // WALLET_DB_DAO_HPP
