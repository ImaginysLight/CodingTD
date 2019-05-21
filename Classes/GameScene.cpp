#include"GameScene.h"
USING_NS_CC;

vector<string> GameScene::playerPickedUnit;

/*
this
	defaultCamera
	staticUI
		buyingBar
		questionTable
		unitDetails
*/
Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	Tool::opponentPlayer->id = 8;
	Tool::opponentPlayer->elementName = "Fire";

	Tool::currentPlayer->username = "ImaginysLight";
	Tool::currentPlayer->id = 5;
	Tool::currentPlayer->elementName = "Nature";

	IngameObject::loadIngameObjectStaticVariables();

	BaseSkillClass::LoadSkillRequirement();

	GameScene::SetupCamera();

	GameScene::SetupGUI();

	GameScene::LoadIngamePlayerInfo();

	IngameObject::loadAnimate();

	

	{
		GameScene::InitializeIngameObject("Enraged Ursa 2", 3, 5);
		GameScene::InitializeIngameObject("Vampire Dragon 2", 3, 5);
		GameScene::InitializeIngameObject("Frost Wyvern 3", 3, 8);
		GameScene::InitializeIngameObject("Polar Bear 3", 3, 8);
	}





	this->schedule(schedule_selector(GameScene::UpdateIngameObject), 1/60);
	this->schedule(schedule_selector(GameScene::UpdateQuestionInfo), 0.25);
	this->schedule(schedule_selector(GameScene::UpdatePlayerResource), 1);
	this->scheduleUpdate();
	return true;
}

void GameScene::LoadIngamePlayerInfo() {
	//Add mấy cái đã pick vào đã
	playerPickedUnit.push_back("Blessed Kingdom");
	playerPickedUnit.push_back("Hotheaded Gunner");
	playerPickedUnit.push_back("Crazy Wolf");
	playerPickedUnit.push_back("Dead Walker");
	playerPickedUnit.push_back("Helicopter");
	playerPickedUnit.push_back("Frost Wyvern");
	playerPickedUnit.push_back("Poisonous Butterfly");

	//Set label các loại bên góc trái trên
	ingamePlayerInfo.sp_Background = Sprite::create("UI/GameScene/Ingame Player Info.png");
	ingamePlayerInfo.sp_Background->setAnchorPoint(Vec2(0, 1));
	ingamePlayerInfo.sp_Background->setPositionY(visibleSize.height);
	staticUI->addChild(ingamePlayerInfo.sp_Background, -1);

	ingamePlayerInfo.lbl_PlayerName = Tool::CreateLabel(Tool::currentPlayer->username,Tool::defaultTextSize*0.75);
	ingamePlayerInfo.lbl_PlayerName->enableBold();
	ingamePlayerInfo.lbl_PlayerName->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_PlayerName->setPosition(Vec2(122, 122));
	ingamePlayerInfo.sp_Background->addChild(ingamePlayerInfo.lbl_PlayerName, 1);

	ingamePlayerInfo.lbl_KingdomLevel = Tool::CreateLabel(to_string(ingamePlayerInfo.kingdomLevel), Tool::defaultTextSize, Color4B::GREEN, CCTextAlignment::LEFT);
	ingamePlayerInfo.lbl_KingdomLevel->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_KingdomLevel->setPosition(Vec2(62, 103));
	ingamePlayerInfo.sp_Background->addChild(ingamePlayerInfo.lbl_KingdomLevel,1);

	ingamePlayerInfo.lbl_Gold = Tool::CreateLabel(to_string(ingamePlayerInfo.gold), Tool::defaultTextSize, Color4B::YELLOW, CCTextAlignment::LEFT);
	ingamePlayerInfo.lbl_Gold->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Gold->setPosition(Vec2(62, 82));
	ingamePlayerInfo.sp_Background->addChild(ingamePlayerInfo.lbl_Gold);

	ingamePlayerInfo.lbl_Energy = Tool::CreateLabel(to_string(ingamePlayerInfo.energy), Tool::defaultTextSize, Color4B(Color3B(175, 225, 250), 255), CCTextAlignment::LEFT);
	ingamePlayerInfo.lbl_Energy->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Energy->setPosition(Vec2(62, 58));
	ingamePlayerInfo.sp_Background->addChild(ingamePlayerInfo.lbl_Energy);

	ingamePlayerInfo.lbl_Knowledge = Tool::CreateLabel(to_string(ingamePlayerInfo.knowledge), Tool::defaultTextSize, Color4B(Color3B(175, 225, 200), 255), CCTextAlignment::LEFT);
	ingamePlayerInfo.lbl_Knowledge->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Knowledge->setPosition(Vec2(62, 33));
	ingamePlayerInfo.sp_Background->addChild(ingamePlayerInfo.lbl_Knowledge);
	
	ingamePlayerInfo.btn_UpgradeKingdom = Tool::CreateButtonWithoutSprite(GameScene::playerPickedUnit[0], Tool::ConvertUTF16ToString(L"Up ↑"),Tool::defaultTextSize*1.5);
	ingamePlayerInfo.btn_UpgradeKingdom->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.btn_UpgradeKingdom->setPosition(Vec2(140, 65));
	ingamePlayerInfo.btn_UpgradeKingdom->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_UpgradeKingdom, this));
	ingamePlayerInfo.sp_Background->addChild(ingamePlayerInfo.btn_UpgradeKingdom);

	//Tạo 2 skill
	if (Tool::currentPlayer->elementName == "Ice") {
		ingamePlayerInfo.btn_Skill1 = Tool::CreateButtonWithoutSprite("Cool Blooded", "Cool Blooded", Tool::defaultTextSize*1.25, Color3B(0, 255, 255));
		ingamePlayerInfo.btn_Skill2 = Tool::CreateButtonWithoutSprite("Ice Age", "Ice Age", Tool::defaultTextSize*1.25, Color3B(0, 255, 255));
	}
	else if (Tool::currentPlayer->elementName == "Fire") {
		ingamePlayerInfo.btn_Skill1 = Tool::CreateButtonWithoutSprite("Burning Enthusiasm", "Burning Enthusiasm", Tool::defaultTextSize*1.25, Color3B::RED);
		ingamePlayerInfo.btn_Skill2 = Tool::CreateButtonWithoutSprite("Hell Fire", "Hell Fire", Tool::defaultTextSize*1.25, Color3B::RED);
	}
	else if (Tool::currentPlayer->elementName == "Nature") {
		ingamePlayerInfo.btn_Skill1 = Tool::CreateButtonWithoutSprite("Proliferate", "Proliferate", Tool::defaultTextSize*1.25, Color3B::GREEN);
		ingamePlayerInfo.btn_Skill2 = Tool::CreateButtonWithoutSprite("Heaven Bless", "Heaven Bless", Tool::defaultTextSize*1.25, Color3B::GREEN);
	}
	ingamePlayerInfo.btn_Skill1->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.7));
	ingamePlayerInfo.btn_Skill1->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.btn_Skill1->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_ExecuteSkill_Click, this));
	staticUI->addChild(ingamePlayerInfo.btn_Skill1);

	ingamePlayerInfo.btn_Skill2->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.65));
	ingamePlayerInfo.btn_Skill2->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.btn_Skill2->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_ExecuteSkill_Click, this));
	staticUI->addChild(ingamePlayerInfo.btn_Skill2);

	//Tạo Kingdom
	GameScene::InitializeIngameObject(playerPickedUnit[0], 1, Tool::currentPlayer->id);
	for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
		if (unit->name == playerPickedUnit[0]) {
			ingamePlayerInfo.kingdom = unit;
			break;
		}
	}
	for (int i = 1; i < GameScene::playerPickedUnit.size(); i++) {
		List_BuyableUnit.push_back(Item_BuyableUnit(GameScene::playerPickedUnit[i]));
	}

	//Tạo thanh mua lính
	GameScene::CreateBuyingBar();
	
}

