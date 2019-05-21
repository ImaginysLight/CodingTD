#include "ObjectConstructor.h"

BaseUnitClass * ObjectConstructor::InitializeObject(string objectName, int line, bool isOwned, int playerId)
{
	if (objectName == "Frozen Kingdom") return new FrozenKingdom(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	/*if (objectName == "Frozen Kingdom 2") return new FrozenKingdom_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Frozen Kingdom 3") return new FrozenKingdom_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);*/

	if (objectName == "Flamed Kingdom") return new FlamedKingdom(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	//if (objectName == "Flamed Kingdom 2") return new FlamedKingdom_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	//if (objectName == "Flamed Kingdom 3") return new FlamedKingdom_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Blessed Kingdom") return new BlessedKingdom(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	/*if (objectName == "Blessed Kingdom 2") return new BlessedKingdom_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Blessed Kingdom 3") return new BlessedKingdom_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);*/

	if (objectName == "Frost Wyvern") return new FrostWyvern(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Frost Wyvern 2") return new FrostWyvern_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Frost Wyvern 3") return new FrostWyvern_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Polar Bear") return new PolarBear(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Polar Bear 2") return new PolarBear_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Polar Bear 3") return new PolarBear_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Volcarona") return new Volcarona(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Volcarona 2") return new Volcarona_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Enraged Ursa") return new EnragedUrsa(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Enraged Ursa 2") return new EnragedUrsa_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Poisonous Butterfly")return new PoisonousButterfly(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Poisonous Butterfly 2")return new PoisonousButterfly_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Vampire Dragon")return new VampireDragon(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Vampire Dragon 2")return new VampireDragon_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Hotheaded Gunner") return new HotheadedGunner(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Hotheaded Gunner 2") return new HotheadedGunner_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Hotheaded Gunner 3") return new HotheadedGunner_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Crazy Wolf") return new CrazyWolf(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Crazy Wolf 2") return new CrazyWolf_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Crazy Wolf 3") return new CrazyWolf_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Helicopter") return new Helicopter(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Helicopter 2") return new Helicopter_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Dead Walker") return new DeadWalker(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Dead Walker 2") return new DeadWalker_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Dead Walker 3") return new DeadWalker_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "UFO Driver") return new UFODriver(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "UFO Driver 2") return new UFODriver_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "UFO Driver 3") return new UFODriver_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "UFO Driver 4") return new UFODriver_4(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Winged Orc") return new WingedOrc(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Winged Orc 2") return new WingedOrc_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Winged Orc 3") return new WingedOrc_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Liquid Assassin") return new LiquidAssassin(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Liquid Assassin 2") return new LiquidAssassin_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Liquid Assassin 3") return new LiquidAssassin_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId); 

	if (objectName == "Elemental Alien") return new ElementalAlien(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Elemental Alien 2") return new ElementalAlien_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Elemental Alien 3") return new ElementalAlien_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Elemental Alien 4") return new ElementalAlien_4(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

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
