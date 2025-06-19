#include "WalletMemoryDAO.hpp"
#include <algorithm>
using namespace std;

WalletMemoryDAO::WalletMemoryDAO() : wallets() {}

bool WalletMemoryDAO::addWallet(const Wallet& wallet) {
    // Check if id already exists
    auto it = find_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
        return w.getId() == wallet.getId();
    });
    if (it != wallets.end()) {
        return false; // already exists
    }
    wallets.push_back(wallet);
    return true;
}

Wallet* WalletMemoryDAO::getWalletById(int id){
	auto it = find_if(wallets.begin(), wallets.end(),[id](const Wallet& w) { return w.getId() == id; });

	if (it != wallets.end()) {
		return &(*it);
	}
	return nullptr;
}

bool WalletMemoryDAO::updateWallet(const Wallet& wallet) {
    auto it = find_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
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
    auto it = remove_if(wallets.begin(), wallets.end(), [&](const Wallet& w) {
        return w.getId() == id;
    });
    if (it != wallets.end()) {
        wallets.erase(it, wallets.end());
        return true;
    }
    return false;
}

vector<Wallet> WalletMemoryDAO::getAllWallets(){
    return wallets;
}
