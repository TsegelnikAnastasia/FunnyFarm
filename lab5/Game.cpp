#include "Game.h"
#include "ConsoleUI.h"
#include <iostream>
#include <limits>
using namespace std;
Game::Game(Settings& settings) : settings(settings), saveManager(player,"save.txt") {
    initShop();
    initFoodPrices();
    initProducts();
}
Game::~Game(){ }
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
    for (auto& pair : foodPrices) pair.second += bonus;
}
void Game::run(bool loadFromFile) {
    if (loadFromFile) saveManager.Load();
    else {
        startNewGame();
    }
    saveManager.Start();
    while (true) {
        ConsoleUI::Clear();
        if (player.getAnimals().empty()) {
            gameOver();
            saveManager.Stop();
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
        case 5: 
            if (saveManager.CanSave()) {
                saveManager.SaveNow();
                cout << "Игра сохранена.\n";
            }
            else {
                cout << "Сохранение будет доступно позже.\n";
            }
            break;
        case 6: saveManager.Stop();
            return;
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
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("День: " + to_string(player.getDay())
        + "  |  Деньги: " + to_string(player.getMoney())
        + "  |  Действия: " + to_string(player.getActionsLeft())
        + "  |  Животных: " + to_string(player.getAnimals().size()));
    ConsoleUI::PrintSeparator();
}
void Game::showDayMenu() {
    ConsoleUI::PrintLine("1. Покормить животное");
    ConsoleUI::PrintLine("2. Купить животное");
    ConsoleUI::PrintLine("3. Купить еду");
    ConsoleUI::PrintLine("4. Лечь спать");
    ConsoleUI::PrintLine("5. Сохранить игру");
    ConsoleUI::PrintLine("6. Выйти в главное меню");
    ConsoleUI::PrintSeparator();
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
        ConsoleUI::PrintLine(to_string(i + 1) + ". " + animals[i].getSpecies()
            + " (сытость: " + to_string(animals[i].getSatiety())
            + ", счастье: " + to_string(animals[i].getHappiness()) + ")");
    }
    ConsoleUI::PrintSeparator();
}
int Game::getNutritionFor(const string& foodType) {
    if (foodType == "Трава")     return 15;
    if (foodType == "Зерно")     return 10;
    if (foodType == "Сено")      return 20;
    if (foodType == "Овощи")     return 25;
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
    cout << (animals.size() + 1) << ". Назад\n";
    int animalChoice;
    while(true){
    cout << "Выберите животное (номер): ";
    cin >> animalChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка. Попробуйте снова, введите число\n";
        continue;
    }
    if (animalChoice == animals.size() + 1) return;
    if (animalChoice >= 1 && animalChoice <= animals.size()) break;
    cout << "Неверный номер. Попробуйте снова.\n";
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
    cout << (foodTypes.size() + 1) << ". Назад\n";
    int foodChoice;
    while(true){
    cout << "Выберите еду (номер): ";
    cin >> foodChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка. Попробуйте снова, введите число.\n";
        continue;
    }
    if (foodChoice == foodTypes.size() + 1) return;
    if (foodChoice >= 1 && foodChoice <= foodTypes.size()) break;
    cout << "Неверный номер. Попробуйте снова.\n";
    }
    string foodType = foodTypes[foodChoice - 1];
    int nutrition = getNutritionFor(foodType);
    player.increaseHappinessAt(animalChoice - 1, 10);
    player.feedAnimalAt(animalChoice - 1, nutrition);
    player.removeFood(foodType, 1);
    player.useAction();
    Animal updated = player.getAnimals()[animalChoice - 1];
    cout << updated.getSpecies() << " покормлен(а). Сытость: "
        << updated.getSatiety() << ", счастье: " << updated.getHappiness() << "\n";
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("Нажмите Enter для продолжения...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("Нажмите Enter для продолжения...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
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
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("Нажмите Enter для продолжения...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
void Game::endDay() {
    ConsoleUI::PrintHeader("ЗАВЕРШЕНИЕ ДНЯ " + to_string(player.getDay()));
    map<string, int>productCount;
    int totalIncome = 0;

    for (const Animal& animal : player.getAnimals()) {
        string species = animal.getSpecies();
        if (productName.find(species) == productName.end())continue;
        string product = productName[species];
        int price = productPrice[species];
        double coefficient = 1.0;
        if (animal.getHappiness() < 30) coefficient = 0.5;
        else if (animal.getHappiness() > 70) coefficient = 1.5;
        int adpricecoaf = (int)(price * coefficient);
        if (adpricecoaf < 1) adpricecoaf = 1;
        productCount[product] += 1;
        totalIncome += adpricecoaf;
    }
    if (!productCount.empty()) {
        string line = "Продано: ";
        bool first = true;
        for (auto& pair : productCount) {
            if (!first) line += ", ";
            line += to_string(pair.second) + " " + pair.first;
            first = false;
        }
        line += ".";
        ConsoleUI::PrintLine(line);
    }
    else {
        ConsoleUI::PrintLine("Продукции нет.");
    }
    ConsoleUI::PrintLine("Доход: +" + to_string(totalIncome) + " монет.");
    player.addMoney(totalIncome);

    int deadCount = player.nextDay(SATIETY_LOSS_PER_DAY,10);;
    if (deadCount > 0) {
        ConsoleUI::PrintLine("Умерло животных: " + to_string(deadCount));
    }
    player.setActions(ACTIONS_PER_DAY);
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("Наступил день " + to_string(player.getDay()) + ".");
    ConsoleUI::PrintLine("Действия на день: " + to_string(ACTIONS_PER_DAY));
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("Нажмите Enter для продолжения...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
void Game::gameOver() {
    ConsoleUI::Clear();
    ConsoleUI::PrintHeader("ИГРА ОКОНЧЕНА");
    ConsoleUI::PrintLine("Все ваши животные погибли.");
    ConsoleUI::PrintLine("Вы продержались: " + to_string(player.getDay() - 1) + " дней.");
    ConsoleUI::PrintLine("Денег осталось: " + to_string(player.getMoney()) + ".");
    ConsoleUI::PrintSeparator();
    ConsoleUI::PrintLine("Нажмите Enter для возврата в меню...");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
void Game::initProducts() {
    productName["Курица"] = "Яйца";
    productName["Утка"] = "Яйца";
    productName["Кролик"] = "Пух";
    productName["Овца"] = "Шерсть";
    productName["Коза"] = "Молоко";
    productName["Корова"] = "Молоко";
    productName["Лошадь"] = "Навоз";

    productPrice["Курица"] = 5;
    productPrice["Утка"] = 7;
    productPrice["Кролик"] = 6;
    productPrice["Овца"] = 15;
    productPrice["Коза"] = 12;
    productPrice["Корова"] = 20;
    productPrice["Лошадь"] = 10;

}