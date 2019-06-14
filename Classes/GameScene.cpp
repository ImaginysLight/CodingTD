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

	IngameObject::loadIngameObjectStaticVariables();

	BaseSkillClass::LoadSkillRequirement();

	GameScene::SetupCamera();

	GameScene::SetupGUI();

	GameScene::LoadIngamePlayerInfo();

	IngameObject::loadAnimate();

	isAllowedToChooseQuestion = Player::opponentPlayer->id > Player::currentPlayer->id ? true : false;

	ChangeQuestionTableState(false);


	Tool::Socket_Client->_client->on("Create_Unit", CC_CALLBACK_2(GameScene::onReceiveEvent_InitializeIngameObject, this));
	Tool::Socket_Client->_client->on("Use_Skill", CC_CALLBACK_2(GameScene::onReceiveEvent_ExcuteSkill, this));
	Tool::Socket_Client->_client->on("Send_Message", CC_CALLBACK_2(GameScene::onReceiveEvent_SendMessage, this));
	Tool::Socket_Client->_client->on("_Question_is_", CC_CALLBACK_2(GameScene::onReceiveEvent_Question, this));
	Tool::Socket_Client->_client->on("_Upgrade_Kingdom_", CC_CALLBACK_2(GameScene::onReceiveEvent_UpgradeKingdom, this));
	Tool::Socket_Client->_client->on("Answer_Result", CC_CALLBACK_2(GameScene::onReceiveEvent_AnswerResult, this));
	Tool::Socket_Client->_client->on("Upload_Player_Info", nullptr);

	this->schedule(schedule_selector(GameScene::UpdateIngameObject), 1/60);
	this->schedule(schedule_selector(GameScene::UpdateQuestionInfo), 0.25);
	this->schedule(schedule_selector(GameScene::UpdatePlayerResourcePerSecond), 1);
	this->scheduleUpdate();

	return true;

}

void GameScene::LoadIngamePlayerInfo() {

	//Set label các loại bên góc trái trên
	ingamePlayerInfo.sp_Background = Sprite::create("UI/GameScene/Ingame Player Info.png");
	ingamePlayerInfo.sp_Background->setAnchorPoint(Vec2(0, 1));
	ingamePlayerInfo.sp_Background->setPosition(Vec2(15,visibleSize.height-15));
	staticUI->addChild(ingamePlayerInfo.sp_Background, -1);

	ingamePlayerInfo.lbl_PlayerName = Tool::CreateLabel(Player::currentPlayer->username,Tool::defaultTextSize*0.75);
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

	//Lấy effect Trophy
	auto knowledge = Trophy::CalculateKnowledgeTrophy(Player::currentPlayer->total_correctAnswer);
	ingamePlayerInfo.correctAnswerGoldRate += knowledge.correctGoldRate / 100.0;
	ingamePlayerInfo.wrongAnswerGoldRate += knowledge.wrongGoldRate / 100.0;
	auto battle = Trophy::CalculateBattleTrophy(Player::currentPlayer->total_kill);
	ingamePlayerInfo.defeatGoldRate += battle.defeatGoldRate / 100.0;
	ingamePlayerInfo.defeatEnergyRate = battle.defeatEnergyRate / 1000.0;
	auto conquest = Trophy::CalculateConquestTrophy(Player::currentPlayer->total_win);
	ingamePlayerInfo.Gps += conquest.bonusGold;
	ingamePlayerInfo.Eps += conquest.bonusEnergy;

	//Tạo 2 skill
	if (Player::currentPlayer->elementName == "Ice") {
		ingamePlayerInfo.btn_Skill1 = Tool::CreateButtonWithoutSprite("Cool Blooded", "Cool Blooded", Tool::defaultTextSize*1.25, Color3B(0, 255, 255));
		ingamePlayerInfo.btn_Skill2 = Tool::CreateButtonWithoutSprite("Ice Age", "Ice Age", Tool::defaultTextSize*1.25, Color3B(0, 255, 255));
	}
	else if (Player::currentPlayer->elementName == "Fire") {
		ingamePlayerInfo.btn_Skill1 = Tool::CreateButtonWithoutSprite("Burning Enthusiasm", "Burning Enthusiasm", Tool::defaultTextSize*1.25, Color3B::RED);
		ingamePlayerInfo.btn_Skill2 = Tool::CreateButtonWithoutSprite("Hell Fire", "Hell Fire", Tool::defaultTextSize*1.25, Color3B::RED);
	}
	else if (Player::currentPlayer->elementName == "Nature") {
		ingamePlayerInfo.btn_Skill1 = Tool::CreateButtonWithoutSprite("Natural Wind", "Natural Wind", Tool::defaultTextSize*1.25, Color3B::GREEN);
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
	GameScene::InitializeIngameObject(IngameObject::GetKingdomByElement(Player::currentPlayer->elementName), 1, Player::currentPlayer->id);
	ingamePlayerInfo.kingdom = BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1];
	ingamePlayerInfo.kingdom->root->setPosition(IngameObject::spawnPoint["1_1"]);
	GameScene::InitializeIngameObject(IngameObject::GetKingdomByElement(Player::opponentPlayer->elementName), 1, Player::opponentPlayer->id);
	ingamePlayerInfo.opponentKingdom = BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1];
	ingamePlayerInfo.opponentKingdom->root->setPosition(IngameObject::spawnPoint["2_1"]);

	if(Player::currentPlayer->elementName == "Ice"){
		Player::currentPlayer->picked_units.push_back("Frost Wyvern");
		Player::currentPlayer->picked_units.push_back("Polar Bear");
	}
	else if (Player::currentPlayer->elementName == "Fire") {
		Player::currentPlayer->picked_units.push_back("Volcarona");
		Player::currentPlayer->picked_units.push_back("Enraged Ursa");
	}
	else if (Player::currentPlayer->elementName == "Nature") {
		Player::currentPlayer->picked_units.push_back("Poisonous Butterfly");
		Player::currentPlayer->picked_units.push_back("Vampire Dragon");
	}

	//Tạo thanh mua lính
	for (int i = 0; i < Player::currentPlayer->picked_units.size(); i++) {
		List_BuyableUnit.push_back(Item_BuyableUnit(Player::currentPlayer->picked_units[i]));
	}
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
			if (BaseUnitClass::AllIngameUnit_Vector[i]->description == "Kingdom") {
				GameScene::Endgame(!BaseUnitClass::AllIngameUnit_Vector[i]->isOwned);
				return;
			}
			if (!BaseUnitClass::AllIngameUnit_Vector[i]->isOwned) { 
				ResultScene::numOfEnemyDefeated++;
				ResultScene::goldReceived += BaseUnitClass::AllIngameUnit_Vector[i]->goldCost * ingamePlayerInfo.defeatGoldRate;
				ingamePlayerInfo.gold += BaseUnitClass::AllIngameUnit_Vector[i]->goldCost * ingamePlayerInfo.defeatGoldRate;
				ingamePlayerInfo.energy += BaseUnitClass::AllIngameUnit_Vector[i]->goldCost * ingamePlayerInfo.defeatEnergyRate;
				GameScene::UpdateIngamePlayerInfo();
			}
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

void GameScene::UpdatePlayerResourcePerSecond(float time) {
	ingamePlayerInfo.gold += ingamePlayerInfo.Gps;
	if(ingamePlayerInfo.energy < ingamePlayerInfo.energyCap) ingamePlayerInfo.energy += ingamePlayerInfo.Eps;
	UpdateIngamePlayerInfo();
}

void GameScene::UpdateQuestionInfo(float time) {
	if (destinationTime < Tool::currentIngameTime){
		questionAvailable = false;
		isAllowedToChooseQuestion = !isAllowedToChooseQuestion;
		GameScene::ChangeQuestionTableState(questionAvailable);
		destinationTime += 10;
	}
	if (questionAvailable) {
		btn_DropDownQuestionTable->setTitleText("Question Ready (" + to_string((int)(destinationTime - Tool::currentIngameTime)) + ")");
	}
	else {
		btn_DropDownQuestionTable->setTitleText("Waiting For Next Question (" + to_string((int)(destinationTime - Tool::currentIngameTime)) + ")");
		btn_DropDownQuestionTable->setTitleColor(GameScene::isAllowedToChooseQuestion ? Color3B::GREEN : Color3B::RED);
	}
}

void GameScene::ChangeQuestionTableState(bool questionAvailable) {
	//Ẩn hết tất cả
	Tool::Button_ChangeState(btn_Level1, false, 0.5);
	Tool::Button_ChangeState(btn_Level2, false, 0.5);
	Tool::Button_ChangeState(btn_Level3, false, 0.5);
	Tool::Button_ChangeState(btn_Answer1, false, 0.5);
	Tool::Button_ChangeState(btn_Answer2, false, 0.5);
	Tool::Button_ChangeState(btn_Answer3, false, 0.5);
	Tool::Button_ChangeState(btn_Answer4, false, 0.5);
	if (questionAvailable) { //Nếu có câu hỏi: hiện đáp án
		
		btn_Answer1->setTitleColor(Color3B::WHITE);
		btn_Answer2->setTitleColor(Color3B::WHITE);
		btn_Answer3->setTitleColor(Color3B::WHITE);
		btn_Answer4->setTitleColor(Color3B::WHITE);

		Tool::Button_ChangeState(btn_Answer1, true, 0.5);
		Tool::Button_ChangeState(btn_Answer2, true, 0.5);
		Tool::Button_ChangeState(btn_Answer3, true, 0.5);
		Tool::Button_ChangeState(btn_Answer4, true, 0.5);	
	}
	else { //Nếu không có câu hỏi và được chọn độ khó thì hiện btn_Level
		if (isAllowedToChooseQuestion) {
			btn_Level1->setTitleColor(Color3B::WHITE);
			btn_Level2->setTitleColor(Color3B::WHITE);
			btn_Level3->setTitleColor(Color3B::WHITE);

			Tool::Button_ChangeState(btn_Level1, true, 0.5);
			Tool::Button_ChangeState(btn_Level2, true, 0.5);
			Tool::Button_ChangeState(btn_Level3, true, 0.5);

			txt_Question->setString("Choose difficulty for the next question or it will be random");
		}
		else
			txt_Question->setString("Wait your opponent choose difficulty for the next question");
		lv_QuestionContent->requestDoLayout();
	}
}

void GameScene::InitializeIngameObject(string objectName, int line, int playerId)
{
	//Tạo lính
	bool isOwned = playerId == Player::currentPlayer->id ? true : false;
	BaseUnitClass* object = ObjectConstructor::InitializeObject(objectName, line, isOwned, playerId, ++BaseUnitClass::Unit_Id_Counter);
	BaseUnitClass::AllIngameUnit_Vector.push_back(object);
	this->addChild(object->root, 4 - object->line);

	//Set vị trí random
	if (BaseUnitClass::AllIngameUnit_Vector.size() % 2)
		BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->setPositionY(
			BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->getPositionY()
			+ Tool::CreateRandomNumber(0, 25));
	else 
		BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->setPositionY(
			BaseUnitClass::AllIngameUnit_Vector[BaseUnitClass::AllIngameUnit_Vector.size() - 1]->root->getPositionY()
			+ Tool::CreateRandomNumber(25, 50));

	//Apply passive skill
	if(object->isOwned) PassiveSkill::ApplyPassive(object->unitId, Player::currentPlayer->elementName);
	else PassiveSkill::ApplyPassive(object->unitId, Player::opponentPlayer->elementName);
	
}

void GameScene::Endgame(bool isVictorious)
{
	GameScene::ClearAllVariables();

	ResultScene::isVictorious = isVictorious;

	this->pauseSchedulerAndActions();
	auto lbl_Result = Tool::CreateLabel("", Tool::defaultTextSize*2.5);
	lbl_Result->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height*0.55));
	staticUI->addChild(lbl_Result,69);

	auto btn_Comfirm = Tool::CreateButtonWithoutSprite("btn_Confirm", "Confirm");
	btn_Comfirm->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.45));
	btn_Comfirm->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	staticUI->addChild(btn_Comfirm,69);

	if (isVictorious) {
		lbl_Result->setString("You are Victorious!");
		lbl_Result->setTextColor(Color4B(175,225,200,255));
	}
	else {
		lbl_Result->setString("You are Defeated");
		lbl_Result->setTextColor(Color4B::RED);
	}
}

void GameScene::ClearAllVariables()
{
	BaseUnitClass::AllIngameUnit_Vector.clear();
	BaseUnitClass::Unit_Id_Counter = 0;
	Player::opponentPlayer = new PlayerInfo();
	Player::currentPlayer->elementName = "";
	Player::currentPlayer->picked_units.clear();
}

void GameScene::onReceiveEvent_InitializeIngameObject(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		GameScene::InitializeIngameObject(document["name"].GetString(), Tool::ConvertStringToInt(document["line"].GetString()), Tool::ConvertStringToInt(document["id"].GetString()));
	}
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
			//if (isAllowedToChooseQuestion) {
				nextQuestionLevel = name.substr(name.size() - 1, 1);
				std::string Send_Level;
				if (name == "btn_Level1") {
					Send_Level = "{\"Room\":\"" + Player::currentPlayer->room_name + "\" ,\"Level\":\"1\"}";
					CCLOG("Easy");
				}
				if (name == "btn_Level2") {
					Send_Level = "{\"Room\":\"" + Player::currentPlayer->room_name + "\" ,\"Level\":\"2\"}";
					CCLOG("Medium");
				}
				if (name == "btn_Level3")
				{
					Send_Level = "{\"Room\":\"" + Player::currentPlayer->room_name + "\" ,\"Level\":\"3\"}";
					CCLOG("Hard");
				}
				Tool::Socket_Client->_client->emit("_Level_", Send_Level);
				nextQuestionLevel = name.substr(name.size() - 1, 1);
				((Button*)pSender)->setTitleColor(Color3B::GREEN);
			//}
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
		else if (name == "btn_Confirm") {
			Player::oldPlayerInfo = *Player::currentPlayer;
			Player::currentPlayer->total_correctAnswer += ResultScene::numOfCorrectAnswer;
			Player::currentPlayer->total_wrongAnswer += ResultScene::numOfWrongAnswer;
			Player::currentPlayer->total_kill += ResultScene::numOfEnemyDefeated;
			float questionPoint = (ResultScene::numOfCorrectAnswer + ResultScene::numOfWrongAnswer)*(0.5 + ResultScene::numOfCorrectAnswer / (float)(ResultScene::numOfWrongAnswer + ResultScene::numOfCorrectAnswer) * 2);
			float battlePoint = ResultScene::goldReceived *0.01;
			int bonusExp = (questionPoint + battlePoint) * (ResultScene::isVictorious ? 1.3 : 0.8);
			Player::currentPlayer->experience += bonusExp;
			ResultScene::isVictorious ? (Player::currentPlayer->total_win++) : (Player::currentPlayer->total_lose++);
			Player::UploadPlayerInfo(Player::currentPlayer);
			Director::getInstance()->replaceScene(ResultScene::createScene());
		}
	}
}

void GameScene::btn_ExecuteSkill_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		auto btn = (Button*)pSender;
		if (GameScene::CheckSkillCondition(name)) {
			//SkillConstructor::InitializeSkill(name, 0, 0, Player::currentPlayer->id, GameScene::choosingUnit->unitId);
			Tool::Socket_Client->_client->emit("Use_Skill", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"name\":\"" + name + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\", \"unitId\":\"" + to_string(GameScene::choosingUnit->unitId) + "\"}");
		}
	}
}

