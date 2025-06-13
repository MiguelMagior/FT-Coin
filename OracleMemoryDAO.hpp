#ifndef ORACLE_MEMORY_DAO_HPP
#define ORACLE_MEMORY_DAO_HPP

#include <vector>
#include <optional>
#include <string>
#include "Oracle.hpp"

class OracleMemoryDAO {
private:
    std::vector<Oracle> oracles;

public:
    OracleMemoryDAO();

    bool addOracle(const Oracle& oracle);
    std::optional<Oracle> getOracleByDate(const std::string& date) const;
    std::vector<Oracle> getAllOracles() const;
    bool updateOracle(const Oracle& oracle);
    bool deleteOracle(const std::string& date);
};

#endif // ORACLE_MEMORY_DAO_HPP
