#include "Transaction.hpp"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

int Transaction::lastTransactionId = 0;

Transaction::Transaction() : walletId(0), transactionId(0), date(""), type('C'), amount(0.0) {}

Transaction::Transaction(int walletId, int transactionId, const string& date, char type, double amount)
    : walletId(walletId), transactionId(transactionId), date(date), type(type), amount(amount) {}

Transaction::Transaction(int walletId, const string& date, char type, double amount)
	: walletId(walletId), transactionId(++lastTransactionId), date(date), type(type), amount(amount){

}

int Transaction::getWalletId() const {
    return walletId;
}

int Transaction::getTransactionId() const {
    return transactionId;
}

string Transaction::getDate() const {
    return date;
}

char Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

void Transaction::setWalletId(int walletId) {
    this->walletId = walletId;
}

void Transaction::setTransactionId(int transactionId) {
    this->transactionId = transactionId;
}

void Transaction::setDate(const string& date) {
    this->date = date;
}

void Transaction::setType(char type) {
    this->type = type;
}

void Transaction::setAmount(double amount) {
    this->amount = amount;
}
ostream& operator<<(ostream& os, const Transaction& transaction){
	os << " Transaction " << transaction.transactionId
	<< " | Date: " << transaction.date
	<< " | Type: " << (transaction.type == 'V' ? "Sale" : "Purchase")
	<< " | Amount: " << fixed << setprecision(2) << transaction.amount;
	return os;
}
