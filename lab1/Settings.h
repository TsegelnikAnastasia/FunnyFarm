#pragma once
#include <string>
#include <vector>
using namespace std;
class Settings {
public:
	Settings();
	string getDifficult() const;
	int getCountChickens()const;
	int getCountCows() const;
	int getCountHorses() const;

	void setDifficult(const string& value);
	void setCountChickens(int value);
	void setCountCows(int value);
	void setCountHorses(int value);

	const vector<string>& getAvailableDifficulties()const;
	const vector<int>& getAvailableChickens()const;
	const vector<int>& getAvailableCows()const;
	const vector<int>& getAvailableHorses()const;
private:
	string Difficult;
	int CountChickens;
	int CountCows;
	int CountHorses;

	vector<string> AvailableDifficulties;
	vector<int> AvailableChickens;
	vector<int> AvailableCows;
	vector<int> AvailableHorses;
};
