#ifndef MOVIMENTACAO_HPP
#define MOVIMENTACAO_HPP

#include "Date.h"

class Movimentacao{
protected:
	int movimentacaoID;
	int carteiraID;
	Date data;
	double quantMov;
	char tipoOp;
public:
	Movimentacao(const int movimentacaoID, const int carteiraID, const Date &data, char tipoOp, double quantMov);
	virtual ~Movimentacao();

	int getCarteiraId() const;
	void setCarteiraId(int carteiraId);
	Date getData() const;
	void setData(Date data);
	int getMovimentacaoId() const;
	void setMovimentacaoId(int movimentacaoId);
	char getTipoOp() const;
	void setTipoOp(char tipoOp);

	void setQuantMov(double quantMov);
	virtual double getQuantMov() const;
};


#endif