void GameScene::update(float time) {
	Tool::currentIngameTime += time;
}

void GameScene::UpdateIngameObject(float time) {
	//Update thông tin unit đang chọn
	if (choosingUnit->currentHealth > 0)
		GameScene::ShowUnitDetails();
	else
		GameScene::unitDetails->removeAllChildrenWithCleanup(true);

	//Update Unit
	for (int i = 0; i < BaseUnitClass::AllIngameUnit_Vector.size(); i++) {
		if (!BaseUnitClass::AllIngameUnit_Vector[i]->isAlive) {
			BaseUnitClass::AllIngameUnit_Vector.erase(BaseUnitClass::AllIngameUnit_Vector.begin() + i);
			continue;
		}
		BaseUnitClass::AllIngameUnit_Vector[i]->Update();
	}

	//Update Skill
	for (int i = 0; i < BaseSkillClass::AllIngameSkill_Vector.size(); i++) {
		if (BaseSkillClass::AllIngameSkill_Vector[i]->isReleased) {
			BaseSkillClass::AllIngameSkill_Vector.erase(BaseSkillClass::AllIngameSkill_Vector.begin() + i);
			continue;
		}
		if (!BaseSkillClass::AllIngameSkill_Vector[i]->isAddedChild) {
			this->addChild(BaseSkillClass::AllIngameSkill_Vector[i]->root, 5);
			BaseSkillClass::AllIngameSkill_Vector[i]->isAddedChild = true;
		}
		BaseSkillClass::AllIngameSkill_Vector[i]->Update();
	}
}

void GameScene::UpdatePlayerResource(float time) {
	ingamePlayerInfo.gold += 5;
	if(ingamePlayerInfo.energy < ingamePlayerInfo.energyCap) ingamePlayerInfo.energy += 1;
	UpdateIngamePlayerInfo();
}

void GameScene::UpdateQuestionInfo(float time) {
	if (destinationTime < Tool::currentIngameTime){
		questionAvailable = !questionAvailable;
		GameScene::ChangeQuestionTableState(questionAvailable);
		if (questionAvailable) {
			//Nếu có câu hỏi thì kiểm tra xem questionContent == "", tức là chưa chọn độ khó
			if (questionContent == ""); //random câu hỏi độ khó mặc định
			destinationTime += currentQuestionLevel * 10;
			GameScene::Request_RandomQuestion(nextQuestionLevel);
			GameScene::Request_ReadQuestion();
		}
		else destinationTime += 10;
	}
	if (questionAvailable) {
		btn_DropDownQuestionTable->setTitleText("Question Ready (" + to_string((int)(destinationTime - Tool::currentIngameTime)) + ")");
	}
	else {
		btn_DropDownQuestionTable->setTitleText("Waiting For Next Question (" + to_string((int)(destinationTime - Tool::currentIngameTime)) + ")");
	}
}

