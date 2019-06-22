﻿#include "CoolBlooded.h"

CoolBlooded::CoolBlooded(int targetId)
{
	this->targetId = targetId;
	this->name = "Cool Blooded";
	this->description = "give an ally a power of Ice, halved their Move Speed and Attack but double Health and Defense. ";

	auto target = BaseUnitClass::GetUnitById(targetId);
	if (target != nullptr && target->isAlive && target->action != "Die") {
		target->baseAttack *= 0.5;
		target->baseMoveSpeed *= 0.5;
		target->baseDefense *= 2;
		float currentHealthPercent = target->currentHealth / (float)target->maxHealth;
		target->maxHealth *= 2;
		target->currentHealth = target->maxHealth*currentHealthPercent;
		target->ReprocessAllStatus("Attack");
		target->ReprocessAllStatus("Defense");
		target->ReprocessAllStatus("MoveSpeed");
		auto sp_Icon = Sprite::create("Skill/Cold Blooded.png");
		sp_Icon->setPosition(target->sprite->getBoundingBox().size / 2);
		Tool::setNodeSize(sp_Icon, 32, 32);
		target->sprite->addChild(sp_Icon);
	}
}

CoolBlooded::~CoolBlooded()
{
}

