#ifndef WALLETDAO_HPP
#define WALLETDAO_HPP

#include "Wallet.hpp"

class WalletDAO{
public:
	WalletDAO();
	virtual ~WalletDAO();

	virtual bool addWallet(const Wallet& wallet) = 0;
	virtual Wallet* getWalletById(int id) = 0;
	virtual bool updateWallet(const Wallet& wallet) = 0;
	virtual bool deleteWallet(int id) = 0;
};
#endif
