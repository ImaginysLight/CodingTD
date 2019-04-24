#include "Robot10.h"





Robot10::Robot10(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot10";
	levelRequired = 2;
	description = "Crazy wolf, fast speed and regeneration";
	cost = 100;
	maxHealth = 300;
	currentHealth = maxHealth;
	attack = 50;
	defense = 100;
	speed = 13;
	attackRate = 0.75;
	range = 75;
	regeneration = 6;
	special = "Enraged: double amount of recover when health below 50%";
	
	string upgradeTo = "Robot10_2";
	upgradeGold = 800;
	upgradeEnergy = 5;
	upgradeLevelRequired = 3;

	// thông tin trong game
	animateName = "Robot10";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot10/run/run (1).png", false);

	regeneration1 = this->regeneration;
	regeneration2 = this->regeneration * 2;
	this->Regeneration();
}
//"Enraged: double amount of recover when health below 50%";
void Robot10::Regeneration() {
	float healthPercent = (float)this->currentHealth / maxHealth;
	if (healthPercent < 0.5) this->regeneration = regeneration2;
	else this->regeneration = regeneration1;

	BaseObjectClass::Regeneration();
}



Robot10::~Robot10()
{
}
