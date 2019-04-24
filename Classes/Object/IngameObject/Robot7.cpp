#include "Robot7.h"

Robot7::Robot7(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot7";
	description = "Melee and tanky warrior";
	cost = 75;
	maxHealth = 500;
	currentHealth = maxHealth;
	attack = 15;
	defense = 100;
	speed = 5;
	attackRate = 0.5;
	range = 150;
	regeneration = 0;
	special = "";

	upgradeTo = "Robot7_2";
	upgradeGold = 800;
	upgradeEnergy = 3;
	upgradeLevelRequired = 3;

	// thông tin trong game
	animateName = "Robot7";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot7/run/run (1).png", false);




}

Robot7::~Robot7()
{
}
