#ifndef TRANSACTION_DB_DAO_HPP
#define TRANSACTION_DB_DAO_HPP

#include <vector>
#include <optional>
#include <tuple>
#include <string>
#include <memory>
#include <mariadb/conncpp.hpp>

class TransactionDBDAO {
private:
    std::unique_ptr<sql::Connection> conn;

public:
    TransactionDBDAO(const std::string& uri, const std::string& user, const std::string& password, const std::string& database);

    bool addTransaction(int walletId, int transactionId, const std::string& date, char type, double amount);
    std::optional<std::tuple<int, int, std::string, char, double>> getTransaction(int walletId, int transactionId) const;
    bool updateTransaction(int walletId, int transactionId, const std::string& date, char type, double amount);
    bool deleteTransaction(int walletId, int transactionId);
    std::vector<std::tuple<int, int, std::string, char, double>> getAllTransactions(int walletId) const;
};

#endif // TRANSACTION_DB_DAO_HPP
