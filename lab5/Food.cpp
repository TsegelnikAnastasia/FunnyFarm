#include "Food.h"
Food::Food() {
    type = "";
    nutrition = 0;
    price = 0;
}
Food::Food(const string& type, int nutrition, int price) {
    this->type = type;
    this->nutrition = nutrition;
    this->price = price;
}
string Food::getType() const {
    return type;
}

int Food::getNutrition() const {
    return nutrition;
}

int Food::getPrice() const {
    return price;
}
