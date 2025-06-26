#include "Controller.hpp"
#include "Menu.hpp"
#include "Utils.hpp"
#include "DataBaseType.hpp"

#include "WalletMemoryDAO.hpp"
#include "WalletDBDAO.hpp"

#include "TransactionMemoryDAO.hpp"
#include "TransactionDBDAO.hpp"

#include "OracleMemoryDAO.hpp"
#include "OracleDBDAO.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <iomanip>
using namespace std;

Controller::Controller(DataBaseType dbType){
	try {
		switch(dbType) {
			case MEMORY:
                wallets = new WalletMemoryDAO();
                transactions = new TransactionMemoryDAO();
                oracle = new OracleMemoryDAO();
                break;

            case DB: {

                const string host = "143.106.234.64";
                const string user = "Pool_25_A03";
                const string password = "SwNWcvIM94";
                const string database = "Pool_25_A03";

                wallets = new WalletDBDAO(host, user, password, database);
                transactions = new TransactionDBDAO(host, user, password, database);
                oracle = new OracleDBDAO(host, user, password, database);
                break;

            }

            default:
                throw invalid_argument(" Invalid database type");
        }
    } catch (const exception& e) {
        delete wallets;
        delete transactions;
        delete oracle;
        throw;
    }
}

Controller::~Controller(){
	delete oracle;
	delete transactions;
	delete wallets;
	cout << " Program closed " << endl;
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

	while((choice = menu.getChoice())){
		if((choice == int(menuItens.size()))){
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
		&Controller::registerPurchase, &Controller::registerSale
	};
	launchMenu(menuItens, "Transaction", functions);
}

void Controller::reportMenu(){
	vector<string> menuItens{
		"Wallets by ID", "Wallets by Name", "Wallet Current Balance", "Transaction History", "All Wallets Balance","Return"
	};
	vector<void (Controller::*)()> functions{
		&Controller::reportWalletById, &Controller::reportWalletByName, &Controller::reportWalletBalance, &Controller::reportTransactionHistory, &Controller::reportAllWalletsBalance
	};
	launchMenu(menuItens, "Transaction", functions);
}

void Controller::menuHelp(){
	vector<string> menuItens{
		"Features Help", "Credits", "Test Population", "Return"
	};
	vector<void (Controller::*)()> functions{
		&Controller::printHelp, &Controller::printCredits, &Controller::populate
	};
	launchMenu(menuItens, "Help", functions);
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

	if(wallets->addWallet(newWallet)){
		cout << " Wallet added successfully" << endl;
	}
	else{
		cout << " Error adding Wallet" << endl;
	}
}


int Controller::getId(){
	int id;
	cin.ignore();
	cout << " ID: ";
	id = validInt();
	return id;
}

bool Controller::findWalletById(int id){
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
	findWalletById(getId());
}

void Controller::editWallet(){
	string holderName, broker;
	Wallet* wallet = new Wallet();
	int id;
	cout << " *** EDIT WALLET ***" << endl;
	id = getId();

	if(findWalletById(id)){
		wallet->setId(id);
		cin.ignore();
		cout << " Holder Name: ";
		getline(cin, holderName);
		wallet->setHolderName(holderName);
		cout << " Broker: ";
		getline(cin, broker);
		wallet->setBroker(broker);
		wallets->updateWallet(*wallet);
	}
}

void Controller::deleteWallet(){
	int id;

	cout << " *** DELETE WALLET ***" << endl;
	id = getId();

	if(findWalletById(id)){
		vector<Transaction> walletTransactions = transactions->getTransactionsByWalletId(id);
		for (const auto& transaction : walletTransactions) {
			transactions->deleteTransaction(transaction.getTransactionId());
		}
		wallets->deleteWallet(id);
		cout << " Wallet deleted successfully" << endl;
	}
	else{
		cout << " Error deleting wallet" << endl;
	}
}

// *** TRANSACTIONS *** //
void Controller::registerTransaction(char type){
	int walletId;
	string date;
	Transaction* transaction;
	double amount;

	cout << " Choose Wallet: " << endl;
	walletId = getId();

	if(findWalletById(walletId)){
		cin.ignore();
		cout << " Date(YEAR/MONTH/DAY): ";
		cin >> date;
		cout << " Amount($0.0): ";
		cin >> amount;
		if(type == 'V' && (getWalletBalance(walletId) < amount)){
			cout << " Invalid transaction. Amount higher than wallet balance." << endl;
			return;
		}
		transaction = new Transaction(walletId, date, type, amount);
		transactions->addTransaction(*transaction);

	}
}

void Controller::registerPurchase(){
	cout << " *** Purchase ***" << endl;
	registerTransaction('C');
}

void Controller::registerSale(){
	cout << " *** Sale ***" << endl;
	registerTransaction('V');
}

double Controller::getWalletBalance(int walletId){
	double balance = 0;
	vector<Transaction> walletTransactions = transactions->getTransactionsByWalletId(walletId);

	for (const auto& transaction : walletTransactions) {
	    balance += (transaction.getType() == 'V' ? transaction.getAmount() : -transaction.getAmount());
	}

	return balance;
}

void Controller::printWalletTransactions(int walletId){
	vector<Transaction> walletTransactions = transactions->getTransactionsByWalletId(walletId);
	for (const auto& transaction : walletTransactions) {
	    cout << transaction << endl;
	}
}

double Controller::getWalletValue(int walletId){
	double value = 0;
	vector<Transaction> walletTransactions = transactions->getTransactionsByWalletId(walletId);

	for ( auto& transaction : walletTransactions) {
		value += getTransactionValue(&transaction);
	}
	return value;
}
// *** ORACLE *** //
double Controller::getTransactionValue(Transaction* transaction){
	Oracle* dateOracle = oracle->getOracleByDate(transaction->getDate());
	double amount = transaction->getAmount();
	double rate = dateOracle->getRate();

	if(transaction->getType() == 'V'){
		return amount * rate;
	}
	else{
		return amount * rate * -1;
	}
}

// **** REPORTS ****  //
void Controller::reportWalletById(){
	vector<Wallet> allWallets = wallets->getAllWallets();

	cout << " *** Wallets by ID ***" << endl;
	for(const auto& wallet : allWallets){
		cout << wallet << endl;
	}
}

void Controller::reportWalletByName(){
	vector<string> names;
	vector<Wallet> allWallets = wallets->getAllWallets();

	for(const auto& wallet : allWallets){
		if((!isDuplicated(names, wallet.getHolderName()))){
			names.push_back(wallet.getHolderName());
		}
	}
	names = sortAlphabetical(names);

	cout << " *** Wallets by Name ***" << endl;

	for(const auto& name : names){
		for(const auto& wallet : allWallets){
			if(wallet.getHolderName() == name){
				cout << wallet << endl;
			}
		}
	}
}

void Controller::reportWalletBalance(){
	int id;
	double value;
	cout << " *** Wallet Balance ***" << endl;
	id = getId();
	if(findWalletById(id)){
		cout << fixed << setprecision(5);
		cout << " " << getWalletBalance(id) << " coins - $";
		value = getWalletValue(id);
		if (value < 0) {
			cout << "\033[31m" << value << "\033[0m" << endl; // Vermelho se negativo
		} else {
			cout << "\033[32m" << value << "\033[0m" << endl; // Verde se positivo/zero
		}
	}
}

void Controller::reportTransactionHistory(){
	int id;

	cout << " *** Transaction History ***" << endl;
	id = getId();
	if(findWalletById(id)){
		printWalletTransactions(id);
	}
}

void Controller::reportAllWalletsBalance(){
	vector<Wallet> allWallets = wallets->getAllWallets();
	double value;
	for(const auto& wallet : allWallets){
		findWalletById(wallet.getId());
		value = getWalletValue(wallet.getId());
		if (value < 0) {
			cout << "\t $" << "\033[31m" << value << "\033[0m" << endl; // Vermelho se negativo
		} else {
			cout << "\t $" << "\033[32m" << value << "\033[0m" << endl; // Verde se positivo/zero
		}
	}
}
// *** HELP ***

void Controller::printCredits(){
	printFile("credits.txt");
}

void Controller::printHelp(){
	printFile("help.txt");
}

void Controller::populate(){
	int lastWalletId = getLastWalletId();

	wallets->addWallet(Wallet(lastWalletId + 1, "Lucas", "Broker1"));
	wallets->addWallet(Wallet(lastWalletId + 2,"Adriane", "Broker2"));
	wallets->addWallet(Wallet(lastWalletId + 3,"Henrique", "Broker3"));

	transactions->addTransaction(Transaction(lastWalletId + 1, "2025/02/26", 'C', 1.0));
	transactions->addTransaction(Transaction(lastWalletId + 1, "2025/12/27", 'V', 0.5));
	transactions->addTransaction(Transaction(lastWalletId + 2, "2025/01/26", 'C', 2.0));
	transactions->addTransaction(Transaction(lastWalletId + 2, "2025/10/27", 'V', 1.0));
	transactions->addTransaction(Transaction(lastWalletId + 3, "2025/03/26", 'C', 3.0));
	transactions->addTransaction(Transaction(lastWalletId + 3, "2025/05/27", 'V', 3.0));

	cout << " Memory populated" << endl;
}

int Controller::getLastWalletId(){
	vector<Wallet> walletVector = wallets->getAllWallets();
	if(walletVector.empty()){
		return 0;
	}
	return walletVector.back().getId();
}
