#pragma once
#include <string>
#include <vector>
#include <map>
#include "Player.h"
#include "Animal.h"
#include "Food.h"
#include "Settings.h"
using namespace std;
class Game {
public:
    Game(Settings& settings);
    void run();
private:
    static const int ACTIONS_PER_DAY = 10;
    static const int SATIETY_LOSS_PER_DAY = 25;

    Settings& settings;
    Player player;
    void startNewGame();
    void showDayMenu();
    void showAnimals();
    void feedAnimal();
    void buyAnimal();
    void buyFood();
    void endDay();
    void showStatus() const;
    int getNutritionFor(const string& foodType);
    void gameOver();
    Animal createAnimal(const string& species);
    map<string, int> shopPrices;
    map<string, int> foodPrices;
    vector<string> foodTypes;

    void initShop();
    void initFoodPrices();
};