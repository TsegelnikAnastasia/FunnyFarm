#include "Save.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;
SaveManager::SaveManager(Player& player, const string& filename)
    : player(player), filename(filename) {
    running = false;
    lastSaveTime = 0;
}
SaveManager::~SaveManager() {
    Stop();
}
void SaveManager::Start() {
    running = true;
    saveThread = std::thread(&SaveManager::saveLoop, this);
}
void SaveManager::Stop() {
    if (!running) return;

    running = false;
    if (saveThread.joinable()) {
        saveThread.join();
    }
}
void SaveManager::saveLoop() {
    const int SLEEP_CHUNK = 1;
    const int TOTAL_SECONDS = 30 * 60;
    while (running) {
        int elapsed = 0;
        while (elapsed < TOTAL_SECONDS && running) {
            std::this_thread::sleep_for(std::chrono::seconds(SLEEP_CHUNK));
            elapsed += SLEEP_CHUNK;
        }
        if (!running) break;
        std::lock_guard<std::mutex>lock(saveMutex);
        SaveGameUnlocked();
    }
}
void SaveManager::SaveNow() {
    if (!CanSave()) return;
    std::lock_guard<std::mutex>lock(saveMutex);
    SaveGameUnlocked();
}
void SaveManager::SaveGameUnlocked() {
    ofstream file(filename);
    if (!file.is_open())return;
    file << "day=" << player.getDay() << "\n";
    file << "money=" << player.getMoney() << "\n";
    file << "actionsLeft=" << player.getActionsLeft() << "\n";
    file << "lastSave=" << time(nullptr) << "\n";
    vector<Animal> animals = player.getAnimals();
    for (const Animal& a : animals) {
        file << "animal=" << a.getSpecies() << "|"
            << a.getSatiety() << "|";
        vector<string> food = a.getAllowedFood();
        for (size_t i = 0; i < food.size(); i++) {
            if (i > 0) file << ",";
            file << food[i];
        }
        file << "|" << a.getPrice() << "\n";
    }
    map<string, int> foodMap = player.getFood();
    for (auto& pair : foodMap) {
        file << "food=" << pair.first << "=" << pair.second << "\n";
    }
    lastSaveTime = time(nullptr);
    file.close();
}
bool SaveManager::CanSave()const {
    time_t now = time(nullptr);
    double diff = difftime(now, lastSaveTime);
    return diff >= 30 * 60;
}
void SaveManager::Load() {
    ifstream file(filename);
    if (!file.is_open()) {
        return;
    }
    player.clearAnimals();
    player.clearFood();
    string line;
    while (getline(file, line)) {
        size_t pos = line.find('=');
        if (pos == string::npos) continue;

        string key = line.substr(0, pos);
        string value = line.substr(pos + 1);

        if (key == "day") {
            player.setDay(stoi(value));
        }
        else if (key == "money") {
            player.setMoney(stoi(value));
        }
        else if (key == "actionsLeft") {
            player.setActions(stoi(value));
        }
        else if (key == "lastSave") {
            lastSaveTime = stoi(value);
        }
        else if (key == "animal") {
            size_t p1 = value.find('|');
            size_t p2 = value.find('|', p1 + 1);
            size_t p3 = value.find('|', p2 + 1);
            string species = value.substr(0, p1);
            int satiety = stoi(value.substr(p1 + 1, p2 - p1 - 1));
            string foodStr = value.substr(p2 + 1, p3 - p2 - 1);
            int price = stoi(value.substr(p3 + 1));
            vector<string> allowedFood;
            size_t start = 0;
            while (true) {
                size_t comma = foodStr.find(',', start);
                if (comma == string::npos) {
                    allowedFood.push_back(foodStr.substr(start));
                    break;
                }
                allowedFood.push_back(foodStr.substr(start, comma - start));
                start = comma + 1;
            }
            Animal a(species, satiety, allowedFood, price);
            player.addAnimal(a);
        }
        else if (key == "food") {
            size_t eq = value.find('=');
            string type = value.substr(0, eq);
            int count = stoi(value.substr(eq + 1));
            player.addFood(type, count);
        }
    }
    file.close();
}
