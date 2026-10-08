#include "Menu.h"
#include "Game.h"
#include "ConsoleUI.h"
#include <iostream>
#include <fstream>
#include <limits>
using namespace std;
const string Menu::VERSION = "1.0";
const string Menu::AUTHOR = "Анастасия Цегельник";
Menu::Menu() {
    settings.LoadFromFile("settings.txt");
}
void Menu::WaitForEnter() {
    cout << "Нажмите Enter для продолжения..." << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
void Menu::run() {
	while (true) {
        ConsoleUI::Clear();
        ConsoleUI::PrintHeader("ВЕСЁЛАЯ ФЕРМА");
        ConsoleUI::PrintLine("1. Начать игру");
        ConsoleUI::PrintLine("2. Загрузить игру");
        ConsoleUI::PrintLine("3. Настройки");
        ConsoleUI::PrintLine("4. О программе");
        ConsoleUI::PrintLine("5. Выход");
        ConsoleUI::PrintSeparator();
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число." << endl;
            continue;
        }
        switch (choice) {
        case MENU_START_GAME: StartGame(); break;
        case MENU_LOAD_GAME: LoadGame(); break;
        case MENU_SETTINGS: ShowSettings(); break;
        case  MENU_ABOUT: ShowAbout(); break;
        case MENU_EXIT:
            cout << "Выход из программы." << endl;
            return;
        default:
            cout << "Неверный пункт меню.\n";
            break;
        }
	}
}
void Menu::StartGame() {
    cout << "Игра началась!" << endl;
    Game game(settings);
    game.run();
}
void Menu::LoadGame() {
    ifstream test("save.txt");
    if (!test.is_open()) {
        cout << "\nСохранение не найдено.\n";
        WaitForEnter();
        return;
    }
    test.close();

    Game game(settings);
    game.run(true);
}
void Menu::ShowAbout() {
    ConsoleUI::Clear();
    ConsoleUI::PrintHeader("О ПРОГРАММЕ");
    ConsoleUI::PrintLine("Весёлая Ферма");
    ConsoleUI::PrintLine("Версия: " + VERSION);
    ConsoleUI::PrintLine("Автор: " + AUTHOR);
    ConsoleUI::PrintSeparator();
    WaitForEnter();
}
void Menu::ShowSettings() {
    while (true) {
        ConsoleUI::Clear();
        ConsoleUI::PrintHeader("НАСТРОЙКИ");
        ConsoleUI::PrintLine("1. Уровень сложности (" + settings.getDifficult() + ")");
        ConsoleUI::PrintLine("2. Животные");
        ConsoleUI::PrintLine("3. Добавить животное");
        ConsoleUI::PrintLine("4. Назад");
        ConsoleUI::PrintSeparator();
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число.\n";
            continue;
        }
        switch (choice) {
        case 1: ChangeDifficult(); break;
        case 2: ShowAnimals(); break;
        case 3: AddAnimal(); break;
        case 4: return;
        default: cout << "Неверный пункт меню" << endl;
            break;
        }
    }
}
void Menu::ChangeDifficult() {
    const vector<string>& options = settings.getAvailableDifficulties();
    while (true) {
        ConsoleUI::Clear();
        ConsoleUI::PrintHeader("УРОВЕНЬ СЛОЖНОСТИ");
        ConsoleUI::PrintLine("Текущий: " + settings.getDifficult());
        ConsoleUI::PrintSeparator();
        for (int i = 0; i < options.size(); i++) {
            ConsoleUI::PrintLine(to_string(i + 1) + ". " + options[i]);
        }
        ConsoleUI::PrintLine(to_string(options.size() + 1) + ". Назад");
        ConsoleUI::PrintSeparator();
        cout << "Выбор : ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число." << endl;
            continue;
        }
        if (choice >= 1 && choice <= options.size()) {
            settings.setDifficult(options[choice - 1]);
            settings.SaveToFile("settings.txt");
        }
        else if (choice == options.size() + 1) return;
        else cout << "Неверный выбор" << endl;
    }
}

void Menu::ShowAnimals() {
    
    while (true) {
    map<string, int>animals = settings.getAnimals();
    if (animals.empty()) {
        cout << "Список животных пуст." << endl;
        WaitForEnter();
        return;
    }
        ConsoleUI::Clear();
        ConsoleUI::PrintHeader("ЖИВОТНЫЕ");
        vector<string>names;
        int index = 1;
        for (auto& pair : animals) {
            ConsoleUI::PrintLine(to_string(index) + ". " + pair.first + ": " + to_string(pair.second)); 
            names.push_back(pair.first);
            index++;
        }
        ConsoleUI::PrintLine(to_string(index) + ". Назад");
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число."<<endl;
            continue;
        }
        if (choice >= 1 && choice <= names.size()) {
            ChangeAnimal(names[choice - 1]);
        }
        else if (choice == names.size() + 1) {
            return;
        }
        else cout << "Неверный пункт меню" << endl;
    }
}
void Menu::ChangeAnimal(const string& name) {
    const vector<int>options = { 1,2,3,5,10 };
    while (true) {
        ConsoleUI::Clear();
        ConsoleUI::PrintHeader(name);
        map <string, int>animals = settings.getAnimals();
        ConsoleUI::PrintLine("Текущее: " + to_string(animals[name]));
        for (int i = 0; i < options.size(); i++) {
            cout << (i + 1) << ". " << options[i] << endl;
        }
        cout << (options.size() + 1) << ". Назад" << endl;
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число." << endl;
            continue;
        }
        if (choice >= 1 && choice <= options.size()) {
            settings.setAnimalCount(name, options[choice - 1]);
            settings.SaveToFile("settings.txt");
        }
        else if (choice == options.size() + 1) {
            return;
        }
        else cout << "Неверный пункт меню" << endl;
    }
}
void Menu::AddAnimal() {
    string name;
    int count;
    ConsoleUI::Clear();
    ConsoleUI::PrintHeader("ДОБАВИТЬ ЖИВОТНОЕ");
    cout << "Введите название животного: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);
    if (settings.HasAnimal(name)) {
        cout << "Животное \"" << name << "\" уже существует." << endl;
        WaitForEnter();
        return;
    }
    cout << "Введите количество: ";
    cin >> count;
    if (cin.fail() || count < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Ошибка ввода. Введите положительное число." <<endl;
        WaitForEnter();
        return;
    }
    settings.AddAnimal(name, count);
    settings.SaveToFile("settings.txt");
    cout << "Животное \"" << name << "\" добавлено с количеством " << count << endl;
    WaitForEnter();
}