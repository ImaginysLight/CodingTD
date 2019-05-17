#include"GameScene.h"
USING_NS_CC;

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

	Tool::currentPlayer->id = 5;
	Tool::currentPlayer->elementName = "Ice";

	//Random question trước cho chắc
	//GameScene::Request_RandomQuestion(nextQuestionLevel);

	GameScene::SetupCamera();

	GameScene::SetupGUI();

	IngameObject::loadAnimate();

	IngameObject::loadIngameObjectStaticVariables();

	
	

	{
		GameScene::InitializeIngameObject("Frozen Kingdom", 3, 5);
		GameScene::InitializeIngameObject("Poisonous Butterfly 2", 3, 5);
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
	ingamePlayerInfo.mana += 1;
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
		else if (name == "btn_ViewDetail") {
			GameScene::isUpgrade = false;
			GameScene::isViewDetail = !isViewDetail;
			if (isViewDetail) RunActionNotify("View Detail Mode Activating!");
			else RunActionNotify("View Detail Mode Off!");
		}
		else if (name == "btn_Upgrade") {
			GameScene::isViewDetail = false;
			GameScene::isUpgrade = !isUpgrade;
			if (isUpgrade) RunActionNotify("Upgrade Mode Activating!");
			else RunActionNotify("Upgrade Mode Off!");
		}
		else if (name == "btn_CloseViewDetail") {
			GameScene::sc_ViewDetail->runAction(RemoveSelf::create());
			Tool::Button_ChangeState(btn_CloseViewDetail, false, 0);
		}
	}
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
	this->addChild(staticUI,4);

	unitDetails = Node::create();
	staticUI->addChild(unitDetails);

	ingamePlayerInfo.lbl_KingdomLevel->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.95));
	staticUI->addChild(ingamePlayerInfo.lbl_KingdomLevel);
	ingamePlayerInfo.lbl_Gold->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.9));
	staticUI->addChild(ingamePlayerInfo.lbl_Gold);
	ingamePlayerInfo.lbl_Energy->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.85));
	staticUI->addChild(ingamePlayerInfo.lbl_Energy);
	ingamePlayerInfo.lbl_Mana->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.8));
	staticUI->addChild(ingamePlayerInfo.lbl_Mana);
	ingamePlayerInfo.btn_UpgradeMainTower->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.95));
	//ingamePlayerInfo.btn_UpgradeMainTower->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_UpgradeObjectClick, this));
	staticUI->addChild(ingamePlayerInfo.btn_UpgradeMainTower);

	auto background = Sprite::create("UI/GameScene/background (3).png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(-500, 0));
	this->addChild(background, -1);

	/*auto background2 = Sprite::create("UI/GameScene/background.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(3500, 0));
	background2->setRotation3D(Vec3(0, 180, 0));
	this->addChild(background2, -1);*/

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

	

	GameScene::CreateBuyingBar();
	GameScene::CreateQuestionTable();

}

