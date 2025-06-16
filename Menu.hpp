#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>
#include <vector>
using namespace std;

class Menu{
private:
	vector<string> &itens;
	string title;
	string message;
	char decorator;

public:
	Menu(vector<string> &itens, string title = "Menu");
	void decorate();
	void printMenu();
	bool isValidChoice(int choice);
	int getChoice();


	vector<string>& getItens() const;
	string getMessage() const;
	void setMessage(string message);
	string getTitle() const;
	void setTitle(string title);
	char getDecorator() const;
	void setDecorator(char decorator);
};


#endif
