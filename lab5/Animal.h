#pragma once

#include <string>
#include <vector>

using namespace std;
class Animal {
public:
	Animal();
	Animal(const string& species, int satiety, const vector<string>& allowedfood, int price);
	string getSpecies() const;
	int getSatiety() const;
	vector<string> getAllowedFood() const;
	int getPrice() const;

	void setSatiety(int value);
	void feed(int nutrition);
	bool isAlive() const;
	bool canEat(const string& foodType) const;
	void decreaseSatiety(int amount);

	int getHappiness()const;
	void setHappiness(int value);
	void increaseHappiness(int amount);
	void decreaseHappiness(int amount);

private:
	string species;
	int satiety;
	vector<string> allowedFood;
	int price;
	int happiness;
};