void GameScene::onReceiveEvent_ExcuteSkill(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		SkillConstructor::InitializeSkill(document["name"].GetString(), 0, 0, Tool::ConvertStringToInt(document["id"].GetString()), Tool::ConvertStringToInt(document["unitId"].GetString()));
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
		if (GameScene::choosingUnit->ownerPlayerId != Player::currentPlayer->id) {
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

	auto _background = Sprite::create("UI/GameScene/static background.png");
	_background->setPosition(visibleSize/2);
	staticUI->addChild(_background, -1);

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

	auto sp_Background = Sprite::create("UI/GameScene/Buying Bar Background.png");
	buyingBar->addChild(sp_Background, -1);
	sp_Background->setPositionX(visibleSize.width / 2);
	sp_Background->setAnchorPoint(Vec2(0.5, 0));

	GameScene::btn_Mode = Tool::CreateButtonWithoutSprite("btn_Mode", "Buy");
	btn_Mode->setPosition(Vec2(visibleSize.width*0.24, visibleSize.height*0.05));
	btn_Mode->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_Mode,2);

	GameScene::btn_CloseViewDetail = Tool::CreateButtonWithoutSprite("btn_CloseViewDetail", "Close", Tool::defaultTextSize, Color3B::RED);
	btn_CloseViewDetail->setPosition(visibleSize*0.85);
	Tool::Button_ChangeState(btn_CloseViewDetail, false, 0);
	btn_CloseViewDetail->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	staticUI->addChild(btn_CloseViewDetail,1);

	ingamePlayerInfo.btn_UpgradeKingdom = Tool::CreateButtonWithoutSprite(IngameObject::GetKingdomByElement(Player::currentPlayer->elementName), Tool::ConvertUTF16ToString(L"Up ↑"));
	ingamePlayerInfo.btn_UpgradeKingdom->setPosition(Vec2(visibleSize.width*0.755, visibleSize.height*0.05));
	ingamePlayerInfo.btn_UpgradeKingdom->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_UpgradeKingdom, this));
	buyingBar->addChild(ingamePlayerInfo.btn_UpgradeKingdom);
	this->buyingBar->addChild(ghostItem);
	for (int i = 0; i < List_BuyableUnit.size(); i++) {
		this->buyingBar->addChild(List_BuyableUnit[i].root);
		List_BuyableUnit[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyUnit_Click, this));
		AddDragAndDropItem(List_BuyableUnit[i].root);
	}
	List_BuyableUnit[0].root->setPosition(Vec2(visibleSize.width*0.305, visibleSize.height*0.05));
	List_BuyableUnit[1].root->setPosition(Vec2(visibleSize.width*0.37, visibleSize.height*0.05));
	if (List_BuyableUnit.size() > 2)
		List_BuyableUnit[2].root->setPosition(Vec2(visibleSize.width*0.435, visibleSize.height*0.05));
	if (List_BuyableUnit.size() > 3)
		List_BuyableUnit[3].root->setPosition(Vec2(visibleSize.width*0.56, visibleSize.height*0.05));
	if (List_BuyableUnit.size() > 4)
		List_BuyableUnit[4].root->setPosition(Vec2(visibleSize.width*0.625, visibleSize.height*0.05));
	if (List_BuyableUnit.size() > 5)
		List_BuyableUnit[5].root->setPosition(Vec2(visibleSize.width*0.69, visibleSize.height*0.05));
	
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
	auto unitDetail = ObjectConstructor::InitializeObject(name, 0, 0, 0, -1);
	if (ingamePlayerInfo.kingdomLevel < unitDetail->levelRequired) {
		RunActionNotify("Requried Kingdom Level " + to_string(unitDetail->levelRequired));
	}
	else if (ingamePlayerInfo.gold < unitDetail->goldCost) {
		RunActionNotify("Not enough gold!");
	}
	else {
		//GameScene::InitializeIngameObject(name, line, Player::currentPlayer->id);
		Tool::Socket_Client->_client->emit("Create_Unit", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"name\":\"" + name + "\", \"line\":\"" + to_string(line) + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
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
		unitDetails = *ObjectConstructor::InitializeObject(name, 0, 0, 0, -1);
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
	else unitDetails = *ObjectConstructor::InitializeObject(name, 0, 0, 0,-1);
	if (ingamePlayerInfo.kingdomLevel < unitDetails.upgradeLevelRequired) {
		RunActionNotify("Requried Kingdom Level " + to_string(unitDetails.upgradeLevelRequired));
	}
	else if (ingamePlayerInfo.gold < unitDetails.upgradeGoldCost || ingamePlayerInfo.knowledge < unitDetails.upgradeKnowledgeCost) {
		RunActionNotify("Not enough resource!");
	}
	else {
		//Upgrade Kingdom
		if (unitDetails.description == "Kingdom") {
			Tool::Socket_Client->_client->emit("_Upgrade_Kingdom_", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"Id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
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
	this->unitInfo = ObjectConstructor::InitializeObject(name, 0, 0, 0, -1);
	this->root = Node::create();
	if (unitInfo != nullptr) {
		this->btn_Icon = Button::create("Sprites/" + this->unitInfo->animateName + "/card.png");
		this->btn_Icon->setName(unitInfo->name);
		Tool::setNodeSize(btn_Icon, 80, 80);
		this->btn_Icon->setPositionY(18);

		this->lbl_Cost = Tool::CreateLabel(to_string(unitInfo->goldCost), Tool::defaultTextSize*0.8, Color4B::YELLOW);
		this->lbl_Cost->enableBold();
		this->lbl_Cost->setPositionY(-18);

		this->root->addChild(btn_Icon);
		this->root->addChild(lbl_Cost);
	}
}

void GameScene::CreateChatbox() {
	
	GameScene::sc_ChatBox = ui::ScrollView::create();
	sc_ChatBox->setContentSize(Size(visibleSize.width*0.285, visibleSize.height*0.25));
	sc_ChatBox->setInnerContainerSize(Size(1000, 200));
	sc_ChatBox->setPosition(Vec2(visibleSize.width*0.985,visibleSize.height*0.25));
	sc_ChatBox->setAnchorPoint(Vec2(1, 0));
	sc_ChatBox->setBounceEnabled(true);
	staticUI->addChild(sc_ChatBox,10);

	auto sp_ChatBox = Sprite::create("UI/GameScene/bgchat.png");
	sp_ChatBox->setPosition(sc_ChatBox->getPosition());
	sp_ChatBox->setAnchorPoint(Vec2(1, 0));
	Tool::setNodeSize(sp_ChatBox, 285, 135);
	staticUI->addChild(sp_ChatBox, 9);

	GameScene::EditBox_Chat = ui::EditBox::create(Size(visibleSize.width*0.255, visibleSize.height*0.06), "", "");
	EditBox_Chat->setPosition(Vec2(visibleSize.width*0.95,visibleSize.height*0.2));
	EditBox_Chat->setAnchorPoint(Vec2(1, 0));
	EditBox_Chat->setTextHorizontalAlignment(TextHAlignment::LEFT);
	EditBox_Chat->setInputMode(EditBox::InputMode::ANY);
	EditBox_Chat->setFontSize(Tool::defaultTextSize);
	EditBox_Chat->setFontColor(Color3B(175, 225, 200));
	EditBox_Chat->setPlaceHolder("Message");
	EditBox_Chat->setPlaceholderFontColor(Color3B::GRAY);
	EditBox_Chat->setMaxLength(100);
	staticUI->addChild(EditBox_Chat,10);

	auto sp_EditBox = Sprite::create("UI/GameScene/bgEditBox.png");
	sp_EditBox->setPosition(EditBox_Chat->getPosition());
	sp_EditBox->setAnchorPoint(Vec2(1, 0));
	Tool::setNodeSize(sp_EditBox, EditBox_Chat->getBoundingBox().size.width, EditBox_Chat->getBoundingBox().size.height);
	staticUI->addChild(sp_EditBox, 9);
	

	GameScene::btn_SendMessage = Button::create("UI/GameScene/Send Message.png");
	btn_SendMessage->setAnchorPoint(Vec2(1, 0));
	btn_SendMessage->setPosition(Vec2(visibleSize.width*0.98, visibleSize.height*0.2));
	btn_SendMessage->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_SendMessage_Click, this));
	staticUI->addChild(btn_SendMessage);

	chatBoxContent.push_back("ImaginysLight and AnhQuyetVo welcome you to Coding TD !");
	UpdateChatbox();
	

}
void GameScene::UpdateChatbox() {
	vector<int> labelHeight;
	int currentHeight = 10;
	sc_ChatBox->removeAllChildrenWithCleanup(true);
	sc_ChatBox->scrollToBottom(0, false);
	for (int i = 0; i < chatBoxContent.size(); i++) {
		Label* lbl_Content = Tool::CreateLabel(chatBoxContent[i],Tool::defaultTextSize*0.8);
		lbl_Content->setMaxLineWidth(sc_ChatBox->getContentSize().width*0.9);
		currentHeight += (lbl_Content->getBoundingBox().size.height / 2);
		labelHeight.push_back(currentHeight);
		currentHeight += (8 + lbl_Content->getBoundingBox().size.height / 2);
	}
	sc_ChatBox->setInnerContainerSize(Size(1000, currentHeight + 20));
	for (int i = 0; i < chatBoxContent.size(); i++) {
		Label* lbl_Content = Tool::CreateLabel(chatBoxContent[i], Tool::defaultTextSize*0.8);
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
		content = Player::currentPlayer->username + ": " + content;
		for (int i = 0; i < content.size(); i++) {
			if (content[i] == '\\') {
				content[i] = '/';
			}
		}
		Tool::Socket_Client->_client->emit("Send_Message", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"content\":\"" + content + "\"}");
		GameScene::EditBox_Chat->setText("");
	}
}
void GameScene::onReceiveEvent_SendMessage(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		GameScene::chatBoxContent.push_back(document["content"].GetString());
		GameScene::UpdateChatbox();
	}
}

void GameScene::onReceiveEvent_UpgradeKingdom(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["Id"].GetString())) {
			ingamePlayerInfo.kingdom->Upgrade();
			ingamePlayerInfo.kingdomLevel++;
			ingamePlayerInfo.lbl_KingdomLevel->setString(to_string(ingamePlayerInfo.kingdomLevel));
			ingamePlayerInfo.btn_UpgradeKingdom->setName(ingamePlayerInfo.kingdom->name);
			ingamePlayerInfo.energyCap += 25;
		}
		else {
			ingamePlayerInfo.opponentKingdom->Upgrade();
		}
	}
}

