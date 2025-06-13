#ifndef ORACLE_HPP
#define ORACLE_HPP

#include <string>

class Oracle {
private:
    std::string date;
    double rate;

public:
    Oracle();
    Oracle(const std::string& date, double rate);

    // Getters
    std::string getDate() const;
    double getRate() const;

    // Setters
    void setDate(const std::string& date);
    void setRate(double rate);
};

#endif // ORACLE_HPP
