#ifndef TRANSACTION_MEMORY_DAO_HPP
#define TRANSACTION_MEMORY_DAO_HPP

#include <vector>
#include "Transaction.hpp"
#include "TransactionDAO.hpp"

using namespace std;

class TransactionMemoryDAO : public TransactionDAO {
private:
    vector<Transaction> transactions;

public:
    TransactionMemoryDAO();

    bool addTransaction(const Transaction& transaction);
    Transaction* getTransactionById(int id);
    vector<Transaction> getTransactionsByWalletId(int walletId);
    vector<Transaction> getAllTransactions();
    bool deleteTransaction(int id);
};

#endif // TRANSACTION_MEMORY_DAO_HPP