void GameScene::ChangeQuestionTableState(bool questionAvailable) {
	if (questionAvailable) {
		btn_Answer1->setTitleColor(Color3B::WHITE);
		btn_Answer2->setTitleColor(Color3B::WHITE);
		btn_Answer3->setTitleColor(Color3B::WHITE);
		btn_Answer4->setTitleColor(Color3B::WHITE);

		btn_Answer1->setEnabled(true);
		btn_Answer2->setEnabled(true);
		btn_Answer3->setEnabled(true);
		btn_Answer4->setEnabled(true);

		btn_Answer1->runAction(FadeIn::create(0.5));
		btn_Answer2->runAction(FadeIn::create(0.5));
		btn_Answer3->runAction(FadeIn::create(0.5));
		btn_Answer4->runAction(FadeIn::create(0.5));
		
		btn_Level1->runAction(FadeOut::create(0.5));
		btn_Level2->runAction(FadeOut::create(0.5));
		btn_Level3->runAction(FadeOut::create(0.5));

		btn_Level1->setEnabled(false);
		btn_Level2->setEnabled(false);
		btn_Level3->setEnabled(false);

		btn_Level1->setLocalZOrder(0);
		btn_Level2->setLocalZOrder(0);
		btn_Level3->setLocalZOrder(0);
	}

	else {
		nextQuestionLevel = "";
		lbl_Level->setString(Tool::ConvertUTF16ToString(L"Đoán xem?"));
		if (isAllowedToChooseQuestion) {
			btn_Level1->setTitleColor(Color3B::WHITE);
			btn_Level2->setTitleColor(Color3B::WHITE);
			btn_Level3->setTitleColor(Color3B::WHITE);

			btn_Level1->setEnabled(true);
			btn_Level2->setEnabled(true);
			btn_Level3->setEnabled(true);

			btn_Level1->runAction(FadeIn::create(0.5));
			btn_Level2->runAction(FadeIn::create(0.5));
			btn_Level3->runAction(FadeIn::create(0.5));

			btn_Level1->setLocalZOrder(2);
			btn_Level2->setLocalZOrder(2);
			btn_Level3->setLocalZOrder(2);
			txt_Question->setString("Choose difficulty for the next question or it will be random");
		}
		else
			txt_Question->setString("Wait your opponent choose difficulty for the next question");
		lv_QuestionContent->requestDoLayout();
		btn_Answer1->setEnabled(false);
		btn_Answer2->setEnabled(false);
		btn_Answer3->setEnabled(false);
		btn_Answer4->setEnabled(false);

		btn_Answer1->runAction(FadeOut::create(0.5));
		btn_Answer2->runAction(FadeOut::create(0.5));
		btn_Answer3->runAction(FadeOut::create(0.5));
		btn_Answer4->runAction(FadeOut::create(0.5));
		
	}
}

void GameScene::InitializeIngameObject(string objectName, int line, int playerId)
{
	bool isOwned = playerId == Tool::currentPlayer->id ? true : false;
	BaseUnitClass* object = ObjectConstructor::InitializeObject(objectName, line, isOwned, playerId);
	BaseUnitClass::AllIngameUnit_Vector.push_back(object);
	this->addChild(object->root, 4 - object->line);
	if (BaseUnitClass::AllIngameUnit_Vector.size() % 2)
		BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->setPositionY(
			BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->getPositionY()
			+ Tool::CreateRandomNumber(0, 25));
	else 
		BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->setPositionY(
			BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->getPositionY()
			+ Tool::CreateRandomNumber(25, 50));
}



void GameScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	string name = ((Node*)pSender)->getName();
	if (type == Widget::TouchEventType::ENDED) {

		if (name == "btn_DropDownQuestionTable") {
			questionTable->setVisible(true);
			if (questionTable->getPositionY() > visibleSize.height) 
				questionTable->runAction(MoveBy::create(0.5, Vec2(0, -visibleSize.height)));
			else questionTable->runAction(MoveBy::create(0.5, Vec2(0, visibleSize.height)));
		}

		else if (name == "btn_Level1" || name == "btn_Level2" || name == "btn_Level3") {
			if (isAllowedToChooseQuestion) {
				nextQuestionLevel = name.substr(name.size() - 1, 1);
				btn_Level1->setEnabled(false);
				btn_Level2->setEnabled(false);
				btn_Level3->setEnabled(false);

				((Button*)pSender)->setTitleColor(Color3B::GREEN);
				destinationTime = Tool::currentIngameTime;
			}
		}
		else if (name == "btn_Mode") {
			if (btn_Mode->getTitleText() == "Buy") btn_Mode->setTitleText("Upgrade");
			else if (btn_Mode->getTitleText() == "Upgrade")btn_Mode->setTitleText("View");
			else if (btn_Mode->getTitleText() == "View")btn_Mode->setTitleText("Buy");
		}
		else if (name == "btn_CloseViewDetail") {
			GameScene::sc_ViewDetail->runAction(RemoveSelf::create());
			Tool::Button_ChangeState(btn_CloseViewDetail, false, 0);
		}
	}
}

void GameScene::btn_ExecuteSkill_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		auto btn = (Button*)pSender;
		if (GameScene::CheckSkillCondition(name)) {
			if (name == "Cool Blooded") {
				SkillConstructor::InitializeSkill(name, 0, 0, 0, GameScene::choosingUnit);
			}
			else if (name == "Ice Age") {
				SkillConstructor::InitializeSkill(name, 0, 0, Tool::currentPlayer->id, nullptr);
			}
			else if (name == "Burning Enthusiasm") {
				SkillConstructor::InitializeSkill(name, 0, 0, 0, GameScene::choosingUnit);
			}
			else if (name == "Hell Fire") {
				SkillConstructor::InitializeSkill(name, 0, 0, Tool::currentPlayer->id, nullptr);
			}
			else if (name == "Proliferate") {
				GameScene::choosingUnit->currentHealth = GameScene::choosingUnit->maxHealth;
				GameScene::InitializeIngameObject(GameScene::choosingUnit->name, GameScene::choosingUnit->line, GameScene::choosingUnit->ownerPlayerId);
				BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->setPositionX(GameScene::choosingUnit->root->getPositionX() + 20);
			}
			else if (name == "Heaven Bless") {
				SkillConstructor::InitializeSkill(name, 0, 0, Tool::currentPlayer->id, nullptr);
			}
		}
	}
}
bool GameScene::CheckSkillCondition(string name) {
	if (ingamePlayerInfo.energy < BaseSkillClass::SkillRequirement[name].energy) {
		RunActionNotify("Not enough energy!");
		return false;
	}
	if (ingamePlayerInfo.kingdomLevel < BaseSkillClass::SkillRequirement[name].level) {
		RunActionNotify("Required Kingdom level " + to_string(BaseSkillClass::SkillRequirement[name].level));
		return false;
	}
	if (BaseSkillClass::SkillRequirement[name].needToSelect) {
		if(GameScene::choosingUnit == nullptr || GameScene::choosingUnit->currentHealth < 1
		|| !GameScene::choosingUnit->isAlive || GameScene::choosingUnit->action == "Die") {
			RunActionNotify("Please select an available unit");
			return false;
		}
		if (GameScene::choosingUnit->description == "Kingdom") {
			RunActionNotify("Kingdom does not affect by this skill");
			return false;
		}
		if (GameScene::choosingUnit->ownerPlayerId != Tool::currentPlayer->id) {
			RunActionNotify("You can't cast this skill to enemy");
			return false;
		}
		for (auto status : GameScene::choosingUnit->statusReceive) {
			if (status.statusName.find(name) != std::string::npos) {
				RunActionNotify("This unit already has this effect");
				return false;
			}
		}
	}

	ingamePlayerInfo.energy -= BaseSkillClass::SkillRequirement[name].energy;
	GameScene::UpdateIngamePlayerInfo();
	return true;
}
void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}


