#include "Menu.h"
#include "Colors.h"
#include "ConsoleUI.h"
#include "SoundTest.h"
#include <iostream>
#include <clocale>
#include <cstdlib>

int main() {
	system("chcp 1251 > nul");
	setlocale(LC_ALL, "ru");
	SoundTest::PlayFile("sound.wav");
	Colors::Enable();
	Menu menu;
	menu.run();


	return 0;
}