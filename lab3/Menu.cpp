#include "Menu.h"
#include "Game.h"
#include <iostream>
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
		cout << "Веселая Ферма" << endl;
        cout << "1. Начать игру" << endl;
        cout << "2. Загрузить игру" << endl;
        cout << "3. Настройки" << endl;
        cout << "4. О программе" << endl;
        cout << "5. Выход" << endl;
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
    cout << "Функция на данный момент недоступна, появиться в ближайших обновлениях";
    WaitForEnter();
}
void Menu::ShowAbout() {
    cout << "---О программе---" << endl;
    cout << "--Веселая Ферма--" << endl;
    cout << "Версия: " <<  VERSION << endl;
    cout << AUTHOR << endl;
    WaitForEnter();
}
void Menu::ShowSettings() {
    while (true) {
        cout << "== Настройки == " << endl;
        cout << "1. Уровень сложности (текущий: " << settings.getDifficult() << ")" << endl;
        cout << "2. Животные " << endl;
        cout << "3. Добавить животное" << endl;
        cout << "4. Назад" << endl;
        cout << "Ваш выбор:" << endl;
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
        cout << "== Уровень сложности ==" << endl;
        cout << "Текущий: " << settings.getDifficult() << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << i + 1 << ". " << options[i] << endl;
        }
        cout << (options.size() + 1) << ". Назад" << endl;
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
        cout << "== Животные ==" << endl;
        vector<string>names;
        int index = 1;
        for (auto& pair : animals) {
            cout << index << ". " << pair.first << ": " << pair.second << "\n";
            names.push_back(pair.first);
            index++;
        }
        cout << index << ". Назад" << endl;
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
        cout << endl << name << endl;
        map <string, int>animals = settings.getAnimals();
        cout << "Текущее: " << animals[name] << endl;
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
    cout << "== Добавить животное ==" << endl;
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