bool GameScene::onTouchBegan(Touch* touch, Event* event) {
	Camera::getDefaultCamera()->setAnchorPoint(Vec2(0, 0.5));
	for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
		auto x = unit->sprite->getBoundingBox();
		x.origin += x.size / 4;
		x.size = Size(x.size.width / 2, x.size.height / 2);
		if (x.containsPoint(staticUI->getPosition() + touch->getLocation() - unit->root->getPosition() + Vec2(unit->sprite->getBoundingBox().size.width*unit->isOwned,0))) {
			GameScene::choosingUnit = unit;
			return true;
		}
	}
	return true;
}
void GameScene::onTouchMoved(Touch* touch, Event* event) {
	Vec2 prePosition = Camera::getDefaultCamera()->getPosition();
	Camera::getDefaultCamera()->setPositionX(Camera::getDefaultCamera()->getPositionX() +
		(touch->getLocation().x - touch->getPreviousLocation().x));
	if (Camera::getDefaultCamera()->getPositionX() < -20) Camera::getDefaultCamera()->setPositionX(-20);
	if (Camera::getDefaultCamera()->getPositionX() > 3020) Camera::getDefaultCamera()->setPositionX(3020);
	staticUI->setPosition(staticUI->getPosition() + Camera::getDefaultCamera()->getPosition() - prePosition);
}

void GameScene::onTouchEnded(Touch* touch, Event* event) {
	
}

void GameScene::SetupCamera() {
	auto cameraSprite = Sprite::create();
	this->addChild(cameraSprite);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = (CC_CALLBACK_2(GameScene::onTouchBegan, this));
	touchListener->onTouchMoved = (CC_CALLBACK_2(GameScene::onTouchMoved, this));
	touchListener->onTouchEnded = (CC_CALLBACK_2(GameScene::onTouchEnded, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, cameraSprite);
}

void GameScene::SetupGUI() {
	staticUI = Node::create();
	this->addChild(staticUI,5);

	unitDetails = Node::create();
	staticUI->addChild(unitDetails);

	auto background = Sprite::create("UI/GameScene/background (3).png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(-500, 0));
	this->addChild(background, -1);

	lbl_Notify =Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize/2));
	staticUI->addChild(lbl_Notify);

	btn_DropDownQuestionTable = Button::create();
	btn_DropDownQuestionTable->setTitleText("Waiting For Next Question (" + to_string((int)(destinationTime-Tool::currentIngameTime)) + ")");
	btn_DropDownQuestionTable->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.95));
	btn_DropDownQuestionTable->setTitleFontSize(Tool::defaultTextSize);
	btn_DropDownQuestionTable->setName("btn_DropDownQuestionTable");
	btn_DropDownQuestionTable->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	staticUI->addChild(btn_DropDownQuestionTable);
	
	GameScene::CreateChatbox();
	GameScene::CreateQuestionTable();
}

void GameScene::CreateBuyingBar() {
	buyingBar = Node::create();
	staticUI->addChild(buyingBar,1);

	GameScene::btn_Mode = Tool::CreateButtonWithoutSprite("btn_Mode", "Buy");
	btn_Mode->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.25));
	btn_Mode->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_Mode);

	GameScene::btn_CloseViewDetail = Tool::CreateButtonWithoutSprite("btn_CloseViewDetail", "Close", Tool::defaultTextSize, Color3B::RED);
	btn_CloseViewDetail->setPosition(visibleSize*0.85);
	Tool::Button_ChangeState(btn_CloseViewDetail, false, 0);
	btn_CloseViewDetail->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	staticUI->addChild(btn_CloseViewDetail,1);

	this->buyingBar->addChild(ghostItem);
	for (int i = 0; i < List_BuyableUnit.size(); i++) {
		this->buyingBar->addChild(List_BuyableUnit[i].root);
		List_BuyableUnit[i].root->setPosition(Vec2(visibleSize.width*(0.05 + 0.12*i), visibleSize.height*0.05));
		List_BuyableUnit[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyUnit_Click, this));
		AddDragAndDropItem(List_BuyableUnit[i].root);
	}	
}

