#ifndef VENDA_HPP
#define VENDA_HPP

#include "Movimentacao.hpp"
#include "Date.h"

class Venda : public Movimentacao{
public:
	Venda(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov);
	virtual ~Venda();
	double getQuantMov() const override;
};

#endif
