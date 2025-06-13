#include "TransactionMemoryDAO.hpp"

TransactionMemoryDAO::TransactionMemoryDAO() {}

bool TransactionMemoryDAO::addTransaction(const Transaction& transaction) {
    for (const auto& t : transactions) {
        if (t.getTransactionId() == transaction.getTransactionId()) {
            return false; // ID já existe
        }
    }
    transactions.push_back(transaction);
    return true;
}

optional<Transaction> TransactionMemoryDAO::getTransactionById(int id) const {
    for (const auto& t : transactions) {
        if (t.getTransactionId() == id) {
            return t;
        }
    }
    return nullopt;
}

vector<Transaction> TransactionMemoryDAO::getTransactionsByWalletId(int walletId) const {
    vector<Transaction> result;
    for (const auto& t : transactions) {
        if (t.getWalletId() == walletId) {
            result.push_back(t);
        }
    }
    return result;
}

vector<Transaction> TransactionMemoryDAO::getAllTransactions() const {
    return transactions;
}

bool TransactionMemoryDAO::deleteTransaction(int id) {
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getTransactionId() == id) {
            transactions.erase(it);
            return true;
        }
    }
    return false;
}
