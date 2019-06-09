#include "HotheadedGunner_3.h"

HotheadedGunner_3::HotheadedGunner_3(int line, bool isOwned, int unitId, int playerId)
{
	name = "Hotheaded Gunner 3";
	description = "A cheap robot with high defense.";
	goldCost = 75;
	levelRequired = 1;
	maxHealth = 300;
	currentHealth = maxHealth;
	baseAttack = 30;
	baseDefense = 150;
	baseMoveSpeed = 60;
	baseAttackSpeed = 30;
	range = 250;
	baseRegeneration = 3;

	animationIndexOnTriggerAttack = 6;

	this->UpdateIngameInfo("Sprites/Hotheaded Gunner/attack/attack (1).png", unitId, playerId, isOwned, "Hotheaded Gunner", line);
}

//Steel Skin: reduce damage received by 10% Defense, calculate after Defense. (means -7.5 / -11 / -15 Health lose under normal circumstances).
void HotheadedGunner_3::onDamageReceive(DamageReceive dmg) {
	//Kiểm tra xem người bắn còn sống không
	if (dmg.special == "" && dmg.attackerId != 0) {
		auto attacker = BaseUnitClass::GetUnitById(dmg.attackerId);
		if (attacker == NULL || !attacker->isAlive || attacker->action == "Die") return;
	}

	else if (dmg.special != "") {
		this->ProcessSpecial(this->unitId, dmg);
		return;
	}

	float healthLose = dmg.damage / (0.5 + this->defense / 100);
	healthLose -= this->defense*0.1;
	if (healthLose < 0) healthLose = 0;
	this->currentHealth -= healthLose;
	this->UpdateHealthBar();

	//Hiệu ứng nổ các kiểu
	if (dmg.animateName != "") {
		Sprite* sp_Animation = Sprite::create("Sprites/Blank Image.png");
		//Chỉnh màu animation
		if (this->isOwned)
			sp_Animation->setColor(IngameObject::elementColor[Player::opponentPlayer->elementName]);
		else
			sp_Animation->setColor(IngameObject::elementColor[Player::currentPlayer->elementName]);

		sp_Animation->setPosition(this->sprite->getBoundingBox().size / 2);
		this->sprite->addChild(sp_Animation);
		auto animate = IngameObject::animate[dmg.animateName]->clone();
		sp_Animation->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));
	}

	//Làm cái label trừ máu cho đẹp
	Label* lbl_HealthLose = Tool::CreateLabel("-" + to_string((int)healthLose), Tool::defaultTextSize*0.8, Color4B::RED);
	this->sprite->addChild(lbl_HealthLose);
	if (this->isOwned) lbl_HealthLose->setRotation3D(Vec3(0, 180, 0));
	lbl_HealthLose->setPosition(Vec2(this->sprite->getBoundingBox().size.width / 2, this->sprite->getBoundingBox().size.height));
	lbl_HealthLose->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0, 30)), RemoveSelf::create(), nullptr));

}

HotheadedGunner_3::~HotheadedGunner_3()
{
}

