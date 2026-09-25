#include "Settings.h"
#include <fstream>
Settings::Settings() {
	Difficult = "Средний";
	AvailableDifficulties = { "Лёгкий", "Средний", "Сложный" };
	Animals["Курица"] = 1;
	Animals["Корова"] = 1;
	Animals["Лошадь"] = 1;
}
string Settings::getDifficult()const {
	return Difficult;
}

void Settings::setDifficult(const string& value) {
	Difficult = value;
}

const vector<string>& Settings::getAvailableDifficulties()const {
	return AvailableDifficulties;
}

map<string, int> Settings::getAnimals()const {
	return Animals;
}
void Settings::setAnimalCount(const string& name, int count) {
	if (HasAnimal(name)) {
		Animals[name] = count;
	}
}
void Settings::AddAnimal(const string& name, int count) {
	Animals[name]=count;
}
bool Settings::HasAnimal(const string& name) const {
	return Animals.find(name) != Animals.end();
}
void Settings::SaveToFile(const string& filename) const {
	ofstream file(filename);
	if (!file.is_open()) {
		return;
	}
	file << "Difficult=" << Difficult << endl;
	for (const auto& pair : Animals) {
		file << pair.first << "=" << pair.second << "\n";
	}
	file.close();
}
void Settings::LoadFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		SaveToFile(filename);
		return;
	}
	Animals.clear();
	string line;
	while (getline(file, line)) {
		size_t pos = line.find('=');
		if (pos == string::npos) {
			continue;
		}
		string key = line.substr(0, pos);
		string value = line.substr(pos + 1);

		if (key == "Difficult") {
			Difficult = value;
		}
		else Animals[key] = stoi(value);
	}
	file.close();
}