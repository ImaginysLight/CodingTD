#include "CardScene.h"

using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * CardScene::createScene()
{
	return CardScene::create();
}

bool CardScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	scroll_UI = ui::ScrollView::create();
	scroll_UI->setContentSize(Size(visibleSize));
	scroll_UI->setInnerContainerSize(Size(visibleSize.width, 1200));
	scroll_UI->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.5));
	scroll_UI->setAnchorPoint(Vec2(0.5, 0.5));
	scroll_UI->setBounceEnabled(true);
	this->addChild(scroll_UI);

	dynamicUI = Node::create();
	scroll_UI->addChild(dynamicUI);
	dynamicUI->setPositionY(scroll_UI->getInnerContainerSize().height - visibleSize.height);

	auto sp_Friendship = Sprite::create("UI/CardScene/friendship.png");
	sp_Friendship->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.9));
	this->addChild(sp_Friendship);

	lbl_Friendship = Tool::CreateLabel(to_string(Player::currentPlayer->friendshipPoint), Tool::defaultTextSize*1.25, Color4B::GREEN);
	lbl_Friendship->setName("lbl_Friendship");
	lbl_Friendship->setPosition(Vec2(100,39));
	sp_Friendship->addChild(lbl_Friendship);
	
	auto btn_LobbyScene = Tool::CreateButtonWithoutSprite("btn_LobbyScene", "<< Back To Lobby", Tool::defaultTextSize, Color3B::MAGENTA);
	btn_LobbyScene->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(1, Vec2(25, 0)),
		MoveBy::create(1, Vec2(-25, 0)),
		nullptr)));
	btn_LobbyScene->setPosition(Vec2(visibleSize.width*0.08, visibleSize.height*0.05));
	btn_LobbyScene->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	this->addChild(btn_LobbyScene,2);

	friendshipNode = Node::create();
	friendshipNode->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*-0.85));
	dynamicUI->addChild(friendshipNode);

	detailNode_Before = Node::create();
	detailNode_Before->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height*0.05));
	dynamicUI->addChild(detailNode_Before);

	auto lbl_After = Tool::CreateLabel("After Friendship Effect", Tool::defaultTextSize*1.2, Color4B::GREEN);
	lbl_After->setName("lbl_After");
	lbl_After->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*-0.275));
	dynamicUI->addChild(lbl_After);

	detailNode_After = Node::create();
	detailNode_After->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height*-0.5));
	dynamicUI->addChild(detailNode_After);

	spriteNode = Node::create();
	spriteNode->setPosition(Vec2(visibleSize.width*0.17, visibleSize.height*0.95));
	dynamicUI->addChild(spriteNode);

	skillNode = Node::create();
	skillNode->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.85));
	dynamicUI->addChild(skillNode);

	scroll_Navigator = ui::ScrollView::create();
	scroll_Navigator->setContentSize(Size(200, 400));
	scroll_Navigator->setInnerContainerSize(Size(200, 900));
	scroll_Navigator->setPosition(Vec2(0, visibleSize.height*0.815));
	scroll_Navigator->setAnchorPoint(Vec2(0, 1));
	scroll_Navigator->setBounceEnabled(true);
	this->addChild(scroll_Navigator);

	vector<string> cardName;
	cardName.push_back("Hotheaded Gunner");
	cardName.push_back("Crazy Wolf");
	cardName.push_back("Helicopter");
	cardName.push_back("Dead Walker");
	cardName.push_back("UFO Driver");
	cardName.push_back("Winged Orc");
	cardName.push_back("Liquid Assassin");
	cardName.push_back("Elemental Alien");

	cardName.push_back("Frost Wyvern");
	cardName.push_back("Polar Bear");
	cardName.push_back("Volcarona");
	cardName.push_back("Enraged Ursa");
	cardName.push_back("Poisonous Butterfly");
	cardName.push_back("Vampire Dragon");

	cardName.push_back("Frozen Kingdom");
	cardName.push_back("Flamed Kingdom");
	cardName.push_back("Blessed Kingdom");
	for (int i = 0; i < cardName.size(); i++) {
		Button* btn = Tool::CreateButtonWithoutSprite(cardName[i], cardName[i], Tool::defaultTextSize, Color3B::GRAY);
		btn->setAnchorPoint(Vec2(0, 0.5));
		btn->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Navigator_Click, this));
		btn->setPosition(Vec2(10, 850 - 50 * i));
		scroll_Navigator->addChild(btn);
		vec_Card.insert({ cardName[i],btn });
		auto sp = Sprite::create("UI/CardScene/UnitDetailsTable.png");
		sp->setPosition(Vec2(10, 850 - 50 * i));
		Tool::setNodeSize(sp, 200, 50);
		sp->setAnchorPoint(Vec2(0.1, 0.5));
		scroll_Navigator->addChild(sp,-1);
	}
	vec_Card["Hotheaded Gunner"]->setTitleColor(Color3B(175, 225, 200));
	CardScene::RefreshScene("Hotheaded Gunner");

	this->schedule(schedule_selector(LobbyScene::UpdateAudio), 1);
	return true;
}

void CardScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

Node * CardScene::GetUnitInfo(BaseUnitClass * unit)
{
	return nullptr;
}

void CardScene::btn_UpFriendship_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		if (Player::currentPlayer->friendshipPoint < 1) {
			RunActionNotify("You don't have enough friendship point!");
		}
		else {
			Player::currentPlayer->friendshipPoint--;
			Player::currentPlayer->friendshipLevel[name] ++;
			RefreshScene(name);
			RunActionNotify("Upgrade successful!");
			Player::UploadPlayerInfo(Player::currentPlayer);
		}
		((Node*)pSender)->getParent()->runAction(RemoveSelf::create());
		lbl_Friendship->setString(to_string(Player::currentPlayer->friendshipPoint));
	}
}

void CardScene::btn_DownFriendship_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		Player::currentPlayer->friendshipPoint++;
		Player::currentPlayer->friendshipLevel[name] --;
		RefreshScene(name);
		RunActionNotify("Downgrade successful!");
		Player::UploadPlayerInfo(Player::currentPlayer);

		((Node*)pSender)->getParent()->runAction(RemoveSelf::create());
		lbl_Friendship->setString(to_string(Player::currentPlayer->friendshipPoint));

	}
}

void CardScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect(Audio::GetButtonClickAudio().c_str(), false);
		/*if (((Node*)pSender)->getName() == "btn_PlayerScene"){
			Director::getInstance()->replaceScene(PlayerInformationScene::createScene());
		}*/
		if (((Node*)pSender)->getName() == "btn_LobbyScene") {
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
		auto btn = (Button*)pSender;
		if (btn->getTitleText() == "Up") {
			if (Player::currentPlayer->friendshipLevel[btn->getName()] == 5)
				RunActionNotify(btn->getName() + "'s Friendship already at maximum level!");
			else {
				auto notify = Tool::CreateNotificationTable("Upgrade 1 Friendship level for " + btn->getName(), "Cancel", "Process");
				notify->setPosition(visibleSize / 2);
				((Button*)notify->getChildByName("btn_Left"))->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_UpFriendship_Click, this));
				((Button*)notify->getChildByName("btn_Left"))->setName(btn->getName());
				this->addChild(notify);
			}
		}
		else if (btn->getTitleText() == "Down") {
			if (Player::currentPlayer->friendshipLevel[btn->getName()] == 0)
				RunActionNotify(btn->getName() + "'s Friendship already at minimum level!");
			else {
				auto notify = Tool::CreateNotificationTable("Downgrade 1 Friendship level for " + btn->getName(), "Cancel", "Process");
				notify->setPosition(visibleSize / 2);
				((Button*)notify->getChildByName("btn_Left"))->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_DownFriendship_Click, this));
				((Button*)notify->getChildByName("btn_Left"))->setName(btn->getName());
				this->addChild(notify);
			}
		}
	}
}

void CardScene::btn_Navigator_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		for (auto card : vec_Card) {
			card.second->setTitleColor(Color3B::GRAY);
		}
		vec_Card[name]->setTitleColor(Color3B(175, 225, 200));
		if(name.find("Kingdom") == std::string::npos)
			RefreshScene(name);
		else RefreshSceneKingdom(name);
	}
}

