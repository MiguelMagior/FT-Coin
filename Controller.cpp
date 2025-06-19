#include "Controller.hpp"
#include "Menu.hpp"
#include "WalletMemoryDAO.hpp"
#include "TransactionMemoryDAO.hpp"
#include "OracleMemoryDAO.hpp"
#include "Wallet.hpp"
#include "Utils.hpp"

#include <vector>
#include <string>
#include <iostream>
using namespace std;

Controller::Controller(){
	wallets = new WalletMemoryDAO();
	transactions = new TransactionMemoryDAO();
	oracle = new OracleMemoryDAO();
}
Controller::~Controller(){
	delete oracle;
	delete transactions;
	delete wallets;
	cout << " Program closed " << endl;
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
		&Controller::reportWalletById, &Controller::reportWalletByName, &Controller::teste, &Controller::teste, &Controller::teste
	};
	launchMenu(menuItens, "Transaction", functions);
}
void Controller::menuHelp(){
	vector<string> menuItens{
		"Tutorial", "Credits", "Test Populate", "Return"
	};
	vector<void (Controller::*)()> functions{
		&Controller::teste, &Controller::teste, &Controller::populate
	};
	launchMenu(menuItens, "Help", functions);
}

void Controller::populate(){
	wallets->addWallet(Wallet("Lucas", "Broker1"));
	wallets->addWallet(Wallet("Adriane", "Broker1"));
	wallets->addWallet(Wallet("Henrique", "Broker1"));

	cout << "Memory populated" << endl;
}

// **** WALLET ****  //
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

bool Controller::getWalletById(){
	int id;
	cin.ignore();
	cout << " ID: ";
	id = validInt();

	const Wallet* wallet = wallets->getWalletById(id);

	if (wallet != nullptr) {
        cout << *wallet << endl;
        return true;
	}
	else {
		cout << "Wallet with ID " << id << " not found!" << endl;
		return false;
	}
}
void Controller::seeWallet(){
	cout << endl << " *** SEE WALLET ***" << endl;
	getWalletById();
}

void Controller::editWallet(){
	string holderName, broker;
	int id;
	Wallet* wallet;

	cout << " *** EDIT WALLET ***" << endl;

	if(getWalletById()){
		wallet = wallets->getWalletById(id);
		cin.ignore();
		cout << " Holder Name: ";
		getline(cin, holderName);
		cout << " Broker: ";
		getline(cin, broker);

		wallet->setHolderName(holderName);
		wallet->setBroker(broker);
	}
}

void Controller::deleteWallet(){
	int id;

	cout << " *** DELETE WALLET ***" << endl;

	if(getWalletById()){
		wallets->deleteWallet(id);
		cout << " Wallet deleted successfully" << endl;
	}
	else{
		cout << " Error deleting wallet" << endl;
	}
}

// **** REPORTS ****  //
void Controller::reportWalletById(){
	vector<Wallet> allWallets = wallets->getAllWallets();

	cout << " *** Wallets by ID ***" << endl;
	for(int index = 0; index < allWallets.size(); index++){
		cout << allWallets.at(index) << endl;
	}
}

void Controller::reportWalletByName(){
	int index = 0;
	vector<string> names;
	vector<Wallet> allWallets = wallets->getAllWallets();

	for(int index = 0; index < allWallets.size(); index++){
		if(!isDuplicated(names, allWallets.at(index).getHolderName())){
			names.push_back(allWallets.at(index).getHolderName());
		}
	}
	names = sortAlphabetical(names);

	cout << " *** Wallets by Name ***" << endl;

	for(int name = 0; name < names.size(); name++){
		for(int wallet = 0; wallet < allWallets.size(); wallet++){
			if(allWallets.at(wallet).getHolderName() == names.at(name)){
				cout << allWallets.at(wallet) << endl;
			}
		}
	}
}
