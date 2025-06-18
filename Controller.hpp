#ifndef CONTROLLLER_HPP
#define CONTROLLER_HPP

#include "WalletDAO.hpp"
#include "TransactionDAO.hpp"
#include "OracleDAO.hpp"

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

	//menu
	void walletMenu();
	void transactionMenu();
	void reportMenu();
	void menuHelp();

	//wallet
	void newWallet();
	bool getWalletById();
	void seeWallet();
	void editWallet();
	void deleteWallet();

public:
	Controller();
	virtual ~Controller();
	void start();

};

#endif

