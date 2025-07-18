#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
using namespace std;

class Transaction {
private:
	static int lastTransactionId;
    int walletId;
    int transactionId;
    string date;
    char type; // 'C' for buy, 'V' for sell
    double amount;

public:
    Transaction();
    Transaction(int walletId, int transactionId, const string& date, char type, double amount);
    Transaction(int walletId, const string& date, char type, double amount);

    // Getters
    int getWalletId() const;
    int getTransactionId() const;
    string getDate() const;
    char getType() const;
    double getAmount() const;

    // Setters
    void setWalletId(int walletId);
    void setTransactionId(int transactionId);
    void setDate(const string& date);
    void setType(char type);
    void setAmount(double amount);

    friend ostream& operator<<(ostream& os, const Transaction& transaction);
};

#endif // TRANSACTION_HPP