void GameScene::AddDragAndDropItem(Node*& root) {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = (CC_CALLBACK_2(GameScene::onTouchBegan, this));
	touchListener->onTouchMoved = (CC_CALLBACK_2(GameScene::onCardMoved, this));
	touchListener->onTouchEnded = (CC_CALLBACK_2(GameScene::onTouchEnded, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, root);
	
	ghostItem->runAction(RemoveSelf::create());
	ghostItem = Node::create();
	this->buyingBar->addChild(ghostItem);
	auto touchListener2 = EventListenerTouchOneByOne::create();
	touchListener2->onTouchBegan = (CC_CALLBACK_2(GameScene::onTouchBegan, this));
	touchListener2->onTouchMoved = (CC_CALLBACK_2(GameScene::onCardMoved, this));
	touchListener2->onTouchEnded = (CC_CALLBACK_2(GameScene::onTouchEnded, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener2, ghostItem);
	
}

void GameScene::onCardMoved(Touch* touch, Event* event) {
	if (GameScene::choosingBuyableUnit != nullptr &&  GameScene::btn_Mode->getTitleText() == "Buy") {
		choosingBuyableUnit->root->setPosition(Vec2(touch->getLocation()));
	}
}

void GameScene::btn_BuyUnit_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::BEGAN) {
		for (int i = 0; i < List_BuyableUnit.size(); i++) {
			if (List_BuyableUnit[i].btn_Icon->getName() == ((Button*)pSender)->getName()) {
				choosingBuyableUnit = &List_BuyableUnit[i];
				oldRootPos = choosingBuyableUnit->root->getPosition();
				break;
			}
		}
	}
	if (type == Widget::TouchEventType::CANCELED) {
		
		choosingBuyableUnit = nullptr;
	}
	if (type == Widget::TouchEventType::ENDED) {
		if (GameScene::btn_Mode->getTitleText() == "Buy") {
			float heightPos = choosingBuyableUnit->root->getPositionY();
			CCLOG("%f", heightPos);
			if (heightPos < IngameObject::spawnPoint["1_1"].y + 50 && heightPos > IngameObject::spawnPoint["1_1"].y - 50) {
				GameScene::BuyUnit(choosingBuyableUnit->btn_Icon->getName(), 1);
			}
			else if (heightPos < IngameObject::spawnPoint["1_2"].y + 50 && heightPos > IngameObject::spawnPoint["1_2"].y - 50) {
				GameScene::BuyUnit(choosingBuyableUnit->btn_Icon->getName(), 2);
			}
			else if (heightPos < IngameObject::spawnPoint["1_3"].y + 50 && heightPos > IngameObject::spawnPoint["1_3"].y - 50) {
				GameScene::BuyUnit(choosingBuyableUnit->btn_Icon->getName(), 3);
			}
			choosingBuyableUnit->root->setPosition(oldRootPos);
		}
		else if (GameScene::btn_Mode->getTitleText() == "Upgrade") {
			GameScene::CreateUpgradeTable(((Button*)pSender)->getName());
		}
		else if (GameScene::btn_Mode->getTitleText() == "View") {
			sc_ViewDetail = ObjectConstructor::GetSpecificUnitDetails(((Button*)pSender)->getName(), visibleSize);
			staticUI->addChild(sc_ViewDetail);
			Tool::Button_ChangeState(GameScene::btn_CloseViewDetail, true, 0.5);
		}
		choosingBuyableUnit = nullptr;
	}
	
}

void GameScene::BuyUnit(string name, int line) {
	auto unitDetail = ObjectConstructor::InitializeObject(name, 0, 0, 0);
	if (ingamePlayerInfo.kingdomLevel < unitDetail->levelRequired) {
		RunActionNotify("Requried Kingdom Level " + to_string(unitDetail->levelRequired));
	}
	else if (ingamePlayerInfo.gold < unitDetail->goldCost) {
		RunActionNotify("Not enough gold!");
	}
	else {
		GameScene::InitializeIngameObject(name, line, Tool::currentPlayer->id);
		ingamePlayerInfo.gold -= unitDetail->goldCost;
		GameScene::UpdateIngamePlayerInfo();
		GameScene::RunActionNotify(name + " has spawned successfully");
	}
}

void GameScene::CreateUpgradeTable(string name) {
	BaseUnitClass unitDetails;
	if(name.find("Kingdom") != std::string::npos){
		unitDetails = *ingamePlayerInfo.kingdom;
	}
	else {
		unitDetails = *ObjectConstructor::InitializeObject(name, 0, 0, 0);
	}
	if (unitDetails.upgradeName == "") {
		RunActionNotify("This unit reached max level");
		return;
	}
	upgradeTable = Node::create();
	staticUI->addChild(upgradeTable, 1);
	upgradeTable->setPosition(visibleSize / 2);

	
	lbl_UpgradeInfo = Tool::CreateLabel(unitDetails.name + Tool::ConvertUTF16ToString(L"\n↓\n") + unitDetails.upgradeName + "\n"
	+ to_string(unitDetails.upgradeGoldCost) + " Gold     " + to_string(unitDetails.upgradeKnowledgeCost) + " Knowledge");
	lbl_UpgradeInfo->setAlignment(TextHAlignment::CENTER);
	lbl_UpgradeInfo->setPositionY(visibleSize.height*0.05);
	upgradeTable->addChild(lbl_UpgradeInfo);

	btn_ProcessUpgrade = Tool::CreateButtonWithoutSprite(name, "Process", Tool::defaultTextSize*1.3,Color3B::GREEN);
	btn_ProcessUpgrade->setPosition(Vec2(visibleSize*-0.1));
	btn_ProcessUpgrade->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Upgrade_Click, this));
	upgradeTable->addChild(btn_ProcessUpgrade);

	btn_CancelUpgrade = Tool::CreateButtonWithoutSprite(name, "Cancel", Tool::defaultTextSize*1.3, Color3B::RED);
	btn_CancelUpgrade->setPosition(Vec2(visibleSize.width*0.1,visibleSize.height*-0.1));
	btn_CancelUpgrade->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Upgrade_Click, this));
	upgradeTable->addChild(btn_CancelUpgrade);
	
}

void GameScene::UpgradeUnit(string name) {
	BaseUnitClass unitDetails;
	if (name.find("Kingdom") != std::string::npos) {
		unitDetails = *ingamePlayerInfo.kingdom;
	}
	else unitDetails = *ObjectConstructor::InitializeObject(name, 0, 0, 0);
	if (ingamePlayerInfo.kingdomLevel < unitDetails.upgradeLevelRequired) {
		RunActionNotify("Requried Kingdom Level " + to_string(unitDetails.upgradeLevelRequired));
	}
	else if (ingamePlayerInfo.gold < unitDetails.upgradeGoldCost || ingamePlayerInfo.knowledge < unitDetails.upgradeKnowledgeCost) {
		RunActionNotify("Not enough resource!");
	}
	else {
		//Upgrade Kingdom
		if (unitDetails.description == "Kingdom") {
			ingamePlayerInfo.kingdom->Upgrade();
			ingamePlayerInfo.kingdomLevel++;
			ingamePlayerInfo.lbl_KingdomLevel->setString(to_string(ingamePlayerInfo.kingdomLevel));
			ingamePlayerInfo.btn_UpgradeKingdom->setName(ingamePlayerInfo.kingdom->name);
		}
		//Upgrade Unit
		else {
			for (int i = 0; i < List_BuyableUnit.size(); i++) {
				if (List_BuyableUnit[i].btn_Icon->getName() == name) {
					auto oldItem = List_BuyableUnit[i];
					List_BuyableUnit[i].root->runAction(RemoveSelf::create());
					List_BuyableUnit[i] = Item_BuyableUnit(unitDetails.upgradeName);
					List_BuyableUnit[i].root->setPosition(oldItem.root->getPosition());
					this->buyingBar->addChild(List_BuyableUnit[i].root);
					List_BuyableUnit[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyUnit_Click, this));
					AddDragAndDropItem(List_BuyableUnit[i].root);
					break;
				}
			}
		}
		ingamePlayerInfo.gold -= unitDetails.upgradeGoldCost;
		ingamePlayerInfo.knowledge -= unitDetails.upgradeKnowledgeCost;
		GameScene::UpdateIngamePlayerInfo();
	}
}

void GameScene::btn_UpgradeKingdom(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		if (GameScene::btn_Mode->getTitleText() == "View") {
			sc_ViewDetail = ObjectConstructor::GetSpecificUnitDetails(((Button*)pSender)->getName(), visibleSize);
			staticUI->addChild(sc_ViewDetail);
			Tool::Button_ChangeState(GameScene::btn_CloseViewDetail, true, 0.5);
		}
		else {
			GameScene::CreateUpgradeTable(((Button*)pSender)->getName());
		}
	}
}

void GameScene::btn_Upgrade_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		Button* btn = (Button*)pSender;
		if (btn->getTitleText() == "Process") {
			GameScene::UpgradeUnit(btn->getName());
			upgradeTable->runAction(RemoveSelf::create());
		}
		else if (btn->getTitleText() == "Cancel") {
			upgradeTable->runAction(RemoveSelf::create());
		}
	}
}

GameScene::Item_BuyableUnit::Item_BuyableUnit(string name)
{
	this->unitInfo = ObjectConstructor::InitializeObject(name, 0, 0, 0);
	this->root = Node::create();
	if (unitInfo != nullptr) {
		this->btn_Icon = Button::create("Sprites/" + this->unitInfo->animateName + "/card.png");
		this->btn_Icon->setName(unitInfo->name);
		//this->btn_Icon = Tool::CreateButtonWithoutSprite(unitInfo->name, unitInfo->name);
		this->btn_Icon->setPosition(Vec2(0, 20));

		this->lbl_Cost = Tool::CreateLabel(to_string(unitInfo->goldCost), Tool::defaultTextSize*0.8, Color4B::YELLOW);
		this->lbl_Cost->setPosition(Vec2(0, -10));

		this->root->addChild(btn_Icon);
		this->root->addChild(lbl_Cost);
	}
}

void GameScene::CreateChatbox() {
	GameScene::sc_ChatBox = ui::ScrollView::create();
	sc_ChatBox->setContentSize(Size(visibleSize.width*0.3, visibleSize.height*0.5));
	sc_ChatBox->setInnerContainerSize(Size(1000, 200));
	sc_ChatBox->setPosition(Vec2(visibleSize.width,visibleSize.height*0.1));
	sc_ChatBox->setAnchorPoint(Vec2(1, 0));
	sc_ChatBox->setBounceEnabled(true);
	staticUI->addChild(sc_ChatBox,1);
	GameScene::EditBox_Chat = ui::EditBox::create(Size(visibleSize.width*0.25, visibleSize.height*0.06), "", "");
	EditBox_Chat->setPositionX(visibleSize.width*0.97);
	EditBox_Chat->setAnchorPoint(Vec2(1, 0));
	EditBox_Chat->setTextHorizontalAlignment(TextHAlignment::LEFT);
	EditBox_Chat->setInputMode(EditBox::InputMode::ANY);
	EditBox_Chat->setFontSize(Tool::defaultTextSize);
	EditBox_Chat->setFontColor(Color3B(175, 225, 200));
	EditBox_Chat->setPlaceHolder("Message");
	EditBox_Chat->setPlaceholderFontColor(Color3B::GRAY);
	EditBox_Chat->setMaxLength(100);
	staticUI->addChild(EditBox_Chat,10);
	

	GameScene::btn_SendMessage = Button::create("UI/GameScene/Send Message.png");
	btn_SendMessage->setAnchorPoint(Vec2(1, 0));
	btn_SendMessage->setPositionX(visibleSize.width);
	btn_SendMessage->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_SendMessage_Click, this));
	staticUI->addChild(btn_SendMessage);

	chatBoxContent.push_back("ImaginysLight: 1  ");
	chatBoxContent.push_back("ImaginysLight: 2  ");
	chatBoxContent.push_back("ImaginysLight: 3  ");
	chatBoxContent.push_back("ImaginysLight: 4  ");
	chatBoxContent.push_back("ImaginysLight: 5  ");
	chatBoxContent.push_back("ImaginysLight: 5  ");
	chatBoxContent.push_back("ImaginysLight: 5  ");
	chatBoxContent.push_back("ImaginysLight: 5  ");
	chatBoxContent.push_back("ImaginysLight: 5  ");
	chatBoxContent.push_back("ImaginysLight: 5  ");
	UpdateChatbox();
	

}
void GameScene::UpdateChatbox() {
	vector<int> labelHeight;
	int currentHeight = 10;
	sc_ChatBox->removeAllChildrenWithCleanup(true);
	sc_ChatBox->scrollToBottom(0, false);
	for (int i = 0; i < chatBoxContent.size(); i++) {
		Label* lbl_Content = Tool::CreateLabel(chatBoxContent[i]);
		lbl_Content->setMaxLineWidth(sc_ChatBox->getContentSize().width*0.9);
		currentHeight += (lbl_Content->getBoundingBox().size.height / 2);
		labelHeight.push_back(currentHeight);
		currentHeight += (8 + lbl_Content->getBoundingBox().size.height / 2);
	}
	sc_ChatBox->setInnerContainerSize(Size(1000, currentHeight + 20));
	for (int i = 0; i < chatBoxContent.size(); i++) {
		Label* lbl_Content = Tool::CreateLabel(chatBoxContent[i]);
		lbl_Content->setMaxLineWidth(sc_ChatBox->getContentSize().width*0.9);
		lbl_Content->setPosition(Vec2(10,sc_ChatBox->getInnerContainerSize().height - labelHeight[i]));
		lbl_Content->setAnchorPoint(Vec2(0, 0.5));
		sc_ChatBox->addChild(lbl_Content);
	}
}

