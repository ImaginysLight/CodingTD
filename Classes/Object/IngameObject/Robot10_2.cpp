#include "Robot10_2.h"





Robot10_2::Robot10_2(int line, bool isLeft) {
	// thông số cơ bản
	objectName = "Robot10_2";
	levelRequired = 2;
	description = "Crazy wolf, fast speed and regeneration";
	cost = 100;
	maxHealth = 500;
	currentHealth = maxHealth;
	attack = 50;
	defense = 100;
	speed = 15;
	attackRate = 0.75;
	range = 75;
	regeneration = 12;
	special = "Enraged: double amount of recover when health below 50%, tripple amount of recover when health below 25%";

	string upgradeTo = "";
	upgradeGold = 0;
	upgradeEnergy = 0;
	upgradeLevelRequired = 0;

	// thông tin trong game
	animateName = "Robot10";
	this->line = line;
	this->isLeft = isLeft;
	this->UpdateIngameInfo("Sprites/robot10/run/run (1).png", false);

	regeneration1 = this->regeneration;
	regeneration2 = this->regeneration * 2;
	regeneration3 = this->regeneration * 3;
	this->Regeneration();
	
}

//Special: Enraged: double amount of recover when health below 50%, tripple amount of recover when health below 25%
void Robot10_2::Regeneration() {
	float healthPercent = (float)this->currentHealth / maxHealth;
	if (healthPercent < 0.25) this->regeneration = regeneration3;
	else if (healthPercent < 0.5)this->regeneration = regeneration2;
	else this->regeneration = regeneration1;

	BaseObjectClass::Regeneration();
}




Robot10_2::~Robot10_2()
{
}
