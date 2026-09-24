#include "Settings.h"
Settings::Settings() {
	Difficult = "Средний";
	CountChickens = 5;
	CountCows = 3;
	CountHorses = 1;
	AvailableDifficulties = { "Лёгкий", "Средний", "Сложный" };
	AvailableChickens = { 1, 3, 5, 10 };
	AvailableCows = { 1, 2, 3, 5 };
	AvailableHorses = { 1, 2, 3 };
}
string Settings::getDifficult()const {
	return Difficult;
}
int Settings::getCountChickens()const {
	return CountChickens;
}
int Settings::getCountCows()const {
	return CountCows;
}
int Settings::getCountHorses()const {
	return CountHorses;
}

void Settings::setDifficult(const string& value) {
	Difficult = value;
}
void Settings::setCountChickens(int value) {
	CountChickens = value;
}
void Settings::setCountCows(int value) {
	CountCows = value;
}
void Settings::setCountHorses(int value) {
	CountHorses = value;
}

const vector<string>& Settings::getAvailableDifficulties()const {
	return AvailableDifficulties;
}
const vector<int>& Settings::getAvailableChickens()const {
	return AvailableChickens;
}
const vector<int>& Settings::getAvailableCows()const {
	return AvailableCows;
}
const vector <int>& Settings::getAvailableHorses()const {
	return AvailableHorses;
}