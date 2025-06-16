#ifndef WALLET_MEMORY_DAO_HPP
#define WALLET_MEMORY_DAO_HPP

#include <vector>
#include <optional>
#include "Wallet.hpp"
#include "WalletDAO.hpp"

class WalletMemoryDAO : public WalletDAO {
private:
    std::vector<Wallet> wallets;

public:
    WalletMemoryDAO();

    bool addWallet(const Wallet& wallet);
    std::optional<Wallet> getWalletById(int id) const;
    bool updateWallet(const Wallet& wallet);
    bool deleteWallet(int id);
    std::vector<Wallet> getAllWallets() const;
};

#endif // WALLET_MEMORY_DAO_HPP
