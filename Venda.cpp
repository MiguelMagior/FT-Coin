#include "Venda.hpp"

Venda::Venda(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov)
	: Movimentacao(movimentacaoID, carteiraID, data, 'V', quantMov ){
}
Venda::~Venda(){
}

double Venda::getQuantMov() const{
	return (-1) * Venda::quantMov;
}
