#include "WalletMemoryDAO.hpp"
#include <algorithm>

WalletMemoryDAO::WalletMemoryDAO() : wallets() {}

bool WalletMemoryDAO::addWallet(const Wallet& wallet) {
    // Check if id already exists
    auto it = std::find_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
        return w.getId() == wallet.getId();
    });
    if (it != wallets.end()) {
        return false; // already exists
    }
    wallets.push_back(wallet);
    return true;
}

std::optional<Wallet> WalletMemoryDAO::getWalletById(int id) const {
    auto it = std::find_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
        return w.getId() == id;
    });
    if (it != wallets.end()) {
        return *it;
    }
    return std::nullopt;
}

bool WalletMemoryDAO::updateWallet(const Wallet& wallet) {
    auto it = std::find_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
        return w.getId() == wallet.getId();
    });
    if (it != wallets.end()) {
        it->setHolderName(wallet.getHolderName());
        it->setBroker(wallet.getBroker());
        return true;
    }
    return false;
}

bool WalletMemoryDAO::deleteWallet(int id) {
    auto it = std::remove_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
        return w.getId() == id;
    });
    if (it != wallets.end()) {
        wallets.erase(it, wallets.end());
        return true;
    }
    return false;
}

std::vector<Wallet> WalletMemoryDAO::getAllWallets() const {
    return wallets;
}
