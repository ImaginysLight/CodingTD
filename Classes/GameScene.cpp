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

	GameScene::GetBuyableObject();

	GameScene::SetupGUI();

	IngameObject::loadAnimate();

	IngameObject::loadIngameObjectStaticVariables();


	{
		GameScene::InitializeIngameObject("Crazy Wolf", 1, 8);
		GameScene::InitializeIngameObject("Crazy Wolf", 3, 8);
	
		GameScene::InitializeIngameObject("Helicopter", 2, 5);
	}





	this->schedule(schedule_selector(GameScene::UpdateIngameObject), 1/60);
	this->schedule(schedule_selector(GameScene::UpdateQuestionInfo), 0.25);
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
		if (name == "btn_Buying_Back") {
			GameScene::RunActionButtonBuyingBack();
		}
		else if (name == "btn_Buying_Next") {
			GameScene::RunActionButtonBuyingNext();
		}
		else if (name == "btn_ChooseLine1" || name == "btn_ChooseLine2" || name == "btn_ChooseLine3") {
			choosingLine = Tool::ConvertStringToInt(name.substr(name.size() - 1, 1));
			btn_ChooseLine1->setTitleColor(Color3B::WHITE);
			btn_ChooseLine2->setTitleColor(Color3B::WHITE);
			btn_ChooseLine3->setTitleColor(Color3B::WHITE);
			((Button*)pSender)->setTitleColor(Color3B::GREEN);

		}
		else if (name == "btn_DropDownQuestionTable") {
			questionTable->setVisible(true);
			if (questionTable->getPositionY() > visibleSize.height) 
				questionTable->runAction(MoveBy::create(0.5, Vec2(0, -visibleSize.height)));
			else questionTable->runAction(MoveBy::create(0.5, Vec2(0, visibleSize.height)));
		}
		else if (name == "btn_SwitchBuyingBar") {
			if (btn_SwitchBuyingBar->getTitleText() == "<") {
				buyingBar->runAction(MoveBy::create(0.5, Vec2(-visibleSize.width*0.25, 0)));
				btn_SwitchBuyingBar->setTitleText(">");
			}
			else {
				buyingBar->runAction(MoveBy::create(0.5, Vec2(visibleSize.width*0.25, 0)));
				btn_SwitchBuyingBar->setTitleText("<");
			}
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
	}
}

void GameScene::btn_BuyObjectClick(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Node*)pSender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		////Lấy thông tin lính đang mua
		//auto object = ObjectConstructor::InitializeObject(name, 0, 0, 0);
		////Kiểm tra cấp nhà chính
		//if (GameScene::ingamePlayerInfo.mainTowerLevel < object->levelRequired) { 
		//	RunActionNotify("Require main tower level " + to_string(object->levelRequired));
		//	return;
		//}
		////Nếu không đủ tiền thì thông báo và break
		//if (object->cost > ingamePlayerInfo.gold) {
		//	RunActionNotify("Not enough resources!");
		//	return;
		//}
		////Trừ tiền
		//ingamePlayerInfo.gold -= object->cost;
		//ingamePlayerInfo.lbl_Gold->setString("Gold: " + to_string(ingamePlayerInfo.gold));

		////Send thông tin lên server


		////Tạo lính
		//GameScene::InitializeIngameObject(name, choosingLine, true);
	}
}

void GameScene::btn_UpgradeObjectClick(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		////Lấy thông tin robot upgrade
		//string name = ((Button*)pSender)->getName();
		//auto object = ObjectConstructor::InitializeObject(name, 0, 0, 0);

		////Kiểm tra cấp nhà chính
		//if (GameScene::ingamePlayerInfo.mainTowerLevel < object->upgradeLevelRequired) {
		//	RunActionNotify("Require main tower level " + to_string(object->upgradeLevelRequired));
		//	return;
		//}
		//
		////Kiểm tra gold và energy
		//if (object->upgradeGold > ingamePlayerInfo.gold || object->upgradeEnergy > ingamePlayerInfo.energy) {
		//	RunActionNotify("Not enough resources!");
		//	return;
		//}

		////Trừ tiền
		//ingamePlayerInfo.gold -= object->upgradeGold;
		//ingamePlayerInfo.lbl_Gold->setString("Gold: " + to_string(ingamePlayerInfo.gold));
		//ingamePlayerInfo.energy -= object->upgradeEnergy;
		//ingamePlayerInfo.lbl_Energy->setString("Energy: " + to_string(ingamePlayerInfo.energy));

		////Cập nhật danh sách mua
		//for (int i = 0; i < List_BuyableObject.size(); i++) {
		//	if (List_BuyableObject[i].btn_Icon->getName() == name) {
		//		auto  oldItemInfo = List_BuyableObject[i];
		//		List_BuyableObject[i] = Item_BuyableObject(object->upgradeTo);
		//		List_BuyableObject[i].btn_Icon->setPosition(oldItemInfo.btn_Icon->getPosition());
		//		List_BuyableObject[i].btn_Upgrade->setPosition(oldItemInfo.btn_Upgrade->getPosition());
		//		List_BuyableObject[i].lbl_Cost->setPosition(oldItemInfo.lbl_Cost->getPosition());
		//		List_BuyableObject[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyObjectClick, this));
		//		List_BuyableObject[i].btn_Upgrade->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_UpgradeObjectClick, this));

		//		oldItemInfo.item->runAction(RemoveSelf::create());
		//		buyingBar->addChild(List_BuyableObject[i].item);
		//		RunActionNotify("Upgrade to " + object->upgradeTo + " successful");
		//	}
		//}
	}
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




void GameScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}


bool GameScene::onTouchBegan(Touch* touch, Event* event) {
	Camera::getDefaultCamera()->setAnchorPoint(Vec2(0, 0.5));
	for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
		if (unit->sprite->getBoundingBox().containsPoint(staticUI->getPosition() + touch->getLocation() - unit->root->getPosition())) {
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

void GameScene::SetupCamera() {
	auto cameraSprite = Sprite::create();
	this->addChild(cameraSprite);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = (CC_CALLBACK_2(GameScene::onTouchBegan, this));
	touchListener->onTouchMoved = (CC_CALLBACK_2(GameScene::onTouchMoved, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, cameraSprite);
}
void GameScene::SetupGUI() {
	staticUI = Node::create();
	this->addChild(staticUI,4);

	unitDetails = Node::create();
	staticUI->addChild(unitDetails);

	ingamePlayerInfo.lbl_MainTowerLevel->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.95));
	staticUI->addChild(ingamePlayerInfo.lbl_MainTowerLevel);
	ingamePlayerInfo.lbl_Gold->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.9));
	staticUI->addChild(ingamePlayerInfo.lbl_Gold);
	ingamePlayerInfo.lbl_Energy->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.85));
	staticUI->addChild(ingamePlayerInfo.lbl_Energy);
	ingamePlayerInfo.btn_UpgradeMainTower->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.95));
	ingamePlayerInfo.btn_UpgradeMainTower->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_UpgradeObjectClick, this));
	staticUI->addChild(ingamePlayerInfo.btn_UpgradeMainTower);

	auto background1 = Sprite::create("UI/GameScene/background.png");
	background1->setAnchorPoint(Vec2(0, 0));
	background1->setPosition(Vec2(-500, 0));
	this->addChild(background1, -1);

	auto background2 = Sprite::create("UI/GameScene/background.png");
	background2->setAnchorPoint(Vec2(0, 0));
	background2->setPosition(Vec2(3500, 0));
	background2->setRotation3D(Vec3(0, 180, 0));
	this->addChild(background2, -1);

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

	

	//GameScene::CreateBuyingBar();

	//button chọn line để thả
	{
		auto lbl_Line = Tool::CreateLabel("Line: ", Tool::defaultTextSize*1.5, Color4B::RED);
		lbl_Line->setPosition(Vec2(visibleSize.width *0.05, visibleSize.height*0.05));
		staticUI->addChild(lbl_Line);

		btn_ChooseLine1 = Tool::CreateButtonWithoutSprite("btn_ChooseLine1", "1", Tool::defaultTextSize * 2, Color3B::GREEN);
		btn_ChooseLine1->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height*0.05));
		btn_ChooseLine1->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		staticUI->addChild(btn_ChooseLine1);

		btn_ChooseLine2 = Tool::CreateButtonWithoutSprite("btn_ChooseLine2", "2", Tool::defaultTextSize * 2);
		btn_ChooseLine2->setPosition(Vec2(visibleSize.width *0.15, visibleSize.height*0.05));
		btn_ChooseLine2->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		staticUI->addChild(btn_ChooseLine2);

		btn_ChooseLine3 = Tool::CreateButtonWithoutSprite("btn_ChooseLine3", "3", Tool::defaultTextSize * 2);
		btn_ChooseLine3->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.05));
		btn_ChooseLine3->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		staticUI->addChild(btn_ChooseLine3);
	}

	//Bảng câu hỏi
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
			questionTable->addChild(lv_QuestionContent,1);
			lv_QuestionContent->setContentSize({ 450, 120});
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
}





void GameScene::RunActionButtonBuyingBack()
{
	if (currentPositionOfBuyingBar < 1) return;

	float fadeTime = 0.5;
	auto MoveDown = MoveBy::create(fadeTime, Vec2(0, visibleSize.height*-distanceBetweenItems));
	auto MoveDown_FadeIn = Spawn::create(MoveDown, FadeIn::create(fadeTime), nullptr);
	auto MoveDown_FadeOut = Spawn::create(MoveDown, FadeOut::create(fadeTime), nullptr);

	List_BuyableObject[currentPositionOfBuyingBar - 1].lbl_Cost->runAction(MoveDown_FadeIn->clone());
	List_BuyableObject[currentPositionOfBuyingBar - 1].btn_Icon->setEnabled(true);
	List_BuyableObject[currentPositionOfBuyingBar - 1].btn_Icon->runAction(MoveDown_FadeIn->clone());
	List_BuyableObject[currentPositionOfBuyingBar - 1].btn_Upgrade->setEnabled(true);
	List_BuyableObject[currentPositionOfBuyingBar - 1].btn_Upgrade->runAction(MoveDown_FadeIn->clone());

	for (int i = 0; i < numOfVisibleItem - 1; i++) {
		List_BuyableObject[currentPositionOfBuyingBar + i].btn_Icon->runAction(MoveDown->clone());
		List_BuyableObject[currentPositionOfBuyingBar + i].btn_Upgrade->runAction(MoveDown->clone());
		List_BuyableObject[currentPositionOfBuyingBar + i].lbl_Cost->runAction(MoveDown->clone());
	}

	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem - 1].lbl_Cost->runAction(MoveDown_FadeOut->clone());
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem - 1].btn_Icon->setEnabled(false);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem - 1].btn_Icon->runAction(MoveDown_FadeOut->clone());
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem - 1].btn_Upgrade->setEnabled(false);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem - 1].btn_Upgrade->runAction(MoveDown_FadeOut->clone());
	
	currentPositionOfBuyingBar--;
}

void GameScene::RunActionButtonBuyingNext() {
	if (currentPositionOfBuyingBar + numOfVisibleItem >= List_BuyableObject.size()) return;

	float fadeTime = 0.5;
	auto MoveUp = MoveBy::create(fadeTime, Vec2(0, visibleSize.height*distanceBetweenItems));
	auto MoveUp_FadeIn = Spawn::create(MoveUp, FadeIn::create(fadeTime), nullptr);
	auto MoveUp_FadeOut = Spawn::create(MoveUp, FadeOut::create(fadeTime), nullptr);

	List_BuyableObject[currentPositionOfBuyingBar].lbl_Cost->runAction(MoveUp_FadeOut->clone());
	List_BuyableObject[currentPositionOfBuyingBar].btn_Icon->setEnabled(false);
	List_BuyableObject[currentPositionOfBuyingBar].btn_Icon->runAction(MoveUp_FadeOut->clone());
	List_BuyableObject[currentPositionOfBuyingBar].btn_Upgrade->setEnabled(false);
	List_BuyableObject[currentPositionOfBuyingBar].btn_Upgrade->runAction(MoveUp_FadeOut->clone());

	for (int i = 1; i < numOfVisibleItem; i++) {
		List_BuyableObject[currentPositionOfBuyingBar + i].btn_Icon->runAction(MoveUp->clone());
		List_BuyableObject[currentPositionOfBuyingBar + i].btn_Upgrade->runAction(MoveUp->clone());
		List_BuyableObject[currentPositionOfBuyingBar + i].lbl_Cost->runAction(MoveUp->clone());
	}

	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].lbl_Cost->setVisible(true);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].lbl_Cost->runAction(MoveUp_FadeIn->clone());
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].btn_Icon->setVisible(true);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].btn_Icon->setEnabled(true);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].btn_Icon->runAction(MoveUp_FadeIn->clone());
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].btn_Upgrade->setVisible(true);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].btn_Upgrade->setEnabled(true);
	List_BuyableObject[currentPositionOfBuyingBar + numOfVisibleItem].btn_Upgrade->runAction(MoveUp_FadeIn->clone());
	
	currentPositionOfBuyingBar++;
}


void GameScene::GetBuyableObject() {
	List_BuyableObject.push_back(Item_BuyableObject("Robot2"));
	List_BuyableObject.push_back(Item_BuyableObject("Robot5"));
	List_BuyableObject.push_back(Item_BuyableObject("Robot7"));
	List_BuyableObject.push_back(Item_BuyableObject("Robot10"));
	List_BuyableObject.push_back(Item_BuyableObject("Robot12"));
}

