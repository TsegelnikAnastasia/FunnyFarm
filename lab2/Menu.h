#pragma once
#include "Settings.h"
#include <string>
#include <vector>
using namespace std;
class Menu {
public:
	Menu();
	void run();
private:
	static const string VERSION;
	static const string AUTHOR;
	static const int MENU_START_GAME = 1;
	static const int MENU_LOAD_GAME = 2;
	static const int MENU_SETTINGS = 3;
	static const int MENU_ABOUT = 4;
	static const int MENU_EXIT = 5;

	Settings settings;
	void StartGame();
	void LoadGame();
	void ShowSettings();
	void ShowAbout();

	void ChangeDifficult();
	void ShowAnimals();
	void ChangeAnimal(const string& name);
	void AddAnimal();
	void WaitForEnter();
};