void GameScene::CreateBuyingBar() {
	buyingBar = Node::create();
	staticUI->addChild(buyingBar,1);

	GameScene::btn_ViewDetail = Tool::CreateButtonWithoutSprite("btn_ViewDetail","Detail");
	btn_ViewDetail->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.05));
	btn_ViewDetail->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_ViewDetail);

	GameScene::btn_CloseViewDetail = Tool::CreateButtonWithoutSprite("btn_CloseViewDetail", "Close", Tool::defaultTextSize, Color3B::RED);
	btn_CloseViewDetail->setPosition(visibleSize*0.85);
	Tool::Button_ChangeState(btn_CloseViewDetail, false, 0);
	btn_CloseViewDetail->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	staticUI->addChild(btn_CloseViewDetail,1);

	GameScene::btn_Upgrade = Tool::CreateButtonWithoutSprite("btn_Upgrade", "Upgrade");
	btn_Upgrade->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.05));
	btn_Upgrade->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_Upgrade);

	List_BuyableUnit.push_back(Item_BuyableUnit("Hotheaded Gunner"));
	List_BuyableUnit.push_back(Item_BuyableUnit("Crazy Wolf"));
	List_BuyableUnit.push_back(Item_BuyableUnit("Dead Walker"));
	List_BuyableUnit.push_back(Item_BuyableUnit("Helicopter"));
	List_BuyableUnit.push_back(Item_BuyableUnit("Frost Wyvern"));
	List_BuyableUnit.push_back(Item_BuyableUnit("Poisonous Butterfly"));
	this->buyingBar->addChild(ghostItem);
	for (int i = 0; i < List_BuyableUnit.size(); i++) {
		this->buyingBar->addChild(List_BuyableUnit[i].root);
		List_BuyableUnit[i].root->setPosition(Vec2(visibleSize.width*(0.2 + 0.12*i), visibleSize.height*0.05));
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
	if (GameScene::choosingBuyableUnit != nullptr) {
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
		float heightPos = choosingBuyableUnit->root->getPositionY();
		if (heightPos < IngameObject::spawnPoint["1_1"].y + 25 && heightPos > IngameObject::spawnPoint["1_1"].y - 26) {
			GameScene::BuyUnit(choosingBuyableUnit->btn_Icon->getName(),1);
		}
		else if (heightPos < IngameObject::spawnPoint["1_2"].y + 25 && heightPos > IngameObject::spawnPoint["1_2"].y - 26) {
			GameScene::BuyUnit(choosingBuyableUnit->btn_Icon->getName(), 2);
		}
		else if (heightPos < IngameObject::spawnPoint["1_3"].y + 25 && heightPos > IngameObject::spawnPoint["1_3"].y - 26) {
			GameScene::BuyUnit(choosingBuyableUnit->btn_Icon->getName(), 3);
		}
		choosingBuyableUnit->root->setPosition(oldRootPos);
		choosingBuyableUnit = nullptr;
	}
	if (type == Widget::TouchEventType::ENDED) {
		if (GameScene::isViewDetail) {
			sc_ViewDetail = ObjectConstructor::GetSpecificUnitDetails(((Button*)pSender)->getName(),visibleSize);
			staticUI->addChild(sc_ViewDetail);
			Tool::Button_ChangeState(GameScene::btn_CloseViewDetail, true, 0.5);
			GameScene::isViewDetail = false;
		}
		if (GameScene::isUpgrade) {
			GameScene::CreateUpgradeTable(((Button*)pSender)->getName());
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
	}
}

void GameScene::CreateUpgradeTable(string name) {
	upgradeTable = Node::create();
	staticUI->addChild(upgradeTable, 1);
	upgradeTable->setPosition(visibleSize / 2);

	auto unitDetails = ObjectConstructor::InitializeObject(name, 0, 0, 0);
	lbl_UpgradeInfo = Tool::CreateLabel(unitDetails->name + Tool::ConvertUTF16ToString(L"\n↓\n") + unitDetails->upgradeName + "\n"
	+ to_string(unitDetails->upgradeGoldCost) + " Gold     " + to_string(unitDetails->upgradeEnergyCost) + " Energy");
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
	auto unitDetail = ObjectConstructor::InitializeObject(name, 0, 0, 0);
	if (ingamePlayerInfo.kingdomLevel < unitDetail->upgradeLevelRequired) {
		RunActionNotify("Requried Kingdom Level " + to_string(unitDetail->upgradeLevelRequired));
	}
	else if (ingamePlayerInfo.gold < unitDetail->upgradeGoldCost || ingamePlayerInfo.energy < unitDetail->upgradeEnergyCost) {
		RunActionNotify("Not enough resource!");
	}
	else {
		for (int i = 0; i < List_BuyableUnit.size(); i++) {
			if (List_BuyableUnit[i].btn_Icon->getName() == name) {
				auto oldItem = List_BuyableUnit[i];
				List_BuyableUnit[i].root->runAction(RemoveSelf::create());
				List_BuyableUnit[i] = Item_BuyableUnit(unitDetail->upgradeName);
				List_BuyableUnit[i].root->setPosition(oldItem.root->getPosition());
				this->buyingBar->addChild(List_BuyableUnit[i].root);
				List_BuyableUnit[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyUnit_Click, this));
				AddDragAndDropItem(List_BuyableUnit[i].root);
				break;
			}
		}
		ingamePlayerInfo.gold -= unitDetail->upgradeGoldCost;
		ingamePlayerInfo.energy -= unitDetail->upgradeEnergyCost;
		GameScene::UpdateIngamePlayerInfo();
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
		GameScene::isUpgrade = false;
	}
}

