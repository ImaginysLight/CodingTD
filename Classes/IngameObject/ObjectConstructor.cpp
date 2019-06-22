#include "ObjectConstructor.h"

BaseUnitClass * ObjectConstructor::InitializeObject(string objectName, int line, bool isOwned, int playerId, int unitId)
{
	if (objectName == "Frozen Kingdom") return new FrozenKingdom(line, isOwned, unitId, playerId);
	if (objectName == "Flamed Kingdom") return new FlamedKingdom(line, isOwned, unitId, playerId);
	if (objectName == "Blessed Kingdom") return new BlessedKingdom(line, isOwned, unitId, playerId);

	if (objectName == "Frost Wyvern 1") return new FrostWyvern_1(line, isOwned, unitId, playerId);
	if (objectName == "Frost Wyvern 2") return new FrostWyvern_2(line, isOwned, unitId, playerId);
	if (objectName == "Frost Wyvern 3") return new FrostWyvern_3(line, isOwned, unitId, playerId);

	if (objectName == "Polar Bear 1") return new PolarBear_1(line, isOwned, unitId, playerId);
	if (objectName == "Polar Bear 2") return new PolarBear_2(line, isOwned, unitId, playerId);
	if (objectName == "Polar Bear 3") return new PolarBear_3(line, isOwned, unitId, playerId);

	if (objectName == "Volcarona 1") return new Volcarona_1(line, isOwned, unitId, playerId);
	if (objectName == "Volcarona 2") return new Volcarona_2(line, isOwned, unitId, playerId);

	if (objectName == "Enraged Ursa 1") return new EnragedUrsa_1(line, isOwned, unitId, playerId);
	if (objectName == "Enraged Ursa 2") return new EnragedUrsa_2(line, isOwned, unitId, playerId);

	if (objectName == "Poisonous Butterfly 1")return new PoisonousButterfly_1(line, isOwned, unitId, playerId);
	if (objectName == "Poisonous Butterfly 2")return new PoisonousButterfly_2(line, isOwned, unitId, playerId);

	if (objectName == "Vampire Dragon 1")return new VampireDragon_1(line, isOwned, unitId, playerId);
	if (objectName == "Vampire Dragon 2")return new VampireDragon_2(line, isOwned, unitId, playerId);

	if (objectName == "Hotheaded Gunner 1") return new HotheadedGunner_1(line, isOwned, unitId, playerId);
	if (objectName == "Hotheaded Gunner 2") return new HotheadedGunner_2(line, isOwned, unitId, playerId);
	if (objectName == "Hotheaded Gunner 3") return new HotheadedGunner_3(line, isOwned, unitId, playerId);

	if (objectName == "Crazy Wolf 1") return new CrazyWolf_1(line, isOwned, unitId, playerId);
	if (objectName == "Crazy Wolf 2") return new CrazyWolf_2(line, isOwned, unitId, playerId);
	if (objectName == "Crazy Wolf 3") return new CrazyWolf_3(line, isOwned, unitId, playerId);

	if (objectName == "Helicopter 1") return new Helicopter_1(line, isOwned, unitId, playerId);
	if (objectName == "Helicopter 2") return new Helicopter_2(line, isOwned, unitId, playerId);

	if (objectName == "Dead Walker 1") return new DeadWalker_1(line, isOwned, unitId, playerId);
	if (objectName == "Dead Walker 2") return new DeadWalker_2(line, isOwned, unitId, playerId);
	if (objectName == "Dead Walker 3") return new DeadWalker_3(line, isOwned, unitId, playerId);

	if (objectName == "UFO Driver 1") return new UFODriver_1(line, isOwned, unitId, playerId);
	if (objectName == "UFO Driver 2") return new UFODriver_2(line, isOwned, unitId, playerId);
	if (objectName == "UFO Driver 3") return new UFODriver_3(line, isOwned, unitId, playerId);
	if (objectName == "UFO Driver 4") return new UFODriver_4(line, isOwned, unitId, playerId);

	if (objectName == "Winged Orc 1") return new WingedOrc_1(line, isOwned, unitId, playerId);
	if (objectName == "Winged Orc 2") return new WingedOrc_2(line, isOwned, unitId, playerId);
	if (objectName == "Winged Orc 3") return new WingedOrc_3(line, isOwned, unitId, playerId);

	if (objectName == "Liquid Assassin 1") return new LiquidAssassin_1(line, isOwned, unitId, playerId);
	if (objectName == "Liquid Assassin 2") return new LiquidAssassin_2(line, isOwned, unitId, playerId);
	if (objectName == "Liquid Assassin 3") return new LiquidAssassin_3(line, isOwned, unitId, playerId); 

	if (objectName == "Elemental Alien 1") return new ElementalAlien_1(line, isOwned, unitId, playerId);
	if (objectName == "Elemental Alien 2") return new ElementalAlien_2(line, isOwned, unitId, playerId);
	if (objectName == "Elemental Alien 3") return new ElementalAlien_3(line, isOwned, unitId, playerId);
	if (objectName == "Elemental Alien 4") return new ElementalAlien_4(line, isOwned, unitId, playerId);

	return nullptr;
}

ui::ScrollView* ObjectConstructor::GetSpecificUnitDetails(string unitName, Size visibleSize)
{
	if (unitName[unitName.size() - 1] > '0' && unitName[unitName.size() - 1] < '9') {
		unitName = unitName.substr(0, unitName.size() - 2);
	}
	Sprite* sp = Sprite::create("Sprites/Unit Detail Images/" + unitName + ".png");
	Tool::setNodeSize(sp, sp->getBoundingBox().size.width / 2.5, sp->getBoundingBox().size.height / 2.5);
	//sp->setAnchorPoint(Vec2(0.5, 0));
	ui::ScrollView* sc = ui::ScrollView::create();
	sc->setContentSize(Size(visibleSize*0.85));
	sc->setInnerContainerSize(sp->getBoundingBox().size);
	sc->setPosition(visibleSize / 2);
	sc->setAnchorPoint(Vec2(0.5, 0.5));
	sc->setBounceEnabled(true);
	sc->addChild(sp);
	sp->setPosition(Vec2(sc->getContentSize().width / 2, sc->getContentSize().height*1.5));
	return sc;
}
