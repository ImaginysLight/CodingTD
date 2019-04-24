#include "MainTower2.h"

MainTower2::MainTower2(bool isLeft) {
	// thông số cơ bản
	objectName = "MainTower2";
	description = "Main tower";
	maxHealth = 1000;
	currentHealth = maxHealth;
	attack = 100;
	defense = 50;
	attackRate = 1;
	range = 800;
	regeneration = 1;
	
	string upgradeTo = "MainTower2_2";
	int upgradeGold = 200;
	int upgradeEnergy = 3;
	int upgradeLevelRequired = 1;

	// thông tin trong game
	this->line = 2;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/mainTower2/default.png", true);

}

MainTower2::~MainTower2()
{
}
