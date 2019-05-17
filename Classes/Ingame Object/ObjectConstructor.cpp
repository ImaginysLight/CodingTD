#include "ObjectConstructor.h"

BaseUnitClass * ObjectConstructor::InitializeObject(string objectName, int line, bool isOwned, int playerId)
{
	if (objectName == "Frozen Kingdom") return new FrozenKingdom(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Frozen Kingdom 2") return new FrozenKingdom_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Frozen Kingdom 3") return new FrozenKingdom_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Flamed Kingdom") return new FlamedKingdom(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Flamed Kingdom 2") return new FlamedKingdom_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Flamed Kingdom 3") return new FlamedKingdom_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

	if (objectName == "Blessed Kingdom") return new BlessedKingdom(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Blessed Kingdom 2") return new BlessedKingdom_2(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Blessed Kingdom 3") return new BlessedKingdom_3(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);

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
	/*Node* result = Node::create();
	auto details = ObjectConstructor::InitializeObject(unitName, 0, 0, 0);

	auto sp_Background = Sprite::create("UI/Unit Details Background.png");
	Tool::setNodeSize(sp_Background, visibleSize.width, visibleSize.height);
	sp_Background->setPosition(visibleSize / 2);
	result->addChild(sp_Background, -1);

	Label* lbl_Name = Tool::CreateLabel(unitName, Tool::defaultTextSize*1.2, Color4B(175,225,200,250));
	lbl_Name->setPosition(Vec2(visibleSize.width*0.05,visibleSize.height*0.9));
	lbl_Name->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Name);

	Sprite* sp_Icon = Sprite::create("Sprites/"+ details->animateName +"/attack/attack (1).png");
	sp_Icon->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.9));
	result->addChild(sp_Icon);

	Label* lbl_Description = Tool::CreateLabel("It slows enemy on the line, can launch Frost Nova which pierce Defense to counter low defense unit.", Tool::defaultTextSize*0.9);
	lbl_Description->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.85));
	lbl_Description->setAnchorPoint(Vec2(0, 1));
	lbl_Description->setMaxLineWidth(visibleSize.width*0.7);
	result->addChild(lbl_Description);
	
	Label* lbl_Gold = Tool::CreateLabel("Gold: ", Tool::defaultTextSize*0.9, Color4B::YELLOW);
	lbl_Gold->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.9));
	lbl_Gold->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Gold);

	Label* lbl_Level = Tool::CreateLabel("Level: ", Tool::defaultTextSize*0.9, Color4B::RED);
	lbl_Level->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.9));
	lbl_Level->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Level);

	Label* lbl_Health = Tool::CreateLabel("Health: ", Tool::defaultTextSize*0.9);
	lbl_Health->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.6));
	lbl_Health->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Health);

	Label* lbl_Attack = Tool::CreateLabel("Attack: ", Tool::defaultTextSize*0.9);
	lbl_Attack->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.51));
	lbl_Attack->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Attack);

	Label* lbl_Defense = Tool::CreateLabel("Defense: ", Tool::defaultTextSize*0.9);
	lbl_Defense->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.42));
	lbl_Defense->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Defense);

	Label* lbl_MoveSpeed = Tool::CreateLabel("Move Speed: ", Tool::defaultTextSize*0.9);
	lbl_MoveSpeed->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.33));
	lbl_MoveSpeed->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_MoveSpeed);

	Label* lbl_AttackSpeed = Tool::CreateLabel("Attack Speed: ", Tool::defaultTextSize*0.9);
	lbl_AttackSpeed->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.24));
	lbl_AttackSpeed->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_AttackSpeed);

	Label* lbl_Range = Tool::CreateLabel("Range: ", Tool::defaultTextSize*0.9);
	lbl_Range->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.15));
	lbl_Range->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Range);

	Label* lbl_Regeneration = Tool::CreateLabel("Regeneration: ", Tool::defaultTextSize*0.9);
	lbl_Regeneration->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.06));
	lbl_Regeneration->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Regeneration);

	Label* lbl_Skill = Tool::CreateLabel("\tThe Presence of Ice: Slow all enemies on the line, decrease Move Speed by 10 / 15 / 20 and Attack Speed by 10 / 17 / 25%\n\tFrost Nova : Launch a snowball toward enemy, dealing 60 / 75 / 100 splash damage in 100 range, pierce 25 / 35 / 50 Defense (Cooldown 7 / 6 / 4 seconds)", Tool::defaultTextSize*0.9);
	lbl_Skill->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.65));
	lbl_Skill->setAnchorPoint(Vec2(0, 1));
	lbl_Skill->setMaxLineWidth(visibleSize.width*0.43);
	result->addChild(lbl_Skill);

	Label* lbl_Upgrade = Tool::CreateLabel("Frost Wyvern 2: 300g, 1e (required lv2)\nFrost Wyvern 3: 450g, 2e(required lv3)", Tool::defaultTextSize*0.9);
	lbl_Upgrade->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.2));
	lbl_Upgrade->setAnchorPoint(Vec2(0, 1));
	lbl_Upgrade->setMaxLineWidth(visibleSize.width*0.43);
	result->addChild(lbl_Upgrade);

	return result;*/
}
