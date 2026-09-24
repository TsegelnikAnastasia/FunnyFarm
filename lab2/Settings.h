#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;
class Settings {
public:
	Settings();
	string getDifficult() const;
	void setDifficult(const string& value);
	const vector<string>& getAvailableDifficulties()const;

	map<string, int>getAnimals()const;
	void setAnimalCount(const string& name, int count);
	void AddAnimal(const string& name, int count);
	bool HasAnimal(const string& name)const;

	void LoadFromFile(const string& filename);
	void SaveToFile(const string& filename) const;

private:
	string Difficult;
	vector<string> AvailableDifficulties;
	map<string, int>Animals;
};
