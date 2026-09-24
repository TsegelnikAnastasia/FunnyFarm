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
void Player::useAction() {
    if (actionsLeft > 0) {
        actionsLeft--;
    }
}
bool Player::hasActions() const {
    return actionsLeft > 0;
}
void Player::nextDay(int satietyLoss) {
    day++;
    for (Animal& animal : animals) {
        animal.decreaseSatiety(satietyLoss);
    }
    removeDeadAnimals();
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
