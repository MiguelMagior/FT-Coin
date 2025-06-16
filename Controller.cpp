#include "Controller.hpp"
#include "Menu.hpp"
#include <vector>
#include "WalletMemoryDAO.hpp"
#include "TransactionMemoryDAO.hpp"
#include "OracleMemoryDAO.hpp"

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
		&Controller::teste, &Controller::teste, &Controller::teste, &Controller::teste, &Controller::teste
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
