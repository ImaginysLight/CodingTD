#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

struct KnowledegeTrophy {
	int level = 0;
	string name = "None";
	int NumOfCorrectQuestion = 0;
	int ExpToNext = 0;
	int correctGoldRate = 0;
	int wrongGoldRate = 0;
	KnowledegeTrophy(int level, string name, int NumOfCorrectQuestion, int correctGoldRate, int wrongGoldRate);
	KnowledegeTrophy();
};

struct BattleTrophy {
	int level = 0;
	string name = "None";
	int NumOfKill = 0;
	int ExpToNext = 0;
	int defeatGoldRate = 0;
	int defeatEnergyRate = 0;
	BattleTrophy(int level, string name, int NumOfKill, int defeatGoldRate, int defeatEnergyRate);
	BattleTrophy();
};

struct ConquestTrophy {
	int level = 0;
	string name = "None";
	int NumOfWin = 0;
	int ExpToNext = 0;
	float bonusGold = 0;
	float bonusEnergy = 0;
	ConquestTrophy(int level, string name, int NumOfWin, float bonusGold, float bonusEnergy);
	ConquestTrophy();
};
class Trophy {
public:
	static KnowledegeTrophy CalculateKnowledgeTrophy(int numOfCorrectQuestion);
	static BattleTrophy CalculateBattleTrophy(int numOfKill);
	static ConquestTrophy CalculateConquestTrophy(int numOfWin);
};