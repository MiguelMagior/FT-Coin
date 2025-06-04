#include "Carteira.hpp"

Carteira::Carteira(const int carteiraID, string nomeTitular, string corretora)
	: carteiraID(carteiraID), nomeTitular(nomeTitular), corretora(corretora){
}

Carteira::~Carteira(){
}

int Carteira::getCarteiraID() const {
	return carteiraID;
}

void Carteira::setCarteiraID(int carteiraID) {
	this->carteiraID = carteiraID;
}

string Carteira::getCorretora() const {
	return corretora;
}

void Carteira::setCorretora(string corretora) {
	this->corretora = corretora;
}

string Carteira::getNomeTitular() const {
	return nomeTitular;
}

void Carteira::setNomeTitular(string nomeTitular) {
	this->nomeTitular = nomeTitular;
}