void GameScene::onReceiveEvent_AnswerResult(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		string content;
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString())) {
			content = Player::currentPlayer->username;
			PassiveSkill::Improve(Player::currentPlayer->elementName);
		}
		else {
			content = Player::opponentPlayer->username;
			PassiveSkill::Improve(Player::opponentPlayer->elementName);
		}
		content += " made a ";
		content += document["result"].GetString();
		content += " in ";
		content += document["time"].GetString();
		content += " seconds remain.";
		chatBoxContent.push_back(content);
		GameScene::UpdateChatbox();

		
	}
}

void GameScene::CreateQuestionTable()
{
	questionTable = Node::create();
	questionTable->setVisible(false);
	questionTable->setPosition(visibleSize / 2);
	questionTable->runAction(MoveBy::create(0, Vec2(0, visibleSize.height)));
	staticUI->addChild(questionTable, 2);

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
			GameScene::WrongAnswer();
			((Button*)pSender)->setTitleColor(Color3B::RED);
		}
	}
}



void GameScene::onReceiveEvent_Question(SIOClient* client, const std::string& data) {

	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Room"))
	{
		if (document["Room"].GetString() == Player::currentPlayer->room_name)
		{
			CCLOG("Room: %s ", document["Room"].GetString());
			if (document.HasMember("id")) { CCLOG("id: %d ", document["id"].GetInt()); }
			if (document.HasMember("content")) {
				CCLOG("content: %s ", document["content"].GetString());
				//questionContent = document["content"].GetString();
				txt_Question->setString(document["content"].GetString());
				lv_QuestionContent->requestDoLayout();
			}
			if (document.HasMember("level")) {
				CCLOG("level: %s ", document["level"].GetString());
				currentQuestionLevel = Tool::ConvertStringToInt(document["level"].GetString());
				lbl_Level->setString([&]() -> string {
					if (currentQuestionLevel == 1) return "easy";
					else if (currentQuestionLevel == 2) return "medium";
					else if (currentQuestionLevel == 3) return "hard";
					else if (currentQuestionLevel == 4) return "extreme";
				}());
			}

			//answer true
			if (document.HasMember("answer")) {
				CCLOG("answer: %s ", document["answer"].GetString());
				answer = document["answer"].GetString();
			}
			//answer
			if (document.HasMember("answer1")) {
				CCLOG("answer 1: %s ", document["answer1"].GetString());
				btn_Answer1->setTitleText(document["answer1"].GetString());
			}
			if (document.HasMember("answer2")) {
				CCLOG("answer 2: %s ", document["answer2"].GetString());
				btn_Answer2->setTitleText(document["answer2"].GetString());
			}//hjhj
			if (document.HasMember("answer3")) {
				CCLOG("answer 3: %s ", document["answer3"].GetString());
				btn_Answer3->setTitleText(document["answer3"].GetString());
			}
			if (document.HasMember("answer4")) {
				CCLOG("answer 4: %s ", document["answer4"].GetString());
				btn_Answer4->setTitleText(document["answer4"].GetString());
				
			}
			questionAvailable = true;
			GameScene::ChangeQuestionTableState(true);
			destinationTime = 20 * currentQuestionLevel + Tool::currentIngameTime;
		}
	}
};


void GameScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(0.5), nullptr));
}

void GameScene::UpdateIngamePlayerInfo()
{
	ingamePlayerInfo.lbl_Gold->setString(to_string((int)ingamePlayerInfo.gold));
	ingamePlayerInfo.lbl_Knowledge->setString(to_string((int)ingamePlayerInfo.knowledge));
	auto temp = CCString::createWithFormat("%.1f", ingamePlayerInfo.energy);
	ingamePlayerInfo.lbl_Energy->setString(temp->getCString());
}

void GameScene::CorrectAnswer()
{
	ResultScene::numOfCorrectAnswer++;

	//( 1 + TimeRemaining % / 1.5) * QuestionLevel * 100 ) Gold và 1 Knowledge cho câu đúng,
	auto TimeRemaining = destinationTime - Tool::currentIngameTime;
	auto QuestionTime = currentQuestionLevel * 20;
	auto TimeRemainingPercent = TimeRemaining / QuestionTime;
	ingamePlayerInfo.gold += (1 + TimeRemainingPercent / 1.8)*currentQuestionLevel * 100 * ingamePlayerInfo.correctAnswerGoldRate;
	ingamePlayerInfo.knowledge += 1;
	GameScene::UpdateIngamePlayerInfo();

	Tool::Socket_Client->_client->emit("Answer_Result", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\", \"result\":\"" + "Correct Answer" + "\", \"time\":\"" + to_string((int)(destinationTime - Tool::currentIngameTime)) + "\"}");
}

