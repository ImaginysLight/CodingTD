#include "HeavenBless.h"

HeavenBless::HeavenBless(int playerId)
{
	this->playerId = playerId;
	this->name = "Heaven Bless";
	this->description = "encourage all allies with a bless from heaven, increase current Health and max Health by 300.";
	for (auto ally : BaseUnitClass::AllIngameUnit_Vector) {
		if (ally->ownerPlayerId == this->playerId
			&& ally->isAlive && ally->action != "Die" && ally->description != "Kingdom"
			) {
			ally->maxHealth += 300;
			ally->currentHealth += 300;
			auto sp = Sprite::create("Sprites/Heaven Bless/heal/heal (1).png");
			ally->root->addChild(sp);
			sp->runAction(Sequence::create(IngameObject::animate["Heaven Bless_heal"]->clone(), RemoveSelf::create(), nullptr));
			sp->setPosition(Vec2(ally->sprite->getBoundingBox().size / 2));
		}
	}

}

HeavenBless::~HeavenBless()
{
}



