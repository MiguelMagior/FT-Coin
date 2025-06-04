#include "Venda.hpp"

Venda::Venda(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov)
	: movimentacaoID(movimentacaoID), carteiraID(carteiraID), data(data), quantMov(quantMov){
	Venda::tipoOp = 'V';
}
virtual Venda::~Venda(){
}
double Venda::getQuantMov(){
	return Venda::quantMov * (-1);
}
