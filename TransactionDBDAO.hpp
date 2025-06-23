#ifndef TRANSACTION_DB_DAO_HPP
#define TRANSACTION_DB_DAO_HPP

#include "TransactionDAO.hpp"

#include <vector>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>
using namespace std;

class TransactionDBDAO : public TransactionDAO{
private:
    unique_ptr<sql::Connection> conn;

public:
    TransactionDBDAO(const string& uri, const string& user, const string& password, const string& database);

    bool addTransaction(const Transaction& transaction);
    Transaction* getTransactionById(int id);
    vector<Transaction> getTransactionsByWalletId(int walletId);
    vector<Transaction> getAllTransactions();
    bool deleteTransaction(int id);
    bool updateTransaction(int walletId, int transactionId, const string& date, char type, double amount);
};

#endif // TRANSACTION_DB_DAO_HPP
