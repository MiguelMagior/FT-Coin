#ifndef TRANSACTION_MEMORY_DAO_HPP
#define TRANSACTION_MEMORY_DAO_HPP

#include <vector>
#include <optional>
#include "Transaction.hpp"

using namespace std;

class TransactionMemoryDAO {
private:
    vector<Transaction> transactions;

public:
    TransactionMemoryDAO();

    bool addTransaction(const Transaction& transaction);
    optional<Transaction> getTransactionById(int id) const;
    vector<Transaction> getTransactionsByWalletId(int walletId) const;
    vector<Transaction> getAllTransactions() const;
    bool deleteTransaction(int id);
};

#endif // TRANSACTION_MEMORY_DAO_HPP
