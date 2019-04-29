#include "Robot7_2.h"

Robot7_2::Robot7_2(int line, bool isLeft, int id) {
	// thông số cơ bản
	objectName = "Robot7_2";
	description = "Melee and tanky warrior";
	cost = 75;
	maxHealth = 1000;
	currentHealth = maxHealth;
	attack = 15;
	defense = 150;
	speed = 5;
	attackRate = 0.5;
	range = 200;
	regeneration = 0;
	special = "";

	upgradeTo = "";
	upgradeGold = 0;
	upgradeEnergy = 0;
	upgradeLevelRequired = 0;

	// thông tin trong game
	this->id = id;
	animateName = "Robot7";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot7/run/run (1).png", false);




}

Robot7_2::~Robot7_2()
{
}
