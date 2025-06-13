#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>

class Transaction {
private:
    int walletId;
    int transactionId;
    std::string date;
    char type; // 'C' for buy, 'V' for sell
    double amount;

public:
    Transaction();
    Transaction(int walletId, int transactionId, const std::string& date, char type, double amount);

    // Getters
    int getWalletId() const;
    int getTransactionId() const;
    std::string getDate() const;
    char getType() const;
    double getAmount() const;

    // Setters
    void setWalletId(int walletId);
    void setTransactionId(int transactionId);
    void setDate(const std::string& date);
    void setType(char type);
    void setAmount(double amount);
};

#endif // TRANSACTION_HPP
