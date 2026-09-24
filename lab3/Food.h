#pragma once
#include <string>
using namespace std;
class Food {
public:
	Food();
	Food(const string& type, int nutrition, int price);
	string getType()const;
	int getNutrition()const;
	int getPrice()const;
private:
	string type;
	int nutrition;
	int price;
};