void GameScene::btn_SendMessage_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		string content = GameScene::EditBox_Chat->getText();
		if (content.size() < 1) return;
		GameScene::chatBoxContent.push_back(Tool::currentPlayer->username + ": " + content);
		GameScene::EditBox_Chat->setText("");
		GameScene::UpdateChatbox();
	}
}
void GameScene::CreateQuestionTable()
{
	questionTable = Node::create();
	questionTable->setVisible(false);
	questionTable->setPosition(visibleSize / 2);
	questionTable->runAction(MoveBy::create(0, Vec2(0, visibleSize.height)));
	staticUI->addChild(questionTable, 1);

	Sprite* sp_QuestionTableBackground = Sprite::create("UI/GameScene/QuestionTable/background.png");
	sp_QuestionTableBackground->setPosition(Vec2(visibleSize.width * 0, visibleSize.height*-0.05));
	sp_QuestionTableBackground->setScale(1.15);
	questionTable->addChild(sp_QuestionTableBackground);
	// các button đáp án
	{
		btn_Answer1 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Answer1->setName("btn_Answer1");
		btn_Answer1->setEnabled(false);
		btn_Answer1->setTitleFontSize(Tool::defaultTextSize);
		btn_Answer1->setPosition(Vec2(0, visibleSize.height*-0.05));
		btn_Answer1->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_AnswerClick, this));
		questionTable->addChild(btn_Answer1, 1);

		btn_Answer2 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Answer2->setName("btn_Answer2");
		btn_Answer2->setEnabled(false);
		btn_Answer2->setTitleFontSize(Tool::defaultTextSize);
		btn_Answer2->setPosition(Vec2(0, visibleSize.height*-0.15));
		btn_Answer2->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_AnswerClick, this));
		questionTable->addChild(btn_Answer2, 1);

		btn_Answer3 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Answer3->setName("btn_Answer3");
		btn_Answer3->setEnabled(false);
		btn_Answer3->setTitleFontSize(Tool::defaultTextSize);
		btn_Answer3->setPosition(Vec2(0, visibleSize.height*-0.25));
		btn_Answer3->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_AnswerClick, this));
		questionTable->addChild(btn_Answer3, 1);

		btn_Answer4 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Answer4->setName("btn_Answer4");
		btn_Answer4->setEnabled(false);
		btn_Answer4->setTitleFontSize(Tool::defaultTextSize);
		btn_Answer4->setPosition(Vec2(0, visibleSize.height*-0.35));
		btn_Answer4->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_AnswerClick, this));
		questionTable->addChild(btn_Answer4, 1);
	}
	// các button chọn level
	{
		btn_Level1 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Level1->setName("btn_Level1");
		btn_Level1->setTitleText("Easy");
		btn_Level1->setTitleFontSize(Tool::defaultTextSize);
		btn_Level1->setPosition(Vec2(0, visibleSize.height*-0.05));
		btn_Level1->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		questionTable->addChild(btn_Level1, 1);

		btn_Level2 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Level2->setName("btn_Level2");
		btn_Level2->setTitleText("Medium");
		btn_Level2->setTitleFontSize(Tool::defaultTextSize);
		btn_Level2->setPosition(Vec2(0, visibleSize.height*-0.15));
		btn_Level2->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		questionTable->addChild(btn_Level2, 1);

		btn_Level3 = Button::create("UI/GameScene/QuestionTable/answer.png", "UI/GameScene/QuestionTable/answer_S.png");
		btn_Level3->setName("btn_Level3");
		btn_Level3->setTitleText("Hard");
		btn_Level3->setTitleFontSize(Tool::defaultTextSize);
		btn_Level3->setPosition(Vec2(0, visibleSize.height*-0.25));
		btn_Level3->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		questionTable->addChild(btn_Level3, 1);

	}
	//list view câu hỏi
	{
		lv_QuestionContent = ListView::create();
		questionTable->addChild(lv_QuestionContent, 1);
		lv_QuestionContent->setContentSize({ 450, 120 });
		txt_Question = Text::create("", "fonts/arial.ttf", Tool::defaultTextSize);
		txt_Question->setTextAreaSize({ 450,0 });
		lv_QuestionContent->setPosition(Vec2(0, visibleSize.height * 0.25));
		lv_QuestionContent->setAnchorPoint(Vec2(0.5, 1));
		lv_QuestionContent->addChild(txt_Question);
		lv_QuestionContent->requestDoLayout(); //this triggers resizing the listview to accommodate the
									 //string content. Needs to happen each time you
									 //text->setString(new_content) too.
	}

	// label level
	{
		lbl_Level = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize*1.5);
		lbl_Level->setColor(Color3B::MAGENTA);
		lbl_Level->setPosition(Vec2(0, visibleSize.height *.35));
		questionTable->addChild(lbl_Level, 1);
	}

	GameScene::ChangeQuestionTableState(questionAvailable);
}

