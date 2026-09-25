#include "Menu.h"
#include <clocale>
#include <cstdlib>
int main() {
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "ru");
	Menu menu;
	menu.run();


	return 0;
}