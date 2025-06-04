#include "Compra.hpp"
#include "TipoMov.hpp"

Compra::Compra(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov)
	: Movimentacao(movimentacaoID, carteiraID, data, TipoMov::COMPRA, quantMov ){
}

Compra::~Compra(){
}

double Compra::getQuantMov() const{
	return Compra::quantMov;
}
