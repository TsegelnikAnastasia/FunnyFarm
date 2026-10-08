#pragma once

#include <string>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <ctime>
#include "Player.h"

using namespace std;
class SaveManager {
public:
	SaveManager(Player& player, const string& filename);
	~SaveManager();
	void Start();
	void Stop();
	void SaveNow();
	bool CanSave() const;
	void Load();

private:
	Player& player;
	string filename;
	std::thread saveThread;
	std::atomic<bool>running;
	std::mutex saveMutex;
	time_t lastSaveTime;
	void saveLoop();
	void SaveGameUnlocked();
};