#include "OracleMemoryDAO.hpp"

OracleMemoryDAO::OracleMemoryDAO() {}

bool OracleMemoryDAO::addOracle(const Oracle& oracle) {
    for (const auto& o : oracles) {
        if (o.getDate() == oracle.getDate()) {
            return false; // Entry for this date already exists
        }
    }
    oracles.push_back(oracle);
    return true;
}

std::optional<Oracle> OracleMemoryDAO::getOracleByDate(const std::string& date) const {
    for (const auto& o : oracles) {
        if (o.getDate() == date) {
            return o;
        }
    }
    return std::nullopt;
}

std::vector<Oracle> OracleMemoryDAO::getAllOracles() const {
    return oracles;
}

bool OracleMemoryDAO::updateOracle(const Oracle& oracle) {
    for (auto& o : oracles) {
        if (o.getDate() == oracle.getDate()) {
            o = oracle;
            return true;
        }
    }
    return false;
}

bool OracleMemoryDAO::deleteOracle(const std::string& date) {
    for (auto it = oracles.begin(); it != oracles.end(); ++it) {
        if (it->getDate() == date) {
            oracles.erase(it);
            return true;
        }
    }
    return false;
}
