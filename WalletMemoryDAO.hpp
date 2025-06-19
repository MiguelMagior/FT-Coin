#ifndef WALLET_MEMORY_DAO_HPP
#define WALLET_MEMORY_DAO_HPP

#include <vector>
#include "Wallet.hpp"
#include "WalletDAO.hpp"
using namespace std;

class WalletMemoryDAO : public WalletDAO {
private:
    vector<Wallet> wallets;

public:
    WalletMemoryDAO();

    bool addWallet(const Wallet& wallet);
    virtual Wallet* getWalletById(int id);
    bool updateWallet(const Wallet& wallet);
    bool deleteWallet(int id);
    vector<Wallet> getAllWallets();
};

#endif // WALLET_MEMORY_DAO_HPP
