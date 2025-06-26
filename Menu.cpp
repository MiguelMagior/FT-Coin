#include "Menu.hpp"
#include <iostream>
#include <vector>
using namespace std;

Menu::Menu(vector<string> &itens, string title) : itens(itens), title(title){
	this->decorator = '-';
	this->message = "Choose a option: ";
}

void Menu::decorate(){
	int size = message.size() > title.size() ? message.size() : title.size();
	cout << string(size + 2, decorator) << endl;
}

void Menu::printMenu(){
	int index = 0;
	decorate();
	cout << " " << title << endl;
	decorate();
	for(const auto& item : itens){
		cout << " " << index+1 << " - " << item << endl;
		index++;
	}
	decorate();
}

bool Menu::isValidChoice(int choice){
	if((choice > 0) && (choice <= int(itens.size()))){
		return true;
	}
	else{
		cout << " Invalid option!" << endl;
		return false;
	}
}

int Menu::getChoice(){
	int choice;
	do{
		printMenu();
		cout << " " << message;
		cin >> choice;
		} while(!isValidChoice(choice));
	if((choice == int(itens.size()+1)))
		return -1;
	return choice;
}

vector<string>& Menu::getItens() const {
	return itens;
}

string Menu::getMessage() const {
	return message;
}

void Menu::setMessage(string message) {
	this->message = message;
}

string Menu::getTitle() const {
	return title;
}

void Menu::setTitle(string title) {
	this->title = title;
}
char Menu::getDecorator() const {
	return decorator;
}

void Menu::setDecorator(char decorator) {
	this->decorator = decorator;
}