void GameScene::CreateBuyingBar() {
	buyingBar = Node::create();
	staticUI->addChild(buyingBar,1);

	//Button lên xuống
	auto widthOfBuyingBar = 0.05;
	auto maxHeightOfBuyingBar = 0.7;
	auto minHeightOfBuyingBar = 0.4;

	btn_SwitchBuyingBar = Tool::CreateButtonWithoutSprite("btn_SwitchBuyingBar", "<", Tool::defaultTextSize * 2);
	btn_SwitchBuyingBar->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	btn_SwitchBuyingBar->setPosition(Vec2(visibleSize.width*(widthOfBuyingBar + 0.2), visibleSize.height*(maxHeightOfBuyingBar + distanceBetweenItems)));
	buyingBar->addChild(btn_SwitchBuyingBar, 1);

	auto btn_Buying_Back = Tool::CreateButtonWithoutSprite("btn_Buying_Back", Tool::ConvertUTF16ToString(L"↑"), Tool::defaultTextSize, Color3B::GREEN);
	btn_Buying_Back->setPosition(Vec2(visibleSize.width*widthOfBuyingBar, visibleSize.height*(maxHeightOfBuyingBar+distanceBetweenItems)));
	btn_Buying_Back->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_Buying_Back);

	auto btn_Buying_Next = Tool::CreateButtonWithoutSprite("btn_Buying_Next", Tool::ConvertUTF16ToString(L"↓"), Tool::defaultTextSize, Color3B::GREEN);
	btn_Buying_Next->setPosition(Vec2(visibleSize.width*widthOfBuyingBar, visibleSize.height*(minHeightOfBuyingBar - distanceBetweenItems)));
	btn_Buying_Next->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_Buying_Next);
	
	//Set position
	for (int i = 0; i < List_BuyableObject.size(); i++) {
		List_BuyableObject[i].btn_Upgrade->setPosition(Vec2(visibleSize.width*(widthOfBuyingBar + distanceBetweenItems), visibleSize.height*(maxHeightOfBuyingBar - i * distanceBetweenItems)));
		List_BuyableObject[i].lbl_Cost->setPosition(Vec2(visibleSize.width*(widthOfBuyingBar + distanceBetweenItems*0.5), visibleSize.height*(maxHeightOfBuyingBar - i * distanceBetweenItems)));
		List_BuyableObject[i].btn_Icon->setPosition(Vec2(visibleSize.width*widthOfBuyingBar, visibleSize.height*(maxHeightOfBuyingBar - i * distanceBetweenItems)));
		if (i > numOfVisibleItem - 1) {
			List_BuyableObject[i].lbl_Cost->setVisible(false);
			List_BuyableObject[i].btn_Icon->setVisible(false);
			List_BuyableObject[i].btn_Icon->setEnabled(false);
			List_BuyableObject[i].btn_Upgrade->setVisible(false);
			List_BuyableObject[i].btn_Upgrade->setEnabled(false);
			List_BuyableObject[i].lbl_Cost->runAction(FadeOut::create(0));
			List_BuyableObject[i].btn_Icon->runAction(FadeOut::create(0));
		}
		List_BuyableObject[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyObjectClick, this));
		List_BuyableObject[i].btn_Upgrade->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_UpgradeObjectClick, this));
		buyingBar->addChild(List_BuyableObject[i].item);
	}

	
}
GameScene::Item_BuyableObject::Item_BuyableObject(string name)
{
	/*BaseObjectClass* basicStats = ObjectConstructor::InitializeObject(name, 0, 0, 0);
	this->item = Node::create();
	item->setName(name);
	this->lbl_Cost = Tool::CreateLabel(to_string(basicStats->cost), Tool::defaultTextSize, Color4B::YELLOW);
	this->btn_Icon = Tool::CreateButtonWithoutSprite(name, name);
	
	
	if (basicStats->upgradeTo != "") {
		this->btn_Upgrade = Button::create("HelloWorld.png");
		this->btn_Upgrade->setName(basicStats->objectName);
		Tool::setNodeSize(this->btn_Upgrade, 32, 32);
	}
	else {
		this->btn_Upgrade = Button::create();
		this->btn_Upgrade->setName("Not Available");
		this->btn_Upgrade->setTitleText("Not Available");
	}
	item->addChild(this->lbl_Cost);
	item->addChild(this->btn_Icon);
	item->addChild(this->btn_Upgrade);*/
}

