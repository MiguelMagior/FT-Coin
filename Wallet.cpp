#include "Wallet.hpp"
#include <string>
#include <iostream>

using namespace std;

int Wallet::lastWalletId = 0;

// Default constructor
Wallet::Wallet() : id(++lastWalletId), holderName(""), broker("") {
}

Wallet::Wallet(const string& holderName, const string& broker) : id(++lastWalletId), holderName(holderName), broker(broker){
}

// Parameterized constructor
Wallet::Wallet(int id, const string& holderName, const string& broker)
    : id(id), holderName(holderName), broker(broker) {
}

// Getters
int Wallet::getId() const {
    return id;
}

string Wallet::getHolderName() const {
    return holderName;
}

string Wallet::getBroker() const {
    return broker;
}

// Setters
void Wallet::setId(int id) {
    this->id = id;
}

void Wallet::setHolderName(const string& name) {
    this->holderName = name;
}

void Wallet::setBroker(const string& broker) {
    this->broker = broker;
}

ostream& operator<<(ostream& os, const Wallet& wallet){
	os << " Wallet " << wallet.id
	<< " | Holder: " << wallet.holderName
	<< " | Broker: " << wallet.broker;
	return os;
}
