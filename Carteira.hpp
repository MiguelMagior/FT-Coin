#ifndef CARTEIRA_HPP
#define CARTEIRA_HPP

#include <string>
using namespace std;

class Carteira{
private:
	int carteiraID;
	string nomeTitular;
	string corretora;
public:
	Carteira(const int carteiraID, string nomeTitular, string corretora);
	virtual ~Carteira();

	int getCarteiraID() const;
	void setCarteiraID(int carteiraID);
	string getCorretora() const;
	void setCorretora(string corretora);
	string getNomeTitular() const;
	void setNomeTitular(string nomeTitular);
};


#endif
