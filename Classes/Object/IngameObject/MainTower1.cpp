#include "MainTower1.h"


MainTower1::MainTower1(bool isLeft) {
	// thông số cơ bản
	objectName = "MainTower1";
	description = "Main tower";
	maxHealth = 1000;
	currentHealth = 999;
	attack = 100;
	defense = 50;
	attackRate = 1;
	range = 800;
	regeneration = 1;

	string upgradeTo = "MainTower1_2";
	int upgradeGold = 200;
	int upgradeEnergy = 3;
	int upgradeLevelRequired = 1;

	// thông tin trong game
	this->line = 2;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/mainTower1/default.png", true);

}

MainTower1::~MainTower1()
{
}
