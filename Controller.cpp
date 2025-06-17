#include "Controller.hpp"
#include "Menu.hpp"
#include <vector>
#include "WalletMemoryDAO.hpp"
#include "TransactionMemoryDAO.hpp"
#include "OracleMemoryDAO.hpp"
#include "Wallet.hpp"

#include <string>
#include <iostream>
using namespace std;

Controller::Controller(){
	wallets = new WalletMemoryDAO();
	transactions = new TransactionMemoryDAO();
	oracle = new OracleMemoryDAO();
}
Controller::~Controller(){
}
void Controller::teste(){
	cout << "AINDA NÃO IMPLEMENTADO" << endl;
}
void Controller::start(){
	vector<string> menuItens{
		"Wallet", "Transaction", "Report", "Help", "Close"
	};
	vector<void (Controller::*)()> functions{
		&Controller::walletMenu, &Controller::transactionMenu, &Controller::reportMenu, &Controller::menuHelp
	};
	launchMenu(menuItens, "FT-COIN", functions);
}

void Controller::launchMenu(vector<string> menuItens, string title, vector<void (Controller::*)()> functions){
	Menu menu(menuItens, title);
	int choice;

	while(choice = menu.getChoice()){
		if(choice == menuItens.size()){
			break;
		}
		(this->*functions.at(choice-1))();
	}
}

void Controller::walletMenu(){
	vector<string> menuItens{
		"New Wallet", "See Wallet", "Edit Wallet", "Delete Wallet", "Return"
	};
	vector<void (Controller::*)()> functions{
		&Controller::newWallet, &Controller::seeWallet, &Controller::editWallet, &Controller::deleteWallet
	};
	launchMenu(menuItens, "Wallet", functions);
}

void Controller::transactionMenu(){
	vector<string> menuItens{
		"Register Purchase", "Register Sale", "Return"
	};
	vector<void (Controller::*)()> functions{
		&Controller::teste, &Controller::teste
	};
	launchMenu(menuItens, "Transaction", functions);
}

void Controller::reportMenu(){
	vector<string> menuItens{
		"Wallets by ID", "Wallets by Name", "Wallet Balance", "Transaction History", "Wallet Balance","Return"
	};
	vector<void (Controller::*)()> functions{
		&Controller::teste, &Controller::teste, &Controller::teste, &Controller::teste, &Controller::teste
	};
	launchMenu(menuItens, "Transaction", functions);
}
void Controller::menuHelp(){
	teste();
}

void Controller::newWallet(){
	string holderName, broker;
	Wallet newWallet;

	cin.ignore();
	cout << " *** NEW WALLET ***" << endl;
	cout << " Holder Name: ";
	getline(cin, holderName);
	cout << " Broker: ";
	getline(cin, broker);

	newWallet.setId(newWallet.getId());
	newWallet.setHolderName(holderName);
	newWallet.setBroker(broker);

	switch(wallets->addWallet(newWallet)){
	case true:
		cout << " Wallet added successfully" << endl;
		break;
	default:
		cout << " Error adding Wallet" << endl;
	}
}

void Controller::getWalletById(){
	int id;
	cin.ignore();
	cout << " ID: ";
	cin >> id;

	const Wallet* wallet = wallets->getWalletById(id);


	if (wallet != nullptr) {
        cout << *wallet << endl;
	}
	else {
		cout << "Wallet with ID " << id << " not found!" << endl;
	 }
}
void Controller::seeWallet(){
	cout << endl << " *** SEE WALLET ***" << endl;
	getWalletById();
}

void Controller::editWallet(){
	string holderName, broker;
	int id;

	cout << " *** EDIT WALLET ***" << endl;
	cout << " ID: ";
	cin >> id;

	Wallet* wallet = wallets->getWalletById(id);

	cin.ignore();
	cout << " Holder Name: ";
	getline(cin, holderName);
	cout << " Broker: ";
	getline(cin, broker);

	wallet->setHolderName(holderName);
	wallet->setBroker(broker);
}

void Controller::deleteWallet(){
	int id;

	cout << " *** DELETE WALLET ***" << endl;
	cout << " ID: ";
	cin >> id;

	switch(wallets->deleteWallet(id)){
	case true:
		cout << " Wallet deleted successfully" << endl;
		break;
	default:
		cout << " Error deleting wallet" << endl;
	}
}
