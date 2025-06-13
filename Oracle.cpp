#include "Oracle.hpp"

Oracle::Oracle() : date(""), rate(0.0) {}

Oracle::Oracle(const std::string& date, double rate) : date(date), rate(rate) {}

std::string Oracle::getDate() const {
    return date;
}

double Oracle::getRate() const {
    return rate;
}

void Oracle::setDate(const std::string& date) {
    this->date = date;
}

void Oracle::setRate(double rate) {
    this->rate = rate;
}
