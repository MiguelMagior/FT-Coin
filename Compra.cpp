#include "Compra.hpp"

Compra::Compra(const int movimentacaoID, const int carteiraID, const Date &data, double quantMov)
	: movimentacaoID(movimentacaoID), carteiraID(carteiraID), data(data), quantMov(quantMov){
	Compra::tipoOp = 'C';
}
virtual Compra::~Compra(){
}
double Compra::getQuantMov(){
	return Compra::quantMov;
}
