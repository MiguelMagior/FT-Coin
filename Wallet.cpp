#include "Wallet.hpp"
#include <string>

using namespace std;

// Default constructor
Wallet::Wallet() : id(0), holderName(""), broker("") {}

// Parameterized constructor
Wallet::Wallet(int id, const string& holderName, const string& broker)
    : id(id), holderName(holderName), broker(broker) {}

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
