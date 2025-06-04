#include "Menu.hpp"
#include <iostream>
#include <vector>
using namespace std;

Menu::Menu(vector<string> &itens, string title, string message) : title(title), itens(itens), message(message){
	this->decorator = '-';
}

void Menu::decorate(){
	int size = message.size() > title.size() ? message.size() : title.size();
	cout << string(size + 2, decorator) << endl;
}

void Menu::printMenu(){
	cout << " " << title << endl;
	decorate();
	for(int index = 0; index < itens.size(); index++){
		cout << " " << index+1 << " - " << itens.at(index) << endl;
	}
	decorate();
}

bool Menu::isValidChoice(int choice){
	if((choice >= 0) && (choice <= itens.size())){
		return true;
	}
	else{
		cout << " Opcao Invalida!" << endl;
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
