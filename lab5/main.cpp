#include "Menu.h"
#include "Colors.h"
#include "ConsoleUI.h"
#include <iostream>
#include <clocale>
#include <cstdlib>

int main() {
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "ru");
	Colors::Enable();
	Menu menu;
	menu.run();


	return 0;
}