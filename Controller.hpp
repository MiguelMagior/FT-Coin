#ifndef CONTROLLLER_HPP
#define CONTROLLER_HPP

#include "WalletDAO.hpp"
#include "TransactionDAO.hpp"
#include "OracleDAO.hpp"
#include "DataBaseType.hpp"

#include <string>
#include <vector>

using namespace std;

class Controller {
private:
	WalletDAO *wallets;
	TransactionDAO *transactions;
	OracleDAO *oracle;

	void launchMenu(vector<string> menuItens, string title, vector<void (Controller::*)()> functions);
	void teste();
	void populate();
	int getId();
	//menu
	void walletMenu();
	void transactionMenu();
	void reportMenu();
	void menuHelp();

	//wallet
	void newWallet();
	bool findWalletById(int id);
	void seeWallet();
	void editWallet();
	void deleteWallet();
	int getLastWalletId();

	//transaction
	void registerTransaction(char type);
	vector<Transaction> getAllWalletTransactions(int walletId);
	void registerPurchase();
	void registerSale();
	double getWalletBalance(int walletId);
	void printWalletTransactions(int walletId);

	//report
	void reportWalletById();
	void reportWalletByName();
	void reportWalletBalance();
	void reportTransactionHistory();

	//help
	void printCredits();
	void printHelp();
public:
	Controller(DataBaseType dbType);
	virtual ~Controller();
	void start();

};

#endif

