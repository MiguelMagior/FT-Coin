#ifndef ORACULO_HPP
#define ORACULO_HPP

#include "Date.h"

class Oraculo{
private:
	double cotacao;
	Date data;
public:
	Oraculo(double cotacao, Date data);
	~Oraculo();
}

#endif
