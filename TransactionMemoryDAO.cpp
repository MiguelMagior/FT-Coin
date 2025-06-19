#include "TransactionMemoryDAO.hpp"
#include <algorithm>
using namespace std;

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

Transaction* TransactionMemoryDAO::getTransactionById(int id){
	auto it = find_if(transactions.begin(), transactions.end(),[id](const Transaction& t) { return t.getTransactionId() == id; });

	if (it != transactions.end()) {
		return &(*it);
	}
    return nullptr;
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
