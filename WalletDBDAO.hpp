#ifndef WALLET_DB_DAO_HPP
#define WALLET_DB_DAO_HPP

#include <vector>
#include <optional>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
#include "Wallet.hpp"

class WalletDBDAO {
private:
    std::unique_ptr<sql::Connection> conn;

public:
    WalletDBDAO();  //Construtor padrão
    WalletDBDAO(const std::string& uri, const std::string& user, const std::string& password, const std::string& database);
    ~WalletDBDAO();

    bool addWallet(const Wallet& wallet);
    std::optional<Wallet> getWalletById(int id) const;
    bool updateWallet(const Wallet& wallet);
    bool deleteWallet(int id);
    std::vector<Wallet> getAllWallets() const;
};

#endif // WALLET_DB_DAO_HPP
