#include "Game.h"
#include <iostream>
#include <limits>
using namespace std;
Game::Game(Settings& settings) : settings(settings) {
    initShop();
    initFoodPrices();
}
void Game::initShop() {
    shopPrices["Кролик"] = 40;
    shopPrices["Курица"] = 50;
    shopPrices["Утка"] = 60;
    shopPrices["Овца"] = 100;
    shopPrices["Коза"] = 120;
    shopPrices["Корова"] = 200;
    shopPrices["Лошадь"] = 500;
    string difficult = settings.getDifficult();
    int bonus = 0;
    if (difficult == "Средний") bonus = 5;
    else if (difficult == "Сложный") bonus = 10;
    for (auto& pair : shopPrices) pair.second += bonus;
}
void Game::initFoodPrices() {
    foodPrices["Трава"] = 3;
    foodPrices["Зерно"] = 5;
    foodPrices["Сено"] = 10;
    foodPrices["Овощи"] = 15;
    foodPrices["Комбикорм"] = 20;

    foodTypes = { "Трава", "Зерно", "Сено", "Овощи", "Комбикорм" };
    string difficult = settings.getDifficult();
    int bonus = 0;
    if (difficult == "Средний") bonus = 5;
    else if (difficult == "Сложный") bonus = 10;
    for (auto& pair : shopPrices) pair.second += bonus;
}
void Game::run() {
    startNewGame();
    while (true) {
        if (player.getAnimals().empty()) {
            gameOver();
            return;
        }
        if (!player.hasActions()) {
            cout << "\nДействия закончились.\n";
            endDay();
            continue;
        }
        showStatus();
        showDayMenu();
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число." <<endl;
            continue;
        }
        switch (choice) {
        case 1: feedAnimal(); break;
        case 2: buyAnimal();  break;
        case 3: buyFood();    break;
        case 4: endDay();     break;
        case 5: return;
        default:
            cout << "Неверный пункт меню." << endl;
            break;
        }
    }
}
Animal Game::createAnimal(const string& species) {
    int price = 100;
    if (shopPrices.count(species)) {
        price = shopPrices[species];
    }
    if (species == "Кролик") {
        return Animal(species, 100, { "Трава", "Зерно", "Овощи" }, price);
    }
    else if (species == "Курица") {
        return Animal(species, 100, { "Зерно", "Комбикорм" }, price);
    }
    else if (species == "Утка") {
        return Animal(species, 100, { "Зерно", "Комбикорм" }, price);
    }
    else if (species == "Овца") {
        return Animal(species, 100, { "Сено", "Трава" }, price);
    }
    else if (species == "Коза") {
        return Animal(species, 100, { "Сено", "Комбикорм", "Трава", "Овощи" }, price);
    }
    else if (species == "Корова") {
        return Animal(species, 100, { "Сено", "Комбикорм", "Овощи" }, price);
    }
    else if (species == "Лошадь") {
        return Animal(species, 100, { "Сено", "Зерно", "Трава" }, price);
    }
    else {
        return Animal(species, 100, { "Трава", "Зерно", "Сено", "Овощи", "Комбикорм" }, price);
    }
}
void Game::startNewGame() {
    string difficult = settings.getDifficult();
    int startMoney;
    if (difficult == "Лёгкий") {
        startMoney = 1000;
    }
    else if (difficult == "Средний") {
        startMoney = 800;
    }
    else {  
        startMoney = 600;
    }
    player = Player();
    player.addMoney(startMoney);
    player.setActions(ACTIONS_PER_DAY);
    map<string, int> animalsFromSettings = settings.getAnimals();
    for (auto& pair : animalsFromSettings) {
        string species = pair.first;
        int count = pair.second;
        for (int i = 0; i < count; i++) {
            player.addAnimal(createAnimal(species));
        }
    }
    for (const string& food : foodTypes) player.addFood(food, 1);
}
void Game::showStatus() const {
    cout << "\n=== День " << player.getDay() << " ===\n";
    cout << "Деньги: " << player.getMoney() << "\n";
    cout << "Действия: " << player.getActionsLeft() << "\n";
    cout << "Животных: " << player.getAnimals().size() << "\n";
}
void Game::showDayMenu() {
    cout << "\n1. Покормить животное\n";
    cout << "2. Купить животное\n";
    cout << "3. Купить еду\n";
    cout << "4. Лечь спать\n";
    cout << "5. Выйти в главное меню\n";
    cout << "Выбор: ";
}
void Game::showAnimals() {
    vector<Animal> animals = player.getAnimals();
    if (animals.empty()) {
        cout << "\nУ вас нет животных.\n";
        return;
    }
    cout << "\n=== Ваши животные ===\n";
    for (int i = 0; i < animals.size(); i++) {
        cout << (i + 1) << ". " << animals[i].getSpecies()
            << " (сытость: " << animals[i].getSatiety() << ")\n";
    }
}
int Game::getNutritionFor(const string& foodType) {
    if (foodType == "Зерно")     return 10;
    if (foodType == "Сено")      return 20;
    if (foodType == "Комбикорм") return 30;
    return 10;
}
void Game::feedAnimal() {
    if (!player.hasActions()) {
        cout << "\nУ вас не осталось действий на сегодня.\n";
        return;
    }
    showAnimals();
    vector<Animal> animals = player.getAnimals();
    if (animals.empty()) return;
    int animalChoice;
    while(true){
    cout << "Выберите животное (номер): ";
    cin >> animalChoice;
    if (cin.fail() || animalChoice < 1 || animalChoice > animals.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный номер. Попробуйте снова\n";
        continue;
    }
    break;
    }
    map<string, int> food = player.getFood();
    cout << "\n=== Еда на складе ===\n";
    vector<string> foodTypes;
    int index = 1;
    for (auto& pair : food) {
        if (pair.second > 0 && animals[animalChoice - 1].canEat(pair.first)) {
            cout << index << ". " << pair.first << " (" << pair.second << ")\n";
            foodTypes.push_back(pair.first);
            index++;
        }
    }
    if (foodTypes.empty()) {
        cout << "У вас нет еды. Купите еду.\n";
        return;
    }
   
    int foodChoice;

    while(true){
    cout << "Выберите еду (номер): ";
    cin >> foodChoice;
    if (cin.fail() || foodChoice < 1 || foodChoice > foodTypes.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Неверный номер. Попробуйте снова.\n";
        continue;
    }
    break;
    }
    string foodType = foodTypes[foodChoice - 1];
    Animal& animal = animals[animalChoice - 1];
    if (!animal.canEat(foodType)) {
        cout << animal.getSpecies() << " не ест " << foodType << ".\n";
        return;
    }
    int nutrition = getNutritionFor(foodType);
    animal.feed(nutrition);
    player.removeFood(foodType, 1);
    player.useAction();
    cout << animal.getSpecies() << " покормлен(а). Сытость: "
        << animal.getSatiety() << "\n";
}
void Game::buyAnimal() {
    if (!player.hasActions()) {
        cout << "\nУ вас не осталось действий на сегодня.\n";
        return;
    }
    cout << "\n=== Купить животное ===\n";
    vector<string> speciesList;
    int index = 1;
    for (auto& pair : shopPrices) {
        cout << index << ". " << pair.first
            << " (" << pair.second << " монет)\n";
        speciesList.push_back(pair.first);
        index++;
    }
    cout << index << ". Назад\n";

    int choice;
    while(true){
    cout << "Выбор: ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите число.\n";
        continue;
    }
    if (choice == speciesList.size() + 1) {
        return;
    }
    if (choice >= 1 && choice <= speciesList.size()) break;
        cout << "Неверный пункт меню.\n";
    }
    string species = speciesList[choice - 1];
    int price = shopPrices[species];

    if (player.getMoney() < price) {
        cout << "Недостаточно денег. Нужно " << price
            << ", у вас " << player.getMoney() << ".\n";
        return;
    }
    player.spendMoney(price);
    player.addAnimal(createAnimal(species));
    player.useAction();
    cout << species << " куплена за " << price << " монет.\n";
}
void Game::buyFood() {
    if (!player.hasActions()) {
        cout << "\nУ вас не осталось действий на сегодня.\n";
        return;
    }
    cout << "\n=== Купить еду ===\n";
    for (int i = 0; i < foodTypes.size(); i++) {
        cout << (i + 1) << ". " << foodTypes[i]
            << " (" << foodPrices[foodTypes[i]] << " монет)\n";
    }
    cout << (foodTypes.size() + 1) << ". Назад\n";
    int choice;
    while(true){
    cout << "Выбор: ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите число.\n";
        continue;
    }
    if (choice == foodTypes.size() + 1) return;
    if (choice >= 1 && choice <= foodTypes.size()) break;
    cout << "Неверный пункт меню.\n";
    }
    string foodType = foodTypes[choice - 1];
    int price = foodPrices[foodType];
    int amount;
    while (true) {
        cout << "Сколько порций купить? ";   
        cin >> amount;
        if (cin.fail() || amount <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Неверное количество. Попробуйте снова.\n";
            continue;
        }
        break;
    }
    int totalPrice = price * amount;
    if (player.getMoney() < totalPrice) {
        cout << "Недостаточно средств. Нужно " << totalPrice << ", у вас " << player.getMoney() << endl;
        return;
    }
    player.spendMoney(totalPrice);
    player.addFood(foodType, amount);
    player.useAction();
    cout << "Куплено " << amount << " порций " << foodType
        << " за " << totalPrice << " монет.\n";
}
void Game::endDay() {
    cout << "\n=== Завершение дня " << player.getDay() << " ===\n";
    player.nextDay(SATIETY_LOSS_PER_DAY);
    vector<Animal> animals = player.getAnimals();
    int deadCount = 0;
    for (const Animal& animal : animals) {
        if (!animal.isAlive()) {
            deadCount++;
        }
    }
    if (deadCount > 0) {
        cout << "Умерло животных: " << deadCount << "\n";
    }
    player.setActions(ACTIONS_PER_DAY);
    cout << "Наступил день " << player.getDay() << ".\n";
    cout << "Действия на день: " << ACTIONS_PER_DAY << "\n";
}
void Game::gameOver() {
    cout << "\n=== ИГРА ОКОНЧЕНА ===\n";
    cout << "Все ваши животные погибли.\n";
    cout << "Вы продержались: " << player.getDay()-1 << " дней.\n";
    cout << "Денег осталось: " << player.getMoney() << "\n";
    cout << "Нажмите Enter...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}