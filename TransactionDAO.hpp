#ifndef TRANSACTIONDAO_HPP
#define TRANSACTIONDAO_HPP

#include "Transaction.hpp"
#include <vector>
using namespace std;

class TransactionDAO{
public:
	TransactionDAO();
	virtual ~TransactionDAO();

	virtual bool addTransaction(const Transaction& transaction) = 0;
	virtual Transaction* getTransactionById(int id) = 0;
	virtual vector<Transaction> getTransactionsByWalletId(int walletId) = 0;
	virtual vector<Transaction> getAllTransactions() = 0;
	virtual bool deleteTransaction(int id) = 0;
};
#endif