vector<string> CardScene::GetSkillDetail(string unitName)
{
	vector<string> result;
	if (unitName == "Frost Wyvern") {
		result.push_back("The Presence of Ice\nSlow all enemies on the line, decrease Move Speed by 10 / 15 / 20 and Attack Speed by 10 / 17 / 25 %");
		result.push_back("Frost Nova\nLaunch a snowball toward enemy, dealing 60 / 75 / 100 splash damage in 150 range, pierce 25 / 35 / 50 Defense (Cooldown 7 / 6 / 4 seconds)");
	}
	else if (unitName == "Polar Bear") {
		result.push_back("Ice Punch\nEach 3th attack will knock the target into the air, dealing 100 / 200 / 300 bonus damage and stun them for 1 / 2 / 3 seconds.");
		result.push_back("Icy Body\nWhoever attacked this bear will tremble, decrease 12 / 16 / 20% Attack. (Trigger after hit, last 5 seconds)");
	}
	else if (unitName == "Volcarona") {
		result.push_back("The Presence of Fire\nBurn all enemies on the line, dealing 5 / 7 pure dps and decrease Regeneration by 30 / 35%.");
		result.push_back("Fire Armor\nBuff an ally with Fire Armor, increase Defense by 25 / 30 and reflect 25 / 30% damage to whoever attacks them. (Duration: 9s, Cooldown: 10s)");
	}
	else if (unitName == "Enraged Ursa") {
		result.push_back("Demon Heart\nIncrease 1 / 1.5% Attack per 1% Health lose.");
		result.push_back("Lucifer's Indignation\nBecome angry when Health below 75%, improve normal attacks, causing splash damage equal to 35% Attack within 400 range around its target.");
	}
	else if (unitName == "Poisonous Butterfly") {
		result.push_back("The Presence of Life\nBless all allies on the line, increase Regeneration by 3 / 5 and Attack Speed by 15 / 25%");
		result.push_back("Agent Orange\nImprove normal attacks with Agent Orange, dealing bonus damage equal to 2 / 3% the target's Max Health, and decrease target's Defense percent equal to bonus damage.");
	}
	else if (unitName == "Vampire Dragon") {
		result.push_back("Vampire Touch\nImprove normal attacks, restores Current Health by 20 / 35% of damage dealt, and steal 0.3 / 0.5% target's Max Health.");
		result.push_back(" Blessings From Demeter\nOn death, it will respawn with power proportional to amount of Health stolen, this ability only trigger one time. ");
	}
	else if (unitName == "Hotheaded Gunner") {
		result.push_back("Steel Skin\nReduce damage received by 10% Defense, calculate after Defense. (means -7.5 / -11 / -15 Health lose under normal circumstances)");
	}
	else if (unitName == "UFO Driver") {
		result.push_back("Wrong Button\nEach 5 / 4 / 4 / 3th attack, the driver presses the wrong button, causing the next attack to increase damage by 2 / 2.4 / 2.8 / 3, but the UFO runs of energy in 3.5 / 2.5 / 2 / 2 second.");
	}
	else if (unitName == "Winged Orc") {
		result.push_back("Deathwing\nBlows away everything on attack, knockback both itself and the enemy by 25 / 50 / 100 range if the target is a unit, bonus 75 damage if the target is a building.");
	}
	else if (unitName == "Helicopter") {
		result.push_back("Keen Eyes\nAttack upto 2 / 3 targets in all lines.");
	}
	else if (unitName == "Crazy Wolf") {
		result.push_back("Berserker's Blood\nDouble amount of Regeneration when Health below 35 / 55 / 75 %.\nTripple amount of Regeneration when Health below 0 / 20 / 50 %.\nQuadruplicate amount of Regeneration when Health below 0 / 10 / 25 %.");
	}
	else if (unitName == "Dead Walker") {
		result.push_back("Rotten Aura\nDecrease enemies Attack and Defense by 5 / 7.5 / 10% in 500 range around in all line. (last 5 seconds)");
	}
	else if (unitName == "Liquid Assassin") {
		result.push_back("Death Scratch\nBlink toward an enemy on any line and scratch, dealt 100 / 175 / 250 bonus damage on attack. This ability has 1 charge and will be restored when an enemy dies within 550 / 650 / 750 range around Assassin, cooldown 5 seconds.");
	}
	else if (unitName == "Elemental Alien") {
		result.push_back("Ice: Icy Claws: Dealt bonus damage as 13 / 20 / 27 / 35% target's Attack on attack.\n\nFire: Fiery Claws: Dealt bonus damage as 3 / 3.8 / 4.5 / 5* target's base Regeneration and make them unhealable for 1 / 2 / 3 / 4 seconds on attack.\n\nNature: Vitality Claws: Lifesteal 4 / 4.8 / 5.5 / 6% target's Max Health multiply (90 / 100 / 110 / 120 / Move Speed) on attack.");
	}
	else if (unitName == "Frozen Kingdom") {
		result.push_back("Frozen Aura\nWhoever entered this tower range without permission will be trembled, decrease Attack Speed by 10 / 15 / 20%.");
	}
	else if (unitName == "Flamed Kingdom") {
		result.push_back("Burning Aura\nWhoever entered this tower range without permission will be burned, Regeneration decrease to -8 / -14 / -20 hps.");
	}
	else if (unitName == "Blessed Kingdom") {
		result.push_back("Blessing Aura\nAll allies within this tower range will be blessed, restoring 2 / 2.75 / 3.5% hps.");
	}
	return result;
}

