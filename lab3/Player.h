#pragma once
#include <string>
#include <vector>
#include <map>
#include "Animal.h"
using namespace std;
class Player {
public:
	Player();
	int getMoney()const;
	int getDay()const;
	int getActionsLeft()const;
	vector<Animal>getAnimals()const;
	map<string, int>getFood()const;
	void addMoney(int amount);
	bool spendMoney(int amount);
	void nextDay(int satietyLoss);
	void useAction();
	bool hasActions()const;
	void setActions(int amount);
	void addAnimal(const Animal& animal);
	void feedAnimalAt(int index, int nutrition);
	void removeDeadAnimals();
	void addFood(const string& type, int amount);
	bool hasFood(const string& type)const;
	void removeFood(const string& type, int amount);
private:
	int money;
	int day;
	int actionsLeft;
	vector<Animal> animals;
	map<string, int>food;
};