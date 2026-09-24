#include "Menu.h"
#include <iostream>
#include <limits>
using namespace std;
const string Menu::VERSION = "1.0";
const string Menu::AUTHOR = "Анастасия Цегельник";
Menu::Menu() {

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
    WaitForEnter();
}
void Menu::LoadGame() {
    cout << "Функция на данный момент недоступна, появиться в ближайших обновлениях";
    WaitForEnter();
}
void Menu::ShowAbout() {
    cout << "---О программе---" << endl;
    cout << "--Веселая Ферма--" << endl;
    cout << "Версия: " << VERSION << endl;
    cout << AUTHOR << endl;
    WaitForEnter();
}
void Menu::ShowSettings() {
    while (true) {
        cout << "== Настройки == " << endl;
        cout << "1. Уровень сложности (текущий: " << settings.getDifficult() << ")" << endl;
        cout << "2. Количество кур (текущее: " << settings.getCountChickens() << ")" << endl;
        cout << "3. Количество коров (текущее: " << settings.getCountCows() << ")" << endl;
        cout << "4. Количество лошадей (текущее: " << settings.getCountHorses() << ")" << endl;
        cout << "5. Назад" << endl;
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
        case 2: ChangeChickens(); break;
        case 3: ChangeCows(); break;
        case 4:ChangeHorses(); break;
        case 5: return;
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
        }
        else if (choice == options.size() + 1) return;
        else cout << "Неверный выбор" << endl;
    }
}
void Menu::ChangeChickens() {
    const vector<int>& options = settings.getAvailableChickens();
    while (true) {
        cout << "== Количество кур ==" << endl;
        cout << "Текущее: " << settings.getCountChickens() << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << (i + 1) << ". " << options[i] << "\n";
        }
        cout << (options.size() + 1) << ". Назад" << endl;
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число.\n";
            continue;
        }
        if (choice >= 1 && choice <= options.size()) {
            settings.setCountChickens(options[choice - 1]);
        }
        else if (choice == options.size() + 1) return;
        else cout << "Неверный пнукт меню" << endl;
    }
}
void Menu::ChangeCows() {
    const vector<int>& options = settings.getAvailableCows();
    while (true) {
        cout << "== Количество коров ==" << endl;
        cout << "Текущее: " << settings.getCountCows() << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << (i + 1) << ". " << options[i] << "\n";
        }
        cout << (options.size() + 1) << ". Назад" << endl;
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число.\n";
            continue;
        }
        if (choice >= 1 && choice <= options.size()) {
            settings.setCountCows(options[choice - 1]);
        }
        else if (choice == options.size() + 1) return;
        else cout << "Неверный пнукт меню" << endl;
    }
}
void Menu::ChangeHorses() {
    const vector<int>& options = settings.getAvailableHorses();
    while (true) {
        cout << "== Количество лошадей ==" << endl;
        cout << "Текущее: " << settings.getCountHorses() << endl;
        for (int i = 0; i < options.size(); i++) {
            cout << (i + 1) << ". " << options[i] << "\n";
        }
        cout << (options.size() + 1) << ". Назад" << endl;
        cout << "Выбор: ";
        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка ввода. Введите число.\n";
            continue;
        }
        if (choice >= 1 && choice <= options.size()) {
            settings.setCountHorses(options[choice - 1]);
        }
        else if (choice == options.size() + 1) return;
        else cout << "Неверный пнукт меню" << endl;
    }
}

