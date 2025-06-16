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
		&Controller::walletMenu, &Controller::teste, &Controller::teste, &Controller::teste, &Controller::teste
	};
	launchMenu(menuItens, "FT-COIN", functions);
}

void Controller::launchMenu(vector<string> menuItens, string title, vector<void (Controller::*)()> functions){
	Menu menu(menuItens, title);
	int choice;

	while(choice = menu.getChoice()){
		(this->*functions.at(choice-1))();
		if(choice == menuItens.size()){
			break;
		}
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