void CardScene::RefreshScene(string unitName)
{
	dynamicUI->getChildByName("lbl_After")->setVisible(true);

	CardScene::friendshipNode->removeAllChildrenWithCleanup(true);
	auto friendship = FriendShipUpgrade(unitName, Player::currentPlayer->friendshipLevel[unitName]);
	friendship.btn_Up->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	friendship.btn_Down->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	friendshipNode->addChild(friendship.root);

	CardScene::detailNode_Before->removeAllChildrenWithCleanup(true);
	int currentFriendship = Player::currentPlayer->friendshipLevel[unitName];
	Player::currentPlayer->friendshipLevel[unitName] = 0;
	vector<UnitDetailsTable> detailNodeBefore, detailNodeAfter;
	int numOfLevel = IngameObject::GetNumOfLevel(unitName);

	for (int i = 1; i <= numOfLevel; i++) {
		detailNodeBefore.push_back(UnitDetailsTable(*ObjectConstructor::InitializeObject(unitName+ " " + to_string(i), 0, 1, 0, -1), Vec2(0, 0)));
		detailNodeBefore[i - 1].root->setName("level" + to_string(i));
		detailNode_Before->addChild(detailNodeBefore[i - 1].root);
	}
	if (numOfLevel == 2) detailNode_Before->getChildByName("level1")->setPositionX(visibleSize.width*0.2);
	if (numOfLevel == 3) detailNode_Before->getChildByName("level1")->setPositionX(visibleSize.width*0.1);
	for (int i = 1; i < detailNodeBefore.size(); i++) {
		detailNode_Before->getChildByName("level" + to_string(i + 1))->setPosition(detailNode_Before->getChildByName("level" + to_string(i))->getPosition() + Vec2(visibleSize.width*0.2,0));
		
		auto object = ObjectConstructor::InitializeObject(unitName + " " + to_string(i), 0, 1, 0, -1);
		auto lbl_UpgradeGold = Tool::CreateLabel("Gold: " + to_string(object->upgradeGoldCost), Tool::defaultTextSize, Color4B::YELLOW, TextHAlignment::CENTER);
		lbl_UpgradeGold->setPosition(detailNode_Before->getChildByName("level" + to_string(i))->getPosition() + Vec2(visibleSize.width*0.1, visibleSize.height*0.35));
		detailNode_Before->addChild(lbl_UpgradeGold);

		auto lbl_UpgradeKnowledge = Tool::CreateLabel("Knowledge: " + to_string(object->upgradeKnowledgeCost), Tool::defaultTextSize, Color4B(175, 225, 200, 255), TextHAlignment::CENTER);
		lbl_UpgradeKnowledge->setPosition(detailNode_Before->getChildByName("level" + to_string(i))->getPosition() + Vec2(visibleSize.width*0.1, visibleSize.height*0.3));
		detailNode_Before->addChild(lbl_UpgradeKnowledge);
		
		auto lbl_LevelRequired = Tool::CreateLabel("Kingdom Required: " + to_string(object->upgradeLevelRequired), Tool::defaultTextSize, Color4B::RED, TextHAlignment::CENTER);
		lbl_LevelRequired->setPosition(detailNode_Before->getChildByName("level" + to_string(i))->getPosition() + Vec2(visibleSize.width*0.1, visibleSize.height*0.25));
		detailNode_Before->addChild(lbl_LevelRequired);

		auto sp_Arrow = Sprite::create("UI/CardScene/Long Arrow.png");
		sp_Arrow->setScale(0.25);
		sp_Arrow->setRotation(-90);
		sp_Arrow->setPosition(detailNode_Before->getChildByName("level" + to_string(i))->getPosition() + Vec2(visibleSize.width*0.1, visibleSize.height*0.2));
		detailNode_Before->addChild(sp_Arrow);
	}

	CardScene::detailNode_After->removeAllChildrenWithCleanup(true);
	Player::currentPlayer->friendshipLevel[unitName] = currentFriendship;
	for (int i = 1; i <= numOfLevel; i++) {
		detailNodeAfter.push_back(UnitDetailsTable(*ObjectConstructor::InitializeObject(unitName + " " + to_string(i), 0, 1, 0, -1), Vec2(0, 0)));
		detailNodeAfter[i - 1].root->setName("level" + to_string(i));
		detailNode_After->addChild(detailNodeAfter[i - 1].root);
	}
	detailNode_After->getChildByName("level1")->setPosition(detailNode_Before->getChildByName("level1")->getPosition());
	for (int i = 1; i < detailNodeBefore.size(); i++) {
		detailNode_After->getChildByName("level" + to_string(i + 1))->setPosition(detailNode_Before->getChildByName("level" + to_string(i))->getPosition() + Vec2(visibleSize.width*0.2, 0));
	}

	CardScene::spriteNode->removeAllChildrenWithCleanup(true);
	auto sp = Sprite::create("Sprites/" + unitName + "/card.png");
	sp->setPosition(Vec2(0, visibleSize.height*-0.25));
	spriteNode->addChild(sp);
	auto lbl_Gold = Tool::CreateLabel(to_string(ObjectConstructor::InitializeObject(unitName + " 1", 0, 1, 0, -1)->goldCost), Tool::defaultTextSize*0.8, Color4B::YELLOW);
	lbl_Gold->setPosition(Vec2(-5,-89));
	lbl_Gold->enableBold();
	spriteNode->addChild(lbl_Gold);
	auto lbl_Name = Tool::CreateLabel(unitName, Tool::defaultTextSize*1.5, Color4B(200, 75, 150, 255));
	lbl_Name->setPosition(Vec2(visibleSize.width*0.23, -15));
	spriteNode->addChild(lbl_Name);

	if (unitName.find("Frost Wyvern") != std::string::npos || unitName.find("Polar Bear") != std::string::npos) lbl_Name->setTextColor(Color4B(175,225,250,255));
	if (unitName.find("Volcarona") != std::string::npos || unitName.find("Enraged Ursa") != std::string::npos) lbl_Name->setTextColor(Color4B::RED);
	if (unitName.find("Poisonous Butterfly") != std::string::npos || unitName.find("Vampire Dragon") != std::string::npos) lbl_Name->setTextColor(Color4B(175,225,200,255));


	CardScene::skillNode->removeAllChildrenWithCleanup(true);
	Label* lbl_Skill = Tool::CreateLabel("",Tool::defaultTextSize*0.9,Color4B(255,230,255,255),TextHAlignment::CENTER);
	lbl_Skill->setAnchorPoint(Vec2(0, 1));
	lbl_Skill->setMaxLineWidth(400);
	skillNode->addChild(lbl_Skill);
	auto skillDetail = CardScene::GetSkillDetail(unitName);
	for (auto detail : skillDetail) {
		lbl_Skill->setString(lbl_Skill->getString() + detail + "\n\n");
	}
}