void GameScene::WrongAnswer()
{
	ResultScene::numOfWrongAnswer++;

	//( 1 + TimeRemaining % / 1.5) * QuestionLevel * 100 ) * Rand[0.2 , 0.6] Gold cho câu sai.
	auto TimeRemaining = destinationTime - Tool::currentIngameTime;
	auto QuestionTime = currentQuestionLevel * 20;
	auto TimeRemainingPercent = TimeRemaining / QuestionTime;
	auto randomNumber = Tool::CreateRandomNumber(2, 6) / 10.0;
	ingamePlayerInfo.gold += (1 + TimeRemainingPercent / 1.8)*currentQuestionLevel * 100 * randomNumber * ingamePlayerInfo.wrongAnswerGoldRate;
	GameScene::UpdateIngamePlayerInfo();

	Tool::Socket_Client->_client->emit("Answer_Result", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\", \"result\":\"" + "Wrong Answer" + "\", \"time\":\"" + to_string((int)(destinationTime - Tool::currentIngameTime)) + "\"}");
}

void GameScene::ShowUnitDetails()
{
	auto details = UnitDetailsTable(*GameScene::choosingUnit, Vec2(visibleSize.width*0.9, visibleSize.height*0.8));
	GameScene::unitDetails->removeAllChildrenWithCleanup(true);
	GameScene::unitDetails->addChild(details.root);
}
