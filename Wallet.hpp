#ifndef WALLET_HPP
#define WALLET_HPP

#include <string>
using namespace std;

class Wallet {
private:
	static int lastWalletId;
    int id;
    std::string holderName;
    std::string broker;

public:
    // Constructors
    Wallet();
    Wallet(int id, const string& holderName, const string& broker);

    // Getters
    int getId() const;
    string getHolderName() const;
    string getBroker() const;

    // Setters
    void setId(int id);
    void setHolderName(const string& name);
    void setBroker(const string& broker);

    friend ostream& operator<<(ostream& os, const Wallet& wallet);
};

#endif // WALLET_HPP
