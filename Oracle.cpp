#include "Oracle.hpp"
using namespace std;

Oracle::Oracle() : date(""), rate(0.0) {}

Oracle::Oracle(const string& date, double rate) : date(date), rate(rate) {}

string Oracle::getDate() const {
    return date;
}

double Oracle::getRate() const {
    return rate;
}

void Oracle::setDate(const string& date) {
    this->date = date;
}

void Oracle::setRate(double rate) {
    this->rate = rate;
}
