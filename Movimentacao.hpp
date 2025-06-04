#ifndef MOVIMENTACAO_HPP
#define MOVIMENTACAO_HPP

#include "Date.h"
#include "TipoMov.hpp"

class Movimentacao{
protected:
	int movimentacaoID;
	int carteiraID;
	Date data;
	double quantMov;
	TipoMov tipoMov; //será que ele quer um enum aqui?
public:
	Movimentacao(const int movimentacaoID, const int carteiraID, const Date &data, TipoMov tipoMov, double quantMov);
	virtual ~Movimentacao();

	int getCarteiraId() const;
	void setCarteiraId(int carteiraId);
	Date getData() const;
	void setData(Date data);
	int getMovimentacaoId() const;
	void setMovimentacaoId(int movimentacaoId);
	TipoMov getTipoMov() const;
	void setTipoMov(TipoMov tipoMov);

	void setQuantMov(double quantMov);
	virtual double getQuantMov() const;
};


#endif
