#include "Animal.h"
Animal::Animal() {
	species = "";
	satiety = 100;
	allowedFood = {};
	price = 0;
}
Animal::Animal(const string& species, int satiety, const vector<string>& allowedFood, int price) {
	this->species = species;
	this -> satiety = satiety;
	this->allowedFood = allowedFood;
	this->price = price;
}
string Animal::getSpecies()const {
	return species;
}
int Animal::getSatiety()const {
	return satiety;
}
vector<string> Animal::getAllowedFood()const {
	return allowedFood;
}
int Animal::getPrice()const {
	return price;
}
void Animal::setSatiety(int value) {
	if (value < 0) value = 0;
	if (value > 100) value = 100;
	satiety = value;
}
void Animal::feed(int nutrition) {
	setSatiety(satiety + nutrition);
}
bool Animal::isAlive()const {
	return satiety > 0;
}
bool Animal::canEat(const string& foodType)const {
	for (const string& food : allowedFood) {
		if (food == foodType) return true;
	}
	return false;
}
void Animal::decreaseSatiety(int amount) {
	setSatiety(satiety - amount);
}
