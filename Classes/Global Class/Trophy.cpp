#include "Trophy.h"

KnowledegeTrophy Trophy::CalculateKnowledgeTrophy(int numOfCorrectQuestion)
{
	vector<KnowledegeTrophy> vec;
	vec.push_back(KnowledegeTrophy(1, "Brainless", 0, 10, 5));
	vec.push_back(KnowledegeTrophy(2, "Noob", 100, 15, 5));
	vec.push_back(KnowledegeTrophy(3, "Amateur", 200, 25, 5));
	vec.push_back(KnowledegeTrophy(4, "Excellence", 400, 30, 10));
	vec.push_back(KnowledegeTrophy(5, "Profession", 800, 36, 15));
	vec.push_back(KnowledegeTrophy(6, "Erudition", 1200, 42, 20));
	vec.push_back(KnowledegeTrophy(7, "Transcendence", 2000, 50, 25));
	for (int i = 1; i < vec.size(); i++) {
		if (numOfCorrectQuestion < vec[i].NumOfCorrectQuestion)
			return vec[i - 1];
	}
	return vec[vec.size() - 1];
}

BattleTrophy Trophy::CalculateBattleTrophy(int numOfKill)
{
	vector<BattleTrophy> vec;
	vec.push_back(BattleTrophy(1, "Rookie", 0, 5, 1));
	vec.push_back(BattleTrophy(2, "Experienced Slayer", 500, 8, 2));
	vec.push_back(BattleTrophy(3, "Brutal Assassin", 1000, 12, 5));
	vec.push_back(BattleTrophy(4, "Serial Murderer", 3000, 15, 8));
	vec.push_back(BattleTrophy(5, "Alexander Magnus", 5000, 20, 10));
	for (int i = 1; i < vec.size(); i++) {
		if (numOfKill < vec[i].NumOfKill)
			return vec[i - 1];
	}
	return vec[vec.size() - 1];
}

ConquestTrophy Trophy::CalculateConquestTrophy(int numOfWin)
{
	vector<ConquestTrophy> vec;
	vec.push_back(ConquestTrophy(1, "Wise Strategist", 0, 1, 0.5));
	vec.push_back(ConquestTrophy(2, "Excellent King", 160, 3, 1));
	vec.push_back(ConquestTrophy(3, "Immortal Emperor", 400, 5, 1.5));
	for (int i = 1; i < vec.size(); i++) {
		if (numOfWin < vec[i].NumOfWin)
			return vec[i - 1];
	}
	return vec[vec.size() - 1];
}

KnowledegeTrophy::KnowledegeTrophy(int level, string name, int NumOfCorrectQuestion, int correctGoldRate, int wrongGoldRate)
{
	this->level = level;
	this->name = name;
	this->NumOfCorrectQuestion = NumOfCorrectQuestion;
	this->correctGoldRate = correctGoldRate;
	this->wrongGoldRate = wrongGoldRate;
}

KnowledegeTrophy::KnowledegeTrophy()
{
}

BattleTrophy::BattleTrophy(int level, string name, int NumOfKill, int defeatGoldRate, int defeatEnergyRate)
{
	this->level = level;
	this->name = name;
	this->NumOfKill = NumOfKill;
	this->defeatGoldRate = defeatGoldRate;
	this->defeatEnergyRate = defeatEnergyRate;
}

BattleTrophy::BattleTrophy()
{
}

ConquestTrophy::ConquestTrophy(int level, string name, int NumOfWin, int bonusGold, float bonusEnergy)
{
	this->level = level;
	this->name = name;
	this->NumOfWin = NumOfWin;
	this->bonusGold = bonusGold;
	this->bonusEnergy = bonusEnergy;
}

ConquestTrophy::ConquestTrophy()
{
}
