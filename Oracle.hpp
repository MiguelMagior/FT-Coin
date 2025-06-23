#ifndef ORACLE_HPP
#define ORACLE_HPP

#include <string>
using namespace std;

class Oracle {
private:
    string date;
    double rate;

public:
    Oracle();
    Oracle(const string& date, double rate);

    // Getters
    string getDate() const;
    double getRate() const;

    // Setters
    void setDate(const string& date);
    void setRate(double rate);
};

#endif // ORACLE_HPP