void CardScene::RefreshSceneKingdom(string unitName)
{
	dynamicUI->getChildByName("lbl_After")->setVisible(false);
	CardScene::friendshipNode->removeAllChildrenWithCleanup(true);

	CardScene::detailNode_Before->removeAllChildrenWithCleanup(true);
	auto KingdomLevel1 = ObjectConstructor::InitializeObject(unitName, 0, 0, 0, -1);
	auto UnitDetail = UnitDetailsTable(*KingdomLevel1, Vec2(0, 0));
	UnitDetail.root->setPositionX(visibleSize.width*0.1);
	detailNode_Before->addChild(UnitDetail.root);
	auto lbl_UpgradeGold1 = Tool::CreateLabel("Gold: " + to_string(KingdomLevel1->upgradeGoldCost), Tool::defaultTextSize, Color4B::YELLOW, TextHAlignment::CENTER);
	lbl_UpgradeGold1->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.35));
	detailNode_Before->addChild(lbl_UpgradeGold1);
	auto lbl_UpgradeKnowledge1 = Tool::CreateLabel("Knowledge: " + to_string(KingdomLevel1->upgradeKnowledgeCost), Tool::defaultTextSize, Color4B(175, 225, 200, 255), TextHAlignment::CENTER);
	lbl_UpgradeKnowledge1->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.3));
	detailNode_Before->addChild(lbl_UpgradeKnowledge1);
	auto sp_Arrow1 = Sprite::create("UI/CardScene/Long Arrow.png");
	sp_Arrow1->setScale(0.25);
	sp_Arrow1->setRotation(-90);
	sp_Arrow1->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.2));
	detailNode_Before->addChild(sp_Arrow1);

	KingdomLevel1->Upgrade();
	UnitDetail = UnitDetailsTable(*KingdomLevel1, Vec2(0, 0));
	UnitDetail.root->setPositionX(visibleSize.width*0.3);
	detailNode_Before->addChild(UnitDetail.root);
	auto lbl_UpgradeGold2 = Tool::CreateLabel("Gold: " + to_string(KingdomLevel1->upgradeGoldCost), Tool::defaultTextSize, Color4B::YELLOW, TextHAlignment::CENTER);
	lbl_UpgradeGold2->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.35));
	detailNode_Before->addChild(lbl_UpgradeGold2);
	auto lbl_UpgradeKnowledge2 = Tool::CreateLabel("Knowledge: " + to_string(KingdomLevel1->upgradeKnowledgeCost), Tool::defaultTextSize, Color4B(175, 225, 200, 255), TextHAlignment::CENTER);
	lbl_UpgradeKnowledge2->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.3));
	detailNode_Before->addChild(lbl_UpgradeKnowledge2);
	auto sp_Arrow2 = Sprite::create("UI/CardScene/Long Arrow.png");
	sp_Arrow2->setScale(0.25);
	sp_Arrow2->setRotation(-90);
	sp_Arrow2->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.2));
	detailNode_Before->addChild(sp_Arrow2);

	KingdomLevel1->Upgrade();
	UnitDetail = UnitDetailsTable(*KingdomLevel1, Vec2(0, 0));
	UnitDetail.root->setPositionX(visibleSize.width*0.5);
	detailNode_Before->addChild(UnitDetail.root);

	CardScene::detailNode_After->removeAllChildrenWithCleanup(true);

	CardScene::spriteNode->removeAllChildrenWithCleanup(true);
	auto sp = Sprite::create("Sprites/" + unitName + "/default.png");
	Tool::setNodeSize(sp, 200, 200);
	sp->setPosition(Vec2(0, visibleSize.height*-0.25));
	spriteNode->addChild(sp);
	auto lbl_Name = Tool::CreateLabel(unitName, Tool::defaultTextSize*1.5, Color4B(175, 255, 250, 255));
	lbl_Name->setPosition(Vec2(visibleSize.width*0.23, -15));
	spriteNode->addChild(lbl_Name);

	if (unitName.find("Flamed") != std::string::npos) lbl_Name->setTextColor(Color4B::RED);
	if (unitName.find("Blessed") != std::string::npos) lbl_Name->setTextColor(Color4B(175,225,200,255));

	CardScene::skillNode->removeAllChildrenWithCleanup(true);
	Label* lbl_Skill = Tool::CreateLabel("", Tool::defaultTextSize*0.9, Color4B(255, 230, 255, 255), TextHAlignment::CENTER);
	lbl_Skill->setAnchorPoint(Vec2(0, 1));
	lbl_Skill->setMaxLineWidth(400);
	skillNode->addChild(lbl_Skill);
	auto skillDetail = CardScene::GetSkillDetail(unitName);
	for (auto detail : skillDetail) {
		lbl_Skill->setString(lbl_Skill->getString() + detail + "\n\n");
	}
}

UnitDetailsTable::UnitDetailsTable(BaseUnitClass object, Vec2 position)
{
	this->root = Node::create();

	this->lbl_Name = Tool::CreateLabel(object.name, Tool::defaultTextSize*0.8);
	lbl_Name->enableBold();
	lbl_Name->setPosition(position + Vec2(0,85));
	root->addChild(lbl_Name);

	this->sp_Health = Sprite::create("UI/CardScene/Icon/health.png");
	sp_Health->setPosition(position + Vec2(-40, 50));
	Tool::setNodeSize(sp_Health, 40, 40);
	root->addChild(sp_Health);
	this->lbl_Health = Tool::CreateLabel(to_string((int)object.currentHealth) + " / " + to_string((int)object.maxHealth), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Health->setPosition(position + Vec2(20, 50));
	root->addChild(lbl_Health);

	this->sp_Attack = Sprite::create("UI/CardScene/Icon/attack.png");
	sp_Attack->setPosition(position + Vec2(-50, 0));
	Tool::setNodeSize(sp_Attack, 40, 40);
	root->addChild(sp_Attack);
	this->lbl_Attack = Tool::CreateLabel(to_string((int)object.attack), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Attack->setPosition(position + Vec2(-25, 0));
	lbl_Attack->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Attack);

	this->sp_AttackSpeed = Sprite::create("UI/CardScene/Icon/attackSpeed.png");
	sp_AttackSpeed->setPosition(position + Vec2(-50, -50));
	Tool::setNodeSize(sp_AttackSpeed, 40, 40);
	root->addChild(sp_AttackSpeed);
	auto temp = CCString::createWithFormat("%.1f", object.attackSpeed);
	this->lbl_AttackSpeed = Tool::CreateLabel(temp->getCString(), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_AttackSpeed->setPosition(position + Vec2(-25, -50));
	lbl_AttackSpeed->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_AttackSpeed);

	this->sp_Range = Sprite::create("UI/CardScene/Icon/range.png");
	sp_Range->setPosition(position + Vec2(-50, -100));
	Tool::setNodeSize(sp_Range, 40, 40);
	root->addChild(sp_Range);
	this->lbl_Range = Tool::CreateLabel(to_string((int)object.range), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Range->setPosition(position + Vec2(-25, -100));
	lbl_Range->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Range);

	this->sp_Defense = Sprite::create("UI/CardScene/Icon/defense.png");
	sp_Defense->setPosition(position + Vec2(30, 0));
	Tool::setNodeSize(sp_Defense, 40, 40);
	root->addChild(sp_Defense);
	this->lbl_Defense = Tool::CreateLabel(to_string((int)object.defense), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Defense->setPosition(position + Vec2(55, 0));
	lbl_Defense->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Defense);

	this->sp_MoveSpeed = Sprite::create("UI/CardScene/Icon/moveSpeed.png");
	sp_MoveSpeed->setPosition(position + Vec2(30, -50));
	Tool::setNodeSize(sp_MoveSpeed, 40, 40);
	root->addChild(sp_MoveSpeed);
	this->lbl_MoveSpeed = Tool::CreateLabel(to_string((int)object.moveSpeed), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_MoveSpeed->setPosition(position + Vec2(55, -50));
	lbl_MoveSpeed->setAnchorPoint(Vec2(0, 0.5));
	lbl_MoveSpeed->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_MoveSpeed);

	this->sp_Regeneration = Sprite::create("UI/CardScene/Icon/regeneration.png");
	sp_Regeneration->setPosition(position + Vec2(30, -100));
	Tool::setNodeSize(sp_Regeneration, 40, 40);
	root->addChild(sp_Regeneration);
	this->lbl_Regeneration = Tool::CreateLabel(to_string((int)object.regeneration), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Regeneration->setPosition(position + Vec2(55, -100));
	lbl_Regeneration->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Regeneration);

	this->sp_Background = Sprite::create("UI/CardScene/UnitDetailsTable.png");
	Tool::setNodeSize(sp_Background, 200, 240);
	sp_Background->setPosition(position + Vec2(0,-24));
	root->addChild(sp_Background,-1);
}

FriendShipUpgrade::FriendShipUpgrade(string unitName, int currentLevel)
{
	this->root = Node::create();
	this->currentLevel = currentLevel;
	string info1, info2, info3, info4, info5;
	if (unitName == "Frost Wyvern") {
		info1 = "Level 1 : +40 Health";
		info2 = "Level 2 : +10 Defense";
		info3 = "Level 3 : +50 Range";
		info4 = "Level 4 : +50 Health";
		info5 = "Level 5 : +5 Attack Speed";
	}
	else if (unitName == "Polar Bear") {
		info1 = "Level 1 : +50 Health";
		info2 = "Level 2 : +4 Attack";
		info3 = "Level 3 : +25 Defense";
		info4 = "Level 4 : +6 Attack";
		info5 = "Level 5 : +70 Health";
	}
	else if (unitName == "Volcarona") {
		info1 = "Level 1: +5 Attack";
		info2 = "Level 2 : +25 Health";
		info3 = "Level 3 : +50 Range";
		info4 = "Level 4 : +5 Attack";
		info5 = "Level 5 : +5 Atack Speed";
	}
	else if (unitName == "Enraged Ursa") {
		info1 = "Level 1 : +25 Health";
		info2 = "Level 2 : +2 Attack Speed";
		info3 = "Level 3 : +10 Move Speed";
		info4 = "Level 4 : +4 Attack Speed";
		info5 = "Level 5 : +20 Defense";
	}
	else if (unitName == "Poisonous Butterfly") {
		info1 = "Level 1 : +2 Attack Speed";
		info2 = "Level 2 : +28 Health";
		info3 = "Level 3 : +3 Attack Speed";
		info4 = "Level 4 : +32 Health";
		info5 = "Level 5 : +5 Attack Speed";
	}
	else if (unitName == "Vampire Dragon") {
		info1 = "Level 1 : +5 Attack";
		info2 = "Level 2 : +2 Regeneration";
		info3 = "Level 3 : +8 Attack Speed";
		info4 = "Level 4 : +3 Regeneration";
		info5 = "Level 5 : +9 Attack";
	}
	else if (unitName == "Hotheaded Gunner") {
		info1 = "Level 1: +2 Attack";
		info2 = "Level 2 : +25 Health";
		info3 = "Level 3 : +3 Attack";
		info4 = "Level 4 : +35 Health";
		info5 = "Level 5 : +5 Attack";
	}
	else if (unitName == "UFO Driver") {
		info1 = "Level 1 : +50 Health";
		info2 = "Level 2 : +2 Attack";
		info3 = "Level 3 : +8 Defense";
		info4 = "Level 4 : +2 Attack Speed";
		info5 = "Level 5 : +3 Attack";
	}
	else if (unitName == "Winged Orc") {
		info1 = "Level 1 : +2 Attack Speed";
		info2 = "Level 2 : +40 Health";
		info3 = "Level 3 : +3 Attack Speed";
		info4 = "Level 4 : +40 Health";
		info5 = "Level 5 : +5 Attack Speed";
	}
	else if (unitName == "Helicopter") {
		info1 = "Level 1 : +28 Health";
		info2 = "Level 2 : +2 Attack Speed";
		info3 = "Level 3 : +42 Health";
		info4 = "Level 4 : +2 Attack Speed";
		info5 = "Level 5 : +10 Defense";
	}
	else if (unitName == "Crazy Wolf") {
		info1 = "Level 1 : +1 Regeneration";
		info2 = "Level 2 : +4 Attack";
		info3 = "Level 3 : +1 Regeneration";
		info4 = "Level 4 : +6 Attack";
		info5 = "Level 5 : +2 Regeneration";
	}
	else if (unitName == "Dead Walker") {
		info1 = "Level 1 : +40 Health";
		info2 = "Level 2 : +4 Defense";
		info3 = "Level 3 : +50 Health";
		info4 = "Level 4 : +6 Defense";
		info5 = "Level 5 : +60 Health";
	}
	else if (unitName == "Liquid Assassin") {
		info1 = "Level 1 : +6 Attack";
		info2 = "Level 2 : +30 Health";
		info3 = "Level 3 : +5 Defense";
		info4 = "Level 4 : +45 Health";
		info5 = "Level 5 : +9 Attack";
	}
	else if (unitName == "Elemental Alien") {
		info1 = "Level 1 : +5 Defense";
		info2 = "Level 2 : +25 Health";
		info3 = "Level 3 : +2 Attack Speed";
		info4 = "Level 4 : +35 Health";
		info5 = "Level 5 : +5 Attack Speed";
	}
	else return;

	lbl_Level1 = Tool::CreateLabel(info1,Tool::defaultTextSize,Color4B::GRAY);
	lbl_Level1->setAnchorPoint(Vec2(0, 0.5));
	if (currentLevel > 0) lbl_Level1->setTextColor(Color4B(175, 225, 250, 250));
	root->addChild(lbl_Level1);

	lbl_Level2 = Tool::CreateLabel(info2, Tool::defaultTextSize, Color4B::GRAY);
	lbl_Level2->setAnchorPoint(Vec2(0, 0.5));
	if (currentLevel > 1) lbl_Level2->setTextColor(Color4B(175, 225, 250, 250));
	lbl_Level2->setPosition(Vec2(0, -20));
	root->addChild(lbl_Level2);

	lbl_Level3 = Tool::CreateLabel(info3, Tool::defaultTextSize, Color4B::GRAY);
	lbl_Level3->setAnchorPoint(Vec2(0, 0.5));
	if (currentLevel > 2) lbl_Level3->setTextColor(Color4B(175, 225, 250, 250));
	lbl_Level3->setPosition(Vec2(0, -40));
	root->addChild(lbl_Level3);

	lbl_Level4 = Tool::CreateLabel(info4, Tool::defaultTextSize, Color4B::GRAY);
	lbl_Level4->setAnchorPoint(Vec2(0, 0.5));
	if (currentLevel > 3) lbl_Level4->setTextColor(Color4B(175, 225, 250, 250));
	lbl_Level4->setPosition(Vec2(0, -60));
	root->addChild(lbl_Level4);

	lbl_Level5 = Tool::CreateLabel(info5, Tool::defaultTextSize, Color4B::GRAY);
	lbl_Level5->setAnchorPoint(Vec2(0, 0.5));
	if (currentLevel > 4) lbl_Level5->setTextColor(Color4B(175, 225, 250, 250));
	lbl_Level5->setPosition(Vec2(0, -80));
	root->addChild(lbl_Level5);

	btn_Up = Tool::CreateButtonWithoutSprite(unitName, "Up", Tool::defaultTextSize*1.24, Color3B::GREEN);
	btn_Up->setPosition(Vec2(25, -120));
	root->addChild(btn_Up);

	btn_Down = Tool::CreateButtonWithoutSprite(unitName, "Down", Tool::defaultTextSize*1.24, Color3B::RED);
	btn_Down->setPosition(Vec2(150, -120));
	root->addChild(btn_Down);


}

void CardScene::RunActionNotify(string content)
{
	auto lbl_Notify = Tool::CreateLabel(content, Tool::defaultTextSize, Color4B::MAGENTA);
	lbl_Notify->setPosition(visibleSize / 2);
	this->addChild(lbl_Notify, 10);
	lbl_Notify->runAction(Sequence::create(FadeOut::create(0), FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(0.5), RemoveSelf::create(), nullptr));
}