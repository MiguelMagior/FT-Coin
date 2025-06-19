#ifndef WALLETDAO_HPP
#define WALLETDAO_HPP

#include "Wallet.hpp"
#include <vector>
using namespace std;

class WalletDAO{
public:
	WalletDAO();
	virtual ~WalletDAO();

	virtual bool addWallet(const Wallet& wallet) = 0;
	virtual Wallet* getWalletById(int id) = 0;
	virtual bool updateWallet(const Wallet& wallet) = 0;
	virtual bool deleteWallet(int id) = 0;
	virtual vector<Wallet> getAllWallets() = 0;
};
#endif
