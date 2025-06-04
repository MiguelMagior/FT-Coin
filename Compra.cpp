#include "Compra.hpp"

Compra::Compra(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov)
	: Movimentacao(movimentacaoID, carteiraID, data, 'C', quantMov ){
}

Compra::~Compra(){
}

double Compra::getQuantMov() const{
	return Compra::quantMov;
}
