#ifndef MOVIMENTACAODAO_HPP
#define MOVIMENTACAODAO_HPP

#include <vector>
#include "Movimentacao.hpp"

using namespace std;

class MovimentacaoDAO {
public:
	MovimentacaoDAO();
	virtual ~MovimentacaoDAO();

	virtual vector<Movimentacao*> getAllMov() = 0;
	virtual Movimentacao* getMovByID(int movID) = 0;
	virtual void addMov(Movimentacao *mov) = 0;
	virtual void deleteMov(int movID) = 0;
	virtual void writeOffById(int movID) = 0;
};

#endif
