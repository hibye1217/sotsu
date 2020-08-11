#pragma once

#include <fstream>
#include <string>
using namespace std;

#define DataMgr DataManager::instance()

class DataManager {
private:
	string name = "플레이어";
	int level = 37;
	int exp = 1000000;
public:
	DataManager() {

	}
	static DataManager* instance() {
		static DataManager inst;
		return &inst;
	}
	int getLevel() {
		return level;
	}
};