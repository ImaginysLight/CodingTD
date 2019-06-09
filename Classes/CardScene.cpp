#include "CardScene.h"

USING_NS_CC;
cocos2d::Scene * CardScene::createScene()
{
	return CardScene::create();
}

bool CardScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	
	auto lbl_PlayerName = Tool::CreateLabel(Player::currentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_PlayerName->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.9));
	this->addChild(lbl_PlayerName);

	auto levelInfo = Player::CalculateLevel(Player::currentPlayer->experience);

	auto lbl_Level = Tool::CreateLabel("Level: " + to_string(levelInfo.first));
	lbl_Level->setPosition(Vec2(visibleSize.width*0.685, visibleSize.height*0.93));
	this->addChild(lbl_Level);

	auto expBar = Tool::CreateBar(200, 25, Color3B(175, 225, 200));
	expBar.first->setPosition(Vec2(visibleSize.width*0.58, visibleSize.height*0.85));
	expBar.first->setPercentage(Player::currentPlayer->experience / (float)levelInfo.second *100.0);
	expBar.second->setPosition(Vec2(visibleSize.width*0.58, visibleSize.height*0.85));
	this->addChild(expBar.first);
	this->addChild(expBar.second, -1);

	auto lbl_Exp = Tool::CreateLabel(to_string(Player::currentPlayer->experience) + " / " + to_string(levelInfo.second), Tool::defaultTextSize, Color4B::RED);
	lbl_Exp->setPosition(Vec2(visibleSize.width*0.685, visibleSize.height*0.87));
	this->addChild(lbl_Exp);

	lbl_Friendship = Tool::CreateLabel("Friendship: " + to_string(Player::currentPlayer->friendshipPoint));
	lbl_Friendship->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.9));
	this->addChild(lbl_Friendship);

	auto btn_PlayerScene = Tool::CreateButtonWithoutSprite("btn_PlayerScene", "<< Player Info", Tool::defaultTextSize*1.5);
	btn_PlayerScene->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(1, Vec2(-25, 0)),
		MoveBy::create(1, Vec2(25, 0)),
		nullptr)));
	btn_PlayerScene->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.9));
	btn_PlayerScene->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	this->addChild(btn_PlayerScene);

	processUpgradeNode = Node::create();
	processUpgradeNode->setPosition(visibleSize / 2);
	processUpgradeNode->setVisible(false);
	this->addChild(processUpgradeNode, 2);

	lbl_ConfirmUpgrade = Tool::CreateLabel("");
	lbl_ConfirmUpgrade->setPosition(Vec2(0, visibleSize.height*0.05));
	processUpgradeNode->addChild(lbl_ConfirmUpgrade);

	btn_Process = Tool::CreateButtonWithoutSprite("", "Process", Tool::defaultTextSize*1.2, Color3B::GREEN);
	btn_Process->setPosition(Vec2(visibleSize.width*-0.1, visibleSize.height*-0.05));
	processUpgradeNode->addChild(btn_Process);

	btn_Cancel = Tool::CreateButtonWithoutSprite("", "Cancel", Tool::defaultTextSize*1.2, Color3B::RED);
	btn_Cancel->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*-0.05));
	btn_Cancel->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	processUpgradeNode->addChild(btn_Cancel);

	lbl_Notify = Tool::CreateLabel("", Tool::defaultTextSize, Color4B::MAGENTA);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize / 2));
	this->addChild(lbl_Notify, 10);

	friendshipNode = Node::create();
	friendshipNode->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.3));
	this->addChild(friendshipNode);

	detailNode_Before = Node::create();
	detailNode_Before->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height*0.55));
	this->addChild(detailNode_Before);

	detailNode_After = Node::create();
	detailNode_After->setPosition(Vec2(visibleSize.width *0.7, visibleSize.height*0.55));
	this->addChild(detailNode_After);

	spriteNode = Node::create();
	spriteNode->setPosition(Vec2(visibleSize.width*0.22, visibleSize.height*0.8));
	this->addChild(spriteNode);

	skillNode = Node::create();
	skillNode->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.4));
	this->addChild(skillNode);

	scroll_Navigator = ui::ScrollView::create();
	scroll_Navigator->setContentSize(Size(200, 400));
	scroll_Navigator->setInnerContainerSize(Size(200, 1000));
	scroll_Navigator->setPosition(Vec2(visibleSize.width, visibleSize.height*0.8));
	scroll_Navigator->setAnchorPoint(Vec2(1, 1));
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

	for (int i = 0; i < cardName.size(); i++) {
		Button* btn = Tool::CreateButtonWithoutSprite(cardName[i], cardName[i], Tool::defaultTextSize, Color3B::GRAY);
		btn->setAnchorPoint(Vec2(0, 0.5));
		btn->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Navigator_Click, this));
		btn->setPosition(Vec2(10, 950 - 50 * i));
		scroll_Navigator->addChild(btn);
		vec_Card.insert({ cardName[i],btn });
	}
	vec_Card["Hotheaded Gunner"]->setTitleColor(Color3B(175, 225, 200));
	CardScene::RefreshScene("Hotheaded Gunner");

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
			lbl_Friendship->setString("Friendship: " + to_string(Player::currentPlayer->friendshipPoint));
			Player::currentPlayer->friendshipLevel[name] ++;
			RefreshScene(name);
			RunActionNotify("Upgrade successful!");
		}
		processUpgradeNode->setVisible(false);
	}
}

void CardScene::btn_DownFriendship_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		Player::currentPlayer->friendshipLevel[name] --;
		RefreshScene(name);
		processUpgradeNode->setVisible(false);
		RunActionNotify("Downgrade successful!");
	}
}

void CardScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		if (((Node*)pSender)->getName() == "btn_PlayerScene"){
			Director::getInstance()->replaceScene(PlayerInformationScene::createScene());
			return;
		}	
		auto btn = (Button*)pSender;
		if (btn->getTitleText() == "Up") {
			if (Player::currentPlayer->friendshipLevel[btn->getName()] == 5)
				RunActionNotify(btn->getName() + "'s Friendship already at maximum level!");
			else {
				btn_Process->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_UpFriendship_Click, this));
				btn_Process->setName(btn->getName());
				lbl_ConfirmUpgrade->setString("Upgrade 1 Friendship level for " + btn->getName());
				processUpgradeNode->setVisible(true);
			}
		}
		else if (btn->getTitleText() == "Down") {
			if (Player::currentPlayer->friendshipLevel[btn->getName()] == 0)
				RunActionNotify(btn->getName() + "'s Friendship already at minimum level!");
			else {
				btn_Process->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_DownFriendship_Click, this));
				btn_Process->setName(btn->getName());
				lbl_ConfirmUpgrade->setString("Downgrade 1 Friendship level for " + btn->getName());
				processUpgradeNode->setVisible(true);
			}
		}
		else if (btn->getTitleText() == "Cancel")
			processUpgradeNode->setVisible(false);
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
		RefreshScene(name);
	}
}

vector<string> CardScene::GetSkillDetail(string unitName)
{
	vector<string> result;
	if (unitName == "Frost Wyvern") {
		result.push_back("The Presence of Ice: Slow all enemies on the line, decrease Move Speed by 10 / 15 / 20 and Attack Speed by 10 / 17 / 25 %");
		result.push_back("Frost Nova: Launch a snowball toward enemy, dealing 60 / 75 / 100 splash damage in 150 range, pierce 25 / 35 / 50 Defense (Cooldown 7 / 6 / 4 seconds)");
	}
	else if (unitName == "Polar Bear") {
		result.push_back("Ice Punch: Each 3th attack will knock the target into the air, dealing 100 / 200 / 300 bonus damage and stun them for 1 / 2 / 3 seconds.");
		result.push_back("Icy Body: Whoever attacked this bear will tremble, decrease 12 / 16 / 20% Attack. (Trigger after first hit, last 5 seconds)");
	}
	else if (unitName == "Volcarona") {
		result.push_back("The Presence of Fire: burn all enemies on the line, dealing 5 / 7 pure dps and decrease Regeneration by 30 / 35%.");
		result.push_back("Fire Armor: buff an ally with Fire Armor, increase Defense by 25 / 30 and reflect 25 / 30% damage to whoever attacks them. (Duration: 9s, Cooldown: 10s)");
	}
	else if (unitName == "Enraged Ursa") {
		result.push_back("Demon Heart: increase 1 / 1.5% Attack per 1% Health lose.");
		result.push_back("Lucifer's Indignation: become angry when Health below 75%, improve normal attacks, causing splash damage equal to 35% Attack within 400 range around its target.");
	}
	else if (unitName == "Poisonous Butterfly") {
		result.push_back("The Presence of Life: bless all allies on the line, increase Regeneration by 3 / 5 and Attack Speed by 15 / 25%");
		result.push_back("Agent Orange: improve normal attacks with Agent Orange, dealing bonus damage equal to 2 / 3% the target's Max Health, and decrease target's Defense percent equal to bonus damage.");
	}
	else if (unitName == "Vampire Dragon") {
		result.push_back("Vampire Touch: Improve normal attacks, restores Current Health by 20 / 35% of damage dealt, and steal 0.3 / 0.5% target's Max Health.");
		result.push_back(" Blessings From Demeter: On death, it will respawn with power proportional to amount of Health stolen, this ability only trigger one time. ");
	}
	else if (unitName == "Hotheaded Gunner") {
		result.push_back("Steel Skin: reduce damage received by 10% Defense, calculate after Defense. (means -7.5 / -11 / -15 Health lose under normal circumstances)");
	}
	else if (unitName == "UFO Driver") {
		result.push_back("Wrong Button: each 5 / 4 / 4 / 3th attack, the driver presses the wrong button, causing the next attack to increase damage by 2 / 2.4 / 2.8 / 3, but the UFO runs of energy in 3.5 / 2.5 / 2 / 2 second.");
	}
	else if (unitName == "Winged Orc") {
		result.push_back("Deathwing: blows away everything on attack, knockback both itself and the enemy by 25 / 50 / 100 range if the target is a unit, bonus 75 damage if the target is a building.");
	}
	else if (unitName == "Helicopter") {
		result.push_back("Keen Eyes: attack upto 2 / 3 targets in all lines.");
	}
	else if (unitName == "Crazy Wolf") {
		result.push_back("Berserker's Blood:\nDouble amount of Regeneration when Health below 35 / 55 / 75 %.\nTripple amount of Regeneration when Health below 0 / 20 / 50 %.\nQuadruplicate amount of Regeneration when Health below 0 / 10 / 25 %.");
	}
	else if (unitName == "Dead Walker") {
		result.push_back("Rotten Aura: Decrease enemies Attack and Defense by 5 / 7.5 / 10% in 500 range around in all line. (last 5 seconds)");
	}
	else if (unitName == "Liquid Assassin") {
		result.push_back("Death Scratch: blink toward an enemy on any line and scratch, dealt 100 / 175 / 250 bonus damage on attack. This ability has 1 charge and will be restored when an enemy dies within 550 / 650 / 750 range around Assassin, cooldown 5 seconds.");
	}
	else if (unitName == "Elemental Alien") {
		result.push_back("Has 1 of these skill depend on element.\nIcy Claws: dealt bonus damage as 13 / 20 / 27 / 35% target's Attack on attack.\nFiery Claws: dealt bonus damage as 3 / 3.8 / 4.5 / 5* target's base Regeneration and make them unhealable for 1 / 2 / 3 / 4 seconds on attack.\nVitality Claws: lifesteal 4 / 4.8 / 5.5 / 6% target's Max Health multiply (90 / 100 / 110 / 120 / Move Speed) on attack.");
	}

	return result;
}

