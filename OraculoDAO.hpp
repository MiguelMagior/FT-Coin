#ifndef ORACULODAO_HPP
#define ORACULODAO_HPP

#include <vector>
#include "Oraculo.hpp"

using namespace std;

class OraculoDAO {
public:
	OraculoDAO();
	virtual ~OraculoDAO();

	virtual vector<Oraculo*> getAllOrac() = 0;
	virtual Oraculo* getOracByDate(int data) = 0;
	virtual void addMov(Oraculo *orac) = 0;
	virtual void deleteOrac(Date data) = 0;
	virtual void writeOffByDate(Date data) = 0;
};

#endif
