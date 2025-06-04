#ifndef COMPRA_HPP
#define COMPRA_HPP

#include "Movimentacao.hpp"
#include "Date.h"

class Compra : public Movimentacao{
public:
	Compra(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov);
	virtual ~Compra();
	double getQuantMov() const override;
};


#endif
