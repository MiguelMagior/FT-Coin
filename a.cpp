#include <iostream>
#include <vector>
using namespace std;
#include "Menu.hpp"


int main(){
	vector<string> itens {"a", "b", "c", "d"};
	Menu* menu = new Menu(itens, "MENU", "Escolha uma opcao: ");
	menu->getChoice();
	delete(menu);
	return 0;
}
