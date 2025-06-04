#ifndef MOVIMENTACAO_HPP
#define MOVIMENTACAO_HPP

#include "Date.h"

class Movimentacao{
protected:
	int movimentacaoID;
	int carteiraID;
	Date data;
	double quantMov;
	char tipoMov;
public:
	Movimentacao(const int movimentacaoID, const int carteiraID, const Date &data, char tipoMov, double quantMov);
	virtual ~Movimentacao();

	int getCarteiraId() const;
	void setCarteiraId(int carteiraId);
	Date getData() const;
	void setData(Date data);
	int getMovimentacaoId() const;
	void setMovimentacaoId(int movimentacaoId);
	char getTipoMov() const;
	void setTipoMov(char tipoMov);

	void setQuantMov(double quantMov);
	virtual double getQuantMov() const;
};


#endif