void CardScene::RefreshScene(string unitName)
{
	CardScene::friendshipNode->removeAllChildrenWithCleanup(true);
	auto friendship = FriendShipUpgrade(unitName, Player::currentPlayer->friendshipLevel[unitName]);
	friendship.btn_Up->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	friendship.btn_Down->addTouchEventListener(CC_CALLBACK_2(CardScene::btn_Click, this));
	friendshipNode->addChild(friendship.root);

	CardScene::detailNode_Before->removeAllChildrenWithCleanup(true);
	int currentFriendship = Player::currentPlayer->friendshipLevel[unitName];
	Player::currentPlayer->friendshipLevel[unitName] = 0;
	auto detailBefore = UnitDetailsTable(*ObjectConstructor::InitializeObject(unitName, 0, 1, 0, -1), Vec2(0,0));
	detailNode_Before->addChild(detailBefore.root);
	Label* lbl_Before = Tool::CreateLabel("Before",Tool::defaultTextSize*1.2,Color4B::RED);
	lbl_Before->setPosition(Vec2(0, visibleSize.height*0.25));
	detailNode_Before->addChild(lbl_Before);

	CardScene::detailNode_After->removeAllChildrenWithCleanup(true);
	Player::currentPlayer->friendshipLevel[unitName] = currentFriendship;
	auto detailAfter = UnitDetailsTable(*ObjectConstructor::InitializeObject(unitName, 0, 1, 0, -1), Vec2(0,0));
	detailNode_After->addChild(detailAfter.root);
	Label* lbl_After = Tool::CreateLabel("After", Tool::defaultTextSize*1.2, Color4B::GREEN);
	lbl_After->setPosition(Vec2(0, visibleSize.height*0.25));
	detailNode_After->addChild(lbl_After);

	CardScene::spriteNode->removeAllChildrenWithCleanup(true);
	auto sp = Sprite::create("Sprites/" + unitName + "/card.png");
	sp->setPosition(Vec2(0, visibleSize.height*-0.2));
	Tool::setNodeSize(sp, sp->getBoundingBox().size.width*1.3, sp->getBoundingBox().size.height*1.3);
	spriteNode->addChild(sp);
	auto lbl_Name = Tool::CreateLabel(unitName, Tool::defaultTextSize*1.5, Color4B(175, 255, 250, 255));
	spriteNode->addChild(lbl_Name);

	CardScene::skillNode->removeAllChildrenWithCleanup(true);
	Label* lbl_Skill = Tool::CreateLabel("",Tool::defaultTextSize*0.9);
	lbl_Skill->setAnchorPoint(Vec2(0, 1));
	lbl_Skill->setMaxLineWidth(325);
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
	lbl_Name->setPosition(position + Vec2(0,84));
	root->addChild(lbl_Name);

	this->lbl_Health = Tool::CreateLabel(to_string((int)object.currentHealth), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Health->setPosition(position + Vec2(30, 42));
	lbl_Health->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Health);

	this->lbl_Defense = Tool::CreateLabel(to_string((int)object.defense), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Defense->setPosition(position + Vec2(30, 6));
	lbl_Defense->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Defense);

	this->lbl_Regeneration = Tool::CreateLabel(to_string((int)object.regeneration), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Regeneration->setPosition(position + Vec2(30, -30));
	lbl_Regeneration->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Regeneration);

	this->lbl_Attack = Tool::CreateLabel(to_string((int)object.attack), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Attack->setPosition(position + Vec2(-34, 42));
	lbl_Attack->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Attack);

	auto temp = CCString::createWithFormat("%.1f", object.attackSpeed);
	this->lbl_AttackSpeed = Tool::CreateLabel(temp->getCString(), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_AttackSpeed->setPosition(position + Vec2(-34, 6));
	lbl_AttackSpeed->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_AttackSpeed);

	this->lbl_MoveSpeed = Tool::CreateLabel(to_string((int)object.moveSpeed), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_MoveSpeed->setPosition(position + Vec2(-34, -30));
	lbl_MoveSpeed->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_MoveSpeed);

	this->lbl_Range = Tool::CreateLabel(to_string((int)object.range), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Range->setPosition(position + Vec2(-34, -66));
	lbl_Range->setAnchorPoint(Vec2(0, 0.5));
	root->addChild(lbl_Range);

	this->sp_Background = Sprite::create("UI/CardScene/UnitDetailsTable.png");
	sp_Background->setPosition(position);
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
	btn_Up->setPosition(Vec2(50, -120));
	root->addChild(btn_Up);

	btn_Down = Tool::CreateButtonWithoutSprite(unitName, "Down", Tool::defaultTextSize*1.24, Color3B::RED);
	btn_Down->setPosition(Vec2(150, -120));
	root->addChild(btn_Down);


}

void CardScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(0.5), nullptr));
}