void GameScene::btn_AnswerClick(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		btn_Answer1->setEnabled(false);
		btn_Answer2->setEnabled(false);
		btn_Answer3->setEnabled(false);
		btn_Answer4->setEnabled(false);
		if (((Button*)pSender)->getTitleText() == answer) {
			GameScene::CorrectAnswer();
			((Button*)pSender)->setTitleColor(Color3B::GREEN);
		}
		else {
			((Button*)pSender)->setTitleColor(Color3B::RED);
		}
	}
}

void GameScene::Respone_ReadQuestion(cocos2d::network::HttpClient * sender, cocos2d::network::HttpResponse * response)
{
	////Lấy thông tin từ server
	//string* a = new string();
	//vector <string*> Vec;
	//vector<char> *buffer = response->getResponseData();
	//for (unsigned int i = 0; i < buffer->size(); i++)
	//{
	//	*a = *a + (*buffer)[i];
	//}
	//Tool::CutString(a, Vec, "@");

	////Gán vào question
	//txt_Question->setString(*(Vec[0]));
	//lv_QuestionContent->requestDoLayout();

	////Level
	//currentQuestionLevel = Tool::ConvertStringToInt(*(Vec[1]));
	//lbl_Level->setString([&]() -> string {
	//	if (currentQuestionLevel == 1) return "easy";
	//	else if (currentQuestionLevel == 2) return "medium";
	//	else if (currentQuestionLevel == 3) return "hard";
	//	else if (currentQuestionLevel == 4) return "extreme";
	//}());
	//answer = (*(Vec[2]));

	////Button
	//btn_Answer1->setTitleText(*(Vec[3]));
	//btn_Answer2->setTitleText(*(Vec[4]));
	//btn_Answer3->setTitleText(*(Vec[5]));
	//btn_Answer4->setTitleText(*(Vec[6]));

	////Thời gian trả lời
	//destinationTime = 20 * currentQuestionLevel + Tool::currentIngameTime;
	//if (200 == response->getResponseCode())
	//{
	//	//CCLOG("Succeeded");
	//}
	//else
	//{
	//	//CCLOG("Failed");
	//}
}

void GameScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(0.5), nullptr));
}

void GameScene::UpdateIngamePlayerInfo()
{
	ingamePlayerInfo.lbl_Gold->setString(to_string((int)ingamePlayerInfo.gold));
	ingamePlayerInfo.lbl_Knowledge->setString(to_string((int)ingamePlayerInfo.knowledge));
	ingamePlayerInfo.lbl_Energy->setString(to_string((int)ingamePlayerInfo.energy));
}

void GameScene::CorrectAnswer()
{
	auto answerTimeRemain = destinationTime - Tool::currentIngameTime;
	ingamePlayerInfo.gold += currentQuestionLevel * 15 * (1 + answerTimeRemain / (currentQuestionLevel * 20));
	ingamePlayerInfo.lbl_Gold->setString("Gold: " + to_string(ingamePlayerInfo.gold));
}

void GameScene::WrongAnswer()
{
}

void GameScene::ShowUnitDetails()
{
	auto details = UnitDetails(*GameScene::choosingUnit, -Vec2(visibleSize.width*0.1, visibleSize.height*0.05));
	GameScene::unitDetails->removeAllChildrenWithCleanup(true);
	GameScene::unitDetails->setAnchorPoint(Vec2(1, 1));
	GameScene::unitDetails->setPosition(visibleSize);
	GameScene::unitDetails->addChild(details.details);
}

void GameScene::Request_RandomQuestion(string level)
{
	/*string dataToSend = "level=" + level;
	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost/Back_End_Game/GameScene/Random_Question.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setRequestData(dataToSend.c_str(), dataToSend.size());
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();*/
}

void GameScene::Request_ReadQuestion()
{
	/*cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost/Back_End_Game/GameScene/Read_Question.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(GameScene::Respone_ReadQuestion, this));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();*/
}

GameScene::UnitDetails::UnitDetails(BaseUnitClass object, Vec2 position)
{
	this->details = Node::create();

	this->lbl_Name = Tool::CreateLabel(object.name,Tool::defaultTextSize*0.8);
	lbl_Name->enableBold();
	lbl_Name->setPosition(position);
	details->addChild(lbl_Name);

	this->lbl_Health = Tool::CreateLabel(to_string((int)object.currentHealth),Tool::defaultTextSize*0.8,Color4B::GREEN);
	lbl_Health->setPosition(position + Vec2(42,-42));
	lbl_Health->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_Health);

	this->lbl_Defense = Tool::CreateLabel(to_string((int)object.defense), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Defense->setPosition(position + Vec2(42, -77));
	lbl_Defense->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_Defense);

	this->lbl_Regeneration = Tool::CreateLabel(to_string((int)object.regeneration), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Regeneration->setPosition(position + Vec2(42, -113));
	lbl_Regeneration->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_Regeneration);

	this->lbl_Attack = Tool::CreateLabel(to_string((int)object.attack), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Attack->setPosition(position + Vec2(-21, -42));
	lbl_Attack->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_Attack);

	auto temp = CCString::createWithFormat("%.1f", object.attackSpeed);
	this->lbl_AttackSpeed = Tool::CreateLabel(temp->getCString(), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_AttackSpeed->setPosition(position + Vec2(-21, -77));
	lbl_AttackSpeed->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_AttackSpeed); 

	this->lbl_MoveSpeed = Tool::CreateLabel(to_string((int)object.moveSpeed), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_MoveSpeed->setPosition(position + Vec2(-21, -113));
	lbl_MoveSpeed->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_MoveSpeed);

	this->lbl_Range = Tool::CreateLabel(to_string((int)object.range), Tool::defaultTextSize*0.8, Color4B::GREEN);
	lbl_Range->setPosition(position + Vec2(-21, -149));
	lbl_Range->setAnchorPoint(Vec2(0, 0.5));
	details->addChild(lbl_Range);
	
	this->sp_Background = Sprite::create("UI/GameScene/Choosing Unit Details.png");
	sp_Background->setAnchorPoint(Vec2(1, 1));
	details->addChild(sp_Background,-1);
	
}