GameScene::IngamePlayer::IngamePlayer()
{
	this->lbl_Gold = Tool::CreateLabel("Gold: " + to_string(this->gold), Tool::defaultTextSize*1.25, Color4B::YELLOW,CCTextAlignment::LEFT);
	this->lbl_Gold->setAnchorPoint(Vec2(0, 0.5));
	this->lbl_Energy = Tool::CreateLabel("Energy: " + to_string(this->energy), Tool::defaultTextSize*1.25, Color4B(Color3B(0,255,255),255), CCTextAlignment::LEFT);
	this->lbl_Energy->setAnchorPoint(Vec2(0, 0.5));
	this->lbl_MainTowerLevel = Tool::CreateLabel("Level: " + to_string(this->mainTowerLevel), Tool::defaultTextSize*1.25, Color4B::GREEN, CCTextAlignment::LEFT);
	this->lbl_MainTowerLevel->setAnchorPoint(Vec2(0, 0.5));
	this->btn_UpgradeMainTower = Tool::CreateButtonWithoutSprite("MainTower1", Tool::ConvertUTF16ToString(L"Up ↑"));
}

void GameScene::Respone_ReadQuestion(cocos2d::network::HttpClient * sender, cocos2d::network::HttpResponse * response)
{
	//Lấy thông tin từ server
	string* a = new string();
	vector <string*> Vec;
	vector<char> *buffer = response->getResponseData();
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		*a = *a + (*buffer)[i];
	}
	Tool::CutString(a, Vec, "@");

	//Gán vào question
	txt_Question->setString(*(Vec[0]));
	lv_QuestionContent->requestDoLayout();

	//Level
	currentQuestionLevel = Tool::ConvertStringToInt(*(Vec[1]));
	lbl_Level->setString([&]() -> string {
		if (currentQuestionLevel == 1) return "easy";
		else if (currentQuestionLevel == 2) return "medium";
		else if (currentQuestionLevel == 3) return "hard";
		else if (currentQuestionLevel == 4) return "extreme";
	}());
	answer = (*(Vec[2]));

	//Button
	btn_Answer1->setTitleText(*(Vec[3]));
	btn_Answer2->setTitleText(*(Vec[4]));
	btn_Answer3->setTitleText(*(Vec[5]));
	btn_Answer4->setTitleText(*(Vec[6]));

	//Thời gian trả lời
	destinationTime = 20 * currentQuestionLevel + Tool::currentIngameTime;
	if (200 == response->getResponseCode())
	{
		//CCLOG("Succeeded");
	}
	else
	{
		//CCLOG("Failed");
	}
}

void GameScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
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
	string dataToSend = "level=" + level;
	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost/Back_End_Game/GameScene/Random_Question.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setRequestData(dataToSend.c_str(), dataToSend.size());
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void GameScene::Request_ReadQuestion()
{
	cocos2d::network::HttpRequest *request = new cocos2d::network::HttpRequest();
	request->setUrl("http://localhost/Back_End_Game/GameScene/Read_Question.php");
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);
	request->setResponseCallback(CC_CALLBACK_2(GameScene::Respone_ReadQuestion, this));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

GameScene::UnitDetails::UnitDetails(BaseUnitClass object, Vec2 position)
{
	this->details = Node::create();

	this->lbl_Name = Tool::CreateLabel("Name " + object.name);
	lbl_Name->setPosition(position);
	details->addChild(lbl_Name);

	this->lbl_Health = Tool::CreateLabel("Health " + to_string(object.currentHealth) + " / " + to_string(object.maxHealth));
	lbl_Health->setPosition(position + Vec2(0,-20));
	details->addChild(lbl_Health);

	this->lbl_Attack = Tool::CreateLabel("Attack " + to_string(object.attack));
	lbl_Attack->setPosition(position + Vec2(0, -40));
	details->addChild(lbl_Attack);

	this->lbl_Defense = Tool::CreateLabel("Defense " + to_string(object.defense));
	lbl_Defense->setPosition(position + Vec2(0, -60));
	details->addChild(lbl_Defense);

	this->lbl_Speed = Tool::CreateLabel("Speed " + to_string(object.moveSpeed));
	lbl_Speed->setPosition(position + Vec2(0, -80));
	details->addChild(lbl_Speed);

	this->lbl_AttackRate = Tool::CreateLabel("Attack Speed " + to_string(object.attackSpeed));
	lbl_AttackRate->setPosition(position + Vec2(0, -100));
	details->addChild(lbl_AttackRate);

}
