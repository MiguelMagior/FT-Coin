#ifndef WALLET_HPP
#define WALLET_HPP

#include <string>

class Wallet {
private:
    int id;
    std::string holderName;
    std::string broker;

public:
    // Constructors
    Wallet();
    Wallet(int id, const std::string& holderName, const std::string& broker);

    // Getters
    int getId() const;
    std::string getHolderName() const;
    std::string getBroker() const;

    // Setters
    void setId(int id);
    void setHolderName(const std::string& name);
    void setBroker(const std::string& broker);
};

#endif // WALLET_HPP
