#include <iostream>
#include <vector>
using namespace std;
#include "Movimentacao.hpp"
#include "Venda.hpp"
#include "Date.h"


int main(){
	Date* data = new Date(4,5,2025);
	Movimentacao* mov = new Venda(1, 1, *data, 10);
	cout << mov->getQuantMov();
	return 0;
}