GameScene::Item_BuyableUnit::Item_BuyableUnit(string name)
{
	this->unitInfo = ObjectConstructor::InitializeObject(name, 0, 0, 0);
	this->root = Node::create();
	if (unitInfo != nullptr) {
		this->btn_Icon = Tool::CreateButtonWithoutSprite(unitInfo->name, unitInfo->name,Tool::defaultTextSize*0.8);
		this->btn_Icon->setPosition(Vec2(0, 10));

		this->lbl_Cost = Tool::CreateLabel(to_string(unitInfo->goldCost), Tool::defaultTextSize*0.8, Color4B::YELLOW);
		this->lbl_Cost->setPosition(Vec2(0, -10));

		this->root->addChild(btn_Icon);
		this->root->addChild(lbl_Cost);
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

GameScene::IngamePlayer::IngamePlayer()
{
	this->lbl_Gold = Tool::CreateLabel("Gold: " + to_string(this->gold), Tool::defaultTextSize*1.25, Color4B::YELLOW,CCTextAlignment::LEFT);
	this->lbl_Gold->setAnchorPoint(Vec2(0, 0.5));
	this->lbl_Energy = Tool::CreateLabel("Energy: " + to_string(this->energy), Tool::defaultTextSize*1.25, Color4B(Color3B::BLUE,255), CCTextAlignment::LEFT);
	this->lbl_Energy->setAnchorPoint(Vec2(0, 0.5));
	this->lbl_Mana = Tool::CreateLabel("Mana: " + to_string(this->mana), Tool::defaultTextSize*1.25, Color4B(Color3B(175,225,250), 255), CCTextAlignment::LEFT);
	this->lbl_Mana->setAnchorPoint(Vec2(0, 0.5));
	this->lbl_KingdomLevel = Tool::CreateLabel("Level: " + to_string(this->kingdomLevel), Tool::defaultTextSize*1.25, Color4B::GREEN, CCTextAlignment::LEFT);
	this->lbl_KingdomLevel->setAnchorPoint(Vec2(0, 0.5));
	this->btn_UpgradeMainTower = Tool::CreateButtonWithoutSprite("MainTower1", Tool::ConvertUTF16ToString(L"Up ↑"));
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
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

void GameScene::UpdateIngamePlayerInfo()
{
	ingamePlayerInfo.lbl_Gold->setString("Gold: " + to_string((int)ingamePlayerInfo.gold));
	ingamePlayerInfo.lbl_Energy->setString("Energy: " + to_string((int)ingamePlayerInfo.energy));
	ingamePlayerInfo.lbl_Mana->setString("Mana: " + to_string((int)ingamePlayerInfo.mana));
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
	auto details = UnitDetails(*GameScene::choosingUnit, Vec2(visibleSize.width*0.8, visibleSize.height*0.95));
	GameScene::unitDetails->removeAllChildrenWithCleanup(true);
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

	this->lbl_Name = Tool::CreateLabel("Name " + object.name);
	lbl_Name->setPosition(position);
	details->addChild(lbl_Name);

	this->lbl_Health = Tool::CreateLabel("Health " + to_string((int)object.currentHealth) + " / " + to_string((int)object.maxHealth));
	lbl_Health->setPosition(position + Vec2(0,-20));
	details->addChild(lbl_Health);

	this->lbl_Attack = Tool::CreateLabel("Attack " + to_string((int)object.attack));
	lbl_Attack->setPosition(position + Vec2(0, -40));
	details->addChild(lbl_Attack);

	this->lbl_Defense = Tool::CreateLabel("Defense " + to_string((int)object.defense));
	lbl_Defense->setPosition(position + Vec2(0, -60));
	details->addChild(lbl_Defense);

	this->lbl_Speed = Tool::CreateLabel("Speed " + to_string((int)object.moveSpeed));
	lbl_Speed->setPosition(position + Vec2(0, -80));
	details->addChild(lbl_Speed);

	auto temp = CCString::createWithFormat("Attack Speed %.1f", object.attackSpeed);
	this->lbl_AttackRate = Tool::CreateLabel(temp->getCString());
	lbl_AttackRate->setPosition(position + Vec2(0, -100));
	details->addChild(lbl_AttackRate);

}
