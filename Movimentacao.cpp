#include "Movimentacao.hpp"
#include "TipoMov.hpp"
#include "Date.h"

Movimentacao::Movimentacao(const int movimentacaoID, const int carteiraID, const Date &data, TipoMov tipoMov, double quantMov)
	: movimentacaoID(movimentacaoID), carteiraID(carteiraID), data(data), tipoMov(tipoMov), quantMov(quantMov){
}
Movimentacao::~Movimentacao(){
}

int Movimentacao::getCarteiraId() const {
	return carteiraID;
}

void Movimentacao::setCarteiraId(int carteiraId) {
	carteiraID = carteiraId;
}

Date Movimentacao::getData() const {
	return data;
}

void Movimentacao::setData(Date data) {
	this->data = data;
}

int Movimentacao::getMovimentacaoId() const {
	return movimentacaoID;
}

void Movimentacao::setMovimentacaoId(int movimentacaoId) {
	movimentacaoID = movimentacaoId;
}

double Movimentacao::getQuantMov() const {
	return quantMov;
}

void Movimentacao::setQuantMov(double quantMov) {
	this->quantMov = quantMov;
}

TipoMov Movimentacao::getTipoMov() const {
	return tipoMov;
}

void Movimentacao::setTipoMov(TipoMov tipoMov) {
	this->tipoMov = tipoMov;
}
