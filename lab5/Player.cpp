#include "Player.h"
Player::Player() {
    money = 0;
    day = 1;
    actionsLeft = 0;
    animals = {};
    food = {};
}
int Player::getMoney() const {
    return money;
}
int Player::getDay() const {
    return day;
}
int Player::getActionsLeft() const {
    return actionsLeft;
}
vector<Animal> Player::getAnimals() const {
    return animals;
}
map<string, int> Player::getFood() const {
    return food;
}
void Player::addMoney(int amount) {
    money += amount;
}
bool Player::spendMoney(int amount) {
    if (money < amount) {
        return false;
    }
    money -= amount;
    return true;
}

void Player::setActions(int amount) {
    actionsLeft = amount;
}
void Player::setDay(int value) { day = value; }
void Player::setMoney(int value) {money = value; }
void Player::clearAnimals() { animals.clear(); }
void Player::clearFood() { food.clear(); }

void Player::useAction() {
    if (actionsLeft > 0) {
        actionsLeft--;
    }
}
bool Player::hasActions() const {
    return actionsLeft > 0;
}
int Player::nextDay(int satietyLoss,int happinessLoss) {
    day++;
    for (Animal& animal : animals) {
        animal.decreaseSatiety(satietyLoss);
        animal.decreaseHappiness(happinessLoss);
    }
    int before = animals.size();
    removeDeadAnimals();
    int after = animals.size();
    return before - after;
}
void Player::addAnimal(const Animal& animal) {
    animals.push_back(animal);
}
void Player::removeDeadAnimals() {
    vector<Animal> alive;
    for (const Animal& animal : animals) {
        if (animal.isAlive()) {
            alive.push_back(animal);
        }
    }
    animals = alive;
}
void Player::feedAnimalAt(int index, int nutrition) {
    if (index >= 0 && index < animals.size()) {
        animals[index].feed(nutrition);
    }
}
void Player::increaseHappinessAt(int index, int amount) {
    if (index >= 0 && index < animals.size()) {
        animals[index].increaseHappiness(amount);
    }
}
void Player::addFood(const string& type, int amount) {
    food[type] += amount;
}
bool Player::hasFood(const string& type) const {
    auto it = food.find(type);
    if (it == food.end()) {
        return false;
    }
    return it->second > 0;
}
void Player::removeFood(const string& type, int amount) {
    if (!hasFood(type)) {
        return;
    }
    food[type] -= amount;
    if (food[type] < 0) {
        food[type] = 0;
    }
}
