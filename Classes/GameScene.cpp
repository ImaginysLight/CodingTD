#include"GameScene.h"
#include"Global Class/Audio.h"
using namespace CocosDenshion;
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

	Player::currentPlayer->elementName = Player::opponentPlayer->elementName = "Fire";
	Player::currentPlayer->picked_units.push_back("Elemental Alien");
	Player::currentPlayer->picked_units.push_back("Elemental Alien");
	Player::currentPlayer->picked_units.push_back("Elemental Alien");
	Player::currentPlayer->username = "ImaginysLight";

	Audio::audio->stopAllEffects();

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
	Tool::Socket_Client->_client->on("Receive_Question", CC_CALLBACK_2(GameScene::onReceiveEvent_Question, this));
	Tool::Socket_Client->_client->on("_Upgrade_Kingdom_", CC_CALLBACK_2(GameScene::onReceiveEvent_UpgradeKingdom, this));
	Tool::Socket_Client->_client->on("Answer_Result", CC_CALLBACK_2(GameScene::onReceiveEvent_AnswerResult, this));
	Tool::Socket_Client->_client->on("Active_Bet", CC_CALLBACK_2(GameScene::onReceiveEvent_ActiveBet, this));
	Tool::Socket_Client->_client->on("Upload_Player_Info", nullptr);

	this->schedule(schedule_selector(GameScene::UpdateIngameObject), 1/60);
	this->schedule(schedule_selector(GameScene::UpdateQuestionInfo), 0.25);
	this->schedule(schedule_selector(GameScene::UpdatePlayerResourcePerSecond), 1);
	this->schedule(schedule_selector(GameScene::UpdateAudio), 1);
	this->scheduleUpdate();

	return true;

}

void GameScene::LoadIngamePlayerInfo() {

	//Set label các loại bên góc trái trên
	

	ingamePlayerInfo.root = Node::create();
	staticUI->addChild(ingamePlayerInfo.root);

	ingamePlayerInfo.sp_Background = Sprite::create("UI/GameScene/Player Info Background.png");
	Tool::setNodeSize(ingamePlayerInfo.sp_Background, 250, 150);
	ingamePlayerInfo.sp_Background->setAnchorPoint(Vec2(0, 1));
	ingamePlayerInfo.sp_Background->setPosition(Vec2(visibleSize.width*0.02, visibleSize.height*0.98));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.sp_Background);

	ingamePlayerInfo.lbl_PlayerName = Tool::CreateLabel(Player::currentPlayer->username,Tool::defaultTextSize*0.95);
	ingamePlayerInfo.lbl_PlayerName->enableBold();
	ingamePlayerInfo.lbl_PlayerName->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_PlayerName->setPosition(Vec2(visibleSize.width*0.03, visibleSize.height*0.92));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.lbl_PlayerName, 1);

	ingamePlayerInfo.sp_KingdomLevel = Sprite::create("UI/GameScene/kingdomLevel.png");
	Tool::setNodeSize(ingamePlayerInfo.sp_KingdomLevel, 32, 32);
	ingamePlayerInfo.sp_KingdomLevel->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.92));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.sp_KingdomLevel, 1);

	ingamePlayerInfo.lbl_KingdomLevel = Tool::CreateLabel(to_string(ingamePlayerInfo.kingdomLevel), Tool::defaultTextSize, Color4B::GREEN, TextHAlignment::LEFT);
	ingamePlayerInfo.lbl_KingdomLevel->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_KingdomLevel->setPosition(Vec2(visibleSize.width*0.22, visibleSize.height*0.92));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.lbl_KingdomLevel,1);

	ingamePlayerInfo.sp_Gold = Sprite::create("UI/GameScene/gold.png");
	Tool::setNodeSize(ingamePlayerInfo.sp_Gold, 32, 32);
	ingamePlayerInfo.sp_Gold->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.85));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.sp_Gold, 1);

	ingamePlayerInfo.lbl_Gold = Tool::CreateLabel(to_string(ingamePlayerInfo.gold), Tool::defaultTextSize, Color4B::YELLOW, TextHAlignment::LEFT);
	ingamePlayerInfo.lbl_Gold->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Gold->setPosition(Vec2(visibleSize.width*0.07, visibleSize.height*0.85));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.lbl_Gold);

	ingamePlayerInfo.sp_Energy = Sprite::create("UI/GameScene/energy.png");
	Tool::setNodeSize(ingamePlayerInfo.sp_Energy, 32, 32);
	ingamePlayerInfo.sp_Energy->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.85));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.sp_Energy, 1);

	ingamePlayerInfo.lbl_Energy = Tool::CreateLabel(to_string(ingamePlayerInfo.energy), Tool::defaultTextSize, Color4B(Color3B(175, 225, 250), 255), TextHAlignment::LEFT);
	ingamePlayerInfo.lbl_Energy->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Energy->setPosition(Vec2(visibleSize.width*0.17, visibleSize.height*0.85));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.lbl_Energy);

	ingamePlayerInfo.sp_Knowledge = Sprite::create("UI/GameScene/knowledge.png");
	Tool::setNodeSize(ingamePlayerInfo.sp_Knowledge, 32, 32);
	ingamePlayerInfo.sp_Knowledge->setPosition(Vec2(visibleSize.width*0.05, visibleSize.height*0.78));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.sp_Knowledge, 1);

	ingamePlayerInfo.lbl_Knowledge = Tool::CreateLabel(to_string(ingamePlayerInfo.knowledge), Tool::defaultTextSize, Color4B(Color3B(175, 225, 200), 255), TextHAlignment::LEFT);
	ingamePlayerInfo.lbl_Knowledge->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Knowledge->setPosition(Vec2(visibleSize.width*0.07, visibleSize.height*0.78));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.lbl_Knowledge);

	ingamePlayerInfo.sp_Food = Sprite::create("UI/GameScene/food.png");
	Tool::setNodeSize(ingamePlayerInfo.sp_Food, 25, 25);
	ingamePlayerInfo.sp_Food->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.78));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.sp_Food, 1);

	ingamePlayerInfo.lbl_Food = Tool::CreateLabel("0 / 5", Tool::defaultTextSize, Color4B::RED);
	ingamePlayerInfo.lbl_Food->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.lbl_Food->setPosition(Vec2(visibleSize.width*0.17, visibleSize.height*0.78));
	ingamePlayerInfo.root->addChild(ingamePlayerInfo.lbl_Food);

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
		ingamePlayerInfo.btn_Skill1 = Button::create("Skill/Cold Blooded.png");
		ingamePlayerInfo.btn_Skill1->setName("Cool Blooded");
		ingamePlayerInfo.btn_Skill1->setTitleText("Cold Blooded: Give an ally a power of Ice, halved their Move Speed and Attack but double Health and Defense. 20 Energy");

		ingamePlayerInfo.btn_Skill2 = Button::create("Skill/Cold Blooded.png");
		ingamePlayerInfo.btn_Skill2->setName("Icy Soul");
		ingamePlayerInfo.btn_Skill2->setTitleText("Icy Soul: Level 0: +5% Health and 5% Defense");

		ingamePlayerInfo.btn_Skill3 = Button::create("Skill/Ice Age.png");
		ingamePlayerInfo.btn_Skill3->setName("Ice Age");
		ingamePlayerInfo.btn_Skill3->setTitleText("Ice Age: Freeze all enemies in Ice, stun them for 4 seconds and deal damage inversely proportional to their Attack Speed and proportional to their Attack. 100 Energy");

	}
	else if (Player::currentPlayer->elementName == "Fire") {
		ingamePlayerInfo.btn_Skill1 = Button::create("Skill/Burning Enthusiasm.png");
		ingamePlayerInfo.btn_Skill1->setName("Burning Enthusiasm");
		ingamePlayerInfo.btn_Skill1->setTitleText("Burning Enthusiasm: Give an ally a power of Fire, double their Attack but receive pure damage equal to 10% of that bonus each second. 15 Energy");

		ingamePlayerInfo.btn_Skill2 = Button::create("Skill/Burning Enthusiasm.png");
		ingamePlayerInfo.btn_Skill2->setName("Fiery Spirit");
		ingamePlayerInfo.btn_Skill2->setTitleText("Fiery Spirit: Level 0: +17% Attack");

		ingamePlayerInfo.btn_Skill3 = Button::create("Skill/Hell Fire.png");
		ingamePlayerInfo.btn_Skill3->setName("Hell Fire");
		ingamePlayerInfo.btn_Skill3->setTitleText("Hell Fire: Burn down all enemies with hell fire, dealt damage proportional to your army's Attack each second for 4 seconds. 90 Energy");

	}
	else if (Player::currentPlayer->elementName == "Nature") {
		ingamePlayerInfo.btn_Skill1 = Button::create("Skill/Natural Wind.png");
		ingamePlayerInfo.btn_Skill1->setName("Natural Wind");
		ingamePlayerInfo.btn_Skill1->setTitleText("Natural Wind: Give an ally a power of Nature, immediately increase Attack Speed by 10, then increase by 1 each second for 20 seconds. 15 Energy");

		ingamePlayerInfo.btn_Skill2 = Button::create("Skill/Natural Wind.png");
		ingamePlayerInfo.btn_Skill2->setName("Pure Heart");
		ingamePlayerInfo.btn_Skill2->setTitleText("Pure Heart: Level 0: +2 Regeneration and 8 Attack Speed");

		ingamePlayerInfo.btn_Skill3 = Button::create("Skill/Heaven Bless.png");
		ingamePlayerInfo.btn_Skill3->setName("Heaven Bless");
		ingamePlayerInfo.btn_Skill3->setTitleText("Heaven Bless: Encourage all allies with a bless from heaven, increase current Health and max Health by 250. 80 Energy");
	}
	ingamePlayerInfo.btn_Skill1->setPosition(Vec2(visibleSize.width*0.03, visibleSize.height*0.6));
	ingamePlayerInfo.btn_Skill1->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.btn_Skill1->setTitleFontSize(0);
	Tool::setNodeSize(ingamePlayerInfo.btn_Skill1, 50, 50);
	ingamePlayerInfo.btn_Skill1->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_ExecuteSkill_Click, this));
	staticUI->addChild(ingamePlayerInfo.btn_Skill1);

	ingamePlayerInfo.btn_Skill2->setPosition(Vec2(visibleSize.width*0.03, visibleSize.height*0.5));
	ingamePlayerInfo.btn_Skill2->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.btn_Skill2->setTitleFontSize(0);
	Tool::setNodeSize(ingamePlayerInfo.btn_Skill2, 50, 50);
	staticUI->addChild(ingamePlayerInfo.btn_Skill2);

	ingamePlayerInfo.btn_Skill3->setPosition(Vec2(visibleSize.width*0.03, visibleSize.height*0.4));
	ingamePlayerInfo.btn_Skill3->setAnchorPoint(Vec2(0, 0.5));
	ingamePlayerInfo.btn_Skill3->setTitleFontSize(0);
	Tool::setNodeSize(ingamePlayerInfo.btn_Skill3, 50, 50);
	ingamePlayerInfo.btn_Skill3->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_ExecuteSkill_Click, this));
	staticUI->addChild(ingamePlayerInfo.btn_Skill3);

	

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
		List_BuyableUnit.push_back(Item_BuyableUnit(Player::currentPlayer->picked_units[i] + " 1"));
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

void GameScene::UpdateAudio(float time)
{
	if (!Audio::audio->isBackgroundMusicPlaying()) {
		Audio::audio->playBackgroundMusic(Audio::GetBackgroundAudio().c_str(), false);
	}
}

void GameScene::UpdateQuestionInfo(float time) {
	if (destinationTime < Tool::currentIngameTime){
		if (questionAvailable || questionContent == "") {
			questionAvailable = false;
			isAllowedToChooseQuestion = !isAllowedToChooseQuestion;
			GameScene::ChangeQuestionTableState(questionAvailable);
			destinationTime += 10;
			lbl_Level->setString("???");
		}
		else {
			questionAvailable = true;
			GameScene::ChangeQuestionTableState(true);
			destinationTime = 10 + 10 * currentQuestionLevel + Tool::currentIngameTime;
		}
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
		txt_Question->setString(questionContent);
		lv_QuestionContent->requestDoLayout();
		questionContent = "";

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
	//Play nhạc
	Audio::audio->playEffect(Audio::GetSpawnAudio().c_str(), false);

	//Tạo lính
	bool isOwned = playerId == Player::currentPlayer->id ? true : false;
	BaseUnitClass* object = ObjectConstructor::InitializeObject(objectName, line, isOwned, playerId, ++BaseUnitClass::Unit_Id_Counter);
	BaseUnitClass::AllIngameUnit_Vector.push_back(object);
	this->addChild(object->root, 4 - object->line);

	//Thêm food
	if (isOwned) { ingamePlayerInfo.food++; GameScene::UpdateIngamePlayerInfo(); }

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

	Player::oldPlayerInfo = *Player::currentPlayer;
	Player::currentPlayer->total_correctAnswer += ResultScene::numOfCorrectAnswer;
	Player::currentPlayer->total_wrongAnswer += ResultScene::numOfWrongAnswer;
	Player::currentPlayer->total_kill += ResultScene::numOfEnemyDefeated;
	float questionPoint = (ResultScene::numOfCorrectAnswer + ResultScene::numOfWrongAnswer)*(0.5 + ResultScene::numOfCorrectAnswer / (float)(ResultScene::numOfWrongAnswer + ResultScene::numOfCorrectAnswer) * 2);
	if (questionPoint != questionPoint) questionPoint = 0;
	float battlePoint = ResultScene::goldReceived *0.01;
	int bonusExp = (questionPoint + battlePoint) * (ResultScene::isVictorious ? 1.3 : 0.8);
	Player::currentPlayer->experience += bonusExp;
	ResultScene::isVictorious ? (Player::currentPlayer->total_win++) : (Player::currentPlayer->total_lose++);

	if (Player::CalculateLevel(Player::oldPlayerInfo.experience).first < Player::CalculateLevel(Player::currentPlayer->experience).first)
		Player::currentPlayer->friendshipPoint++;

	Player::UploadPlayerInfo(Player::currentPlayer);

	//Play nhạc
	Audio::audio->stopAllEffects();
	if (isVictorious) Audio::audio->playBackgroundMusic(Audio::GetBrightAudio().c_str(), false);
	else Audio::audio->playBackgroundMusic(Audio::GetSadAudio().c_str(), false);
	
}

void GameScene::ClearAllVariables()
{
	BaseUnitClass::AllIngameUnit_Vector.clear();
	BaseUnitClass::Unit_Id_Counter = 0;
	Player::opponentPlayer = new PlayerInfo();
	Player::currentPlayer->elementName = "";
	Player::currentPlayer->picked_units.clear();
	Player::currentPlayer->room_name = "";
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
				auto level = name.substr(name.size() - 1, 1);
				Tool::Socket_Client->_client->emit("Get_Question", "{\"Room\":\"" + Player::currentPlayer->room_name + "\" ,\"Level\":\"" + level + "\"}");
				((Button*)pSender)->setTitleColor(Color3B::GREEN);
		}
		else if (name == "btn_TurnOnUpgrade") {
			if (GameScene::BuyingBarMode == "Buy") BuyingBarMode = "Upgrade";
			else BuyingBarMode = "Buy";
			GameScene::ChangeUpgradeState();
		}
		else if (name == "btn_Confirm") {
			Director::getInstance()->replaceScene(ResultScene::createScene());
		}
		else if (name == "btn_PositiveBet" || name == "btn_NegativeBet") {
			if (Player::currentPlayer->betNegative || Player::currentPlayer->betPositive) {
				RunActionNotify("You activated bet already!");
				return;
			}
			if (ingamePlayerInfo.gold >= 100) {
				if (name == "btn_PositiveBet") {
					Tool::Socket_Client->_client->emit("Active_Bet", "{\"Room\":\"" + Player::currentPlayer->room_name + "\" ,\"id\":\"" + to_string(Player::currentPlayer->id) + "\",\"betStatus\":\"" + "Positive" + "\"}");
					Player::currentPlayer->betPositive = true;
				}
				if (name == "btn_NegativeBet") {
					Tool::Socket_Client->_client->emit("Active_Bet", "{\"Room\":\"" + Player::currentPlayer->room_name + "\" ,\"id\":\"" + to_string(Player::currentPlayer->id) + "\",\"betStatus\":\"" + "Negative" + "\"}");
					Player::currentPlayer->betNegative = true;
				}
				ingamePlayerInfo.gold -= 100;
			}
			else RunActionNotify("Not enough Gold");
			GameScene::UpdateIngamePlayerInfo();
		}
	}
}

void GameScene::btn_ExecuteSkill_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		auto btn = (Button*)pSender;
		if (GameScene::CheckSkillCondition(name)) {
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

void GameScene::onMouseMove(Event * event)
{
	EventMouse* e = (EventMouse*)event;
	Vec2 point = Vec2(e->getCursorX(), e->getCursorY());
	string tooltipContent = "";
	if (ingamePlayerInfo.btn_Skill1->getBoundingBox().containsPoint(point)) tooltipContent = ingamePlayerInfo.btn_Skill1->getTitleText();
	else if (ingamePlayerInfo.btn_Skill2->getBoundingBox().containsPoint(point)) tooltipContent = ingamePlayerInfo.btn_Skill2->getTitleText();
	else if (ingamePlayerInfo.btn_Skill3->getBoundingBox().containsPoint(point)) tooltipContent = ingamePlayerInfo.btn_Skill3->getTitleText();
	else if (ingamePlayerInfo.sp_KingdomLevel->getBoundingBox().containsPoint(point)) tooltipContent = "Kingdom Level";
	else if (ingamePlayerInfo.sp_Gold->getBoundingBox().containsPoint(point)) tooltipContent = "Gold";
	else if (ingamePlayerInfo.sp_Energy->getBoundingBox().containsPoint(point)) tooltipContent = "Energy";
	else if (ingamePlayerInfo.sp_Knowledge->getBoundingBox().containsPoint(point)) tooltipContent = "Knowledge";
	else if (ingamePlayerInfo.sp_Food->getBoundingBox().containsPoint(point)) tooltipContent = "Food";

	if (tooltipContent != "") {
		GameScene::tooltip->removeAllChildrenWithCleanup(true);
		Label* lbl = Tool::CreateLabel(tooltipContent,Tool::defaultTextSize*0.9);
		if (point.x < visibleSize.width*0.5) {
			lbl->setAnchorPoint(Vec2(0, 0.5));
			lbl->setPositionX(25);
		}
		else {
			lbl->setAnchorPoint(Vec2(1, 0.5));
			lbl->setPositionX(-25);
		}
		lbl->setMaxLineWidth(350);
		tooltip->addChild(lbl);
		tooltip->setPosition(point);
	}
	else GameScene::tooltip->removeAllChildrenWithCleanup(true);
}

void GameScene::SetupCamera() {
	auto cameraSprite = Sprite::create();
	this->addChild(cameraSprite);
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = (CC_CALLBACK_2(GameScene::onTouchBegan, this));
	touchListener->onTouchMoved = (CC_CALLBACK_2(GameScene::onTouchMoved, this));
	touchListener->onTouchEnded = (CC_CALLBACK_2(GameScene::onTouchEnded, this));
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, cameraSprite);

	auto _mouseListener = EventListenerMouse::create();
	_mouseListener->onMouseMove = CC_CALLBACK_1(GameScene::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

}

void GameScene::SetupGUI() {
	staticUI = Node::create();
	this->addChild(staticUI,5);

	GameScene::tooltip = Node::create();
	staticUI->addChild(tooltip, 2);

	unitDetails = Node::create();
	staticUI->addChild(unitDetails);

	auto background = Sprite::create("UI/GameScene/background (3).png");
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(Vec2(-500, 0));
	this->addChild(background, -1);

	auto _background = Sprite::create("UI/GameScene/static background.png");
	_background->setPosition(visibleSize/2);
	staticUI->addChild(_background, -1);

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

	GameScene::btn_TurnOnUpgrade = Tool::CreateButtonWithoutSprite("btn_TurnOnUpgrade", Tool::ConvertUTF16ToString(L"↑Upgrade↑"),Tool::defaultTextSize*1.4,Color3B::RED);
	btn_TurnOnUpgrade->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.3));
	btn_TurnOnUpgrade->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
	buyingBar->addChild(btn_TurnOnUpgrade,2);

	GameScene::btn_UpgradeFarm = Tool::CreateButtonWithoutSprite("btn_UpgradeFarm", Tool::ConvertUTF16ToString(L"↑ Farm ↑"), Tool::defaultTextSize*1.4, Color3B(100, 225, 255));
	btn_UpgradeFarm->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.3));
	btn_UpgradeFarm->addTouchEventListener([&](Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			GameScene::CreateUpgradeTable(((Button*)pSender)->getName());
			GameScene::BuyingBarMode = "Buy";
			GameScene::ChangeUpgradeState();
		}
	});
	buyingBar->addChild(btn_UpgradeFarm);
	Tool::Button_ChangeState(btn_UpgradeFarm, false, 0);

	GameScene::btn_UpgradeKingdom = Tool::CreateButtonWithoutSprite(IngameObject::GetKingdomByElement(Player::currentPlayer->elementName), Tool::ConvertUTF16ToString(L"↑ Kingdom ↑"),Tool::defaultTextSize*1.4,Color3B(100,255,200));
	btn_UpgradeKingdom->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.3));
	btn_UpgradeKingdom->addTouchEventListener([&](Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
		if (type == Widget::TouchEventType::ENDED) {
			GameScene::CreateUpgradeTable(((Button*)pSender)->getName());
			GameScene::BuyingBarMode = "Buy";
			GameScene::ChangeUpgradeState();
		}
	});
	buyingBar->addChild(btn_UpgradeKingdom);
	Tool::Button_ChangeState(btn_UpgradeKingdom, false, 0);

	this->buyingBar->addChild(ghostItem);
	for (int i = 0; i < List_BuyableUnit.size(); i++) {
		this->buyingBar->addChild(List_BuyableUnit[i].root);
		List_BuyableUnit[i].btn_Icon->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_BuyUnit_Click, this));
		AddDragAndDropItem(List_BuyableUnit[i].root);
	}
	//List_BuyableUnit[0].root->setPosition(Vec2(visibleSize.width*(0.55 - 0.05*List_BuyableUnit.size()), visibleSize.height*0.05));
	List_BuyableUnit[0].root->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.05));
	List_BuyableUnit[0].oldRootPos = List_BuyableUnit[0].root->getPosition();
	for (int i = 1; i < List_BuyableUnit.size(); i++) {
		List_BuyableUnit[i].root->setPosition(List_BuyableUnit[i - 1].root->getPosition() + Vec2(visibleSize.width*0.1,0));
		List_BuyableUnit[i].oldRootPos = List_BuyableUnit[i].root->getPosition();
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
				break;
			}
		}
	}
	if (type == Widget::TouchEventType::CANCELED) {
		
		choosingBuyableUnit = nullptr;
	}
	if (type == Widget::TouchEventType::ENDED) {
		if (GameScene::BuyingBarMode == "Buy") {
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
			choosingBuyableUnit->root->setPosition(choosingBuyableUnit->oldRootPos);
		}
		else if (GameScene::BuyingBarMode == "Upgrade") {
			GameScene::CreateUpgradeTable(((Button*)pSender)->getName());
			GameScene::BuyingBarMode = "Buy";
			GameScene::ChangeUpgradeState();
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
	else if (ingamePlayerInfo.food >= ingamePlayerInfo.foodLimit) {
		RunActionNotify("Not enough food!");
	}
	else {
		Tool::Socket_Client->_client->emit("Create_Unit", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"name\":\"" + name + "\", \"line\":\"" + to_string(line) + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
		ingamePlayerInfo.gold -= unitDetail->goldCost;
		GameScene::UpdateIngamePlayerInfo();
		GameScene::RunActionNotify(name + " has spawned successfully");
	}
}

void GameScene::CreateUpgradeTable(string name) {
	if (name == "btn_UpgradeFarm") {
		auto upgradeTable = Tool::CreateNotificationTable("Upgrade Farm cost " + to_string(100 + ((int)ingamePlayerInfo.foodLimit - 5) * 20) + " Gold", "Cancel", "Process", Size(visibleSize.width*0.5, visibleSize.height*0.4));
		upgradeTable->setPosition(visibleSize / 2);
		staticUI->addChild(upgradeTable, 1);

		upgradeTable->getChildByName("btn_Left")->setColor(Color3B(175, 225, 200));
		((Button*)upgradeTable->getChildByName("btn_Left"))->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Upgrade_Click, this));
		upgradeTable->getChildByName("btn_Right")->setColor(Color3B::RED);
		upgradeTable->getChildByName("btn_Left")->setName(name);
		return;
	}
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
	string upgradeInfo = unitDetails.name + Tool::ConvertUTF16ToString(L"\n↓\n") + unitDetails.upgradeName + "\n"
		+ to_string(unitDetails.upgradeGoldCost) + " Gold     " + to_string(unitDetails.upgradeKnowledgeCost) + " Knowledge";

	auto upgradeTable = Tool::CreateNotificationTable(upgradeInfo,"Cancel","Process",Size(visibleSize.width*0.5,visibleSize.height*0.4));
	upgradeTable->setPosition(visibleSize / 2);
	staticUI->addChild(upgradeTable, 1);

	upgradeTable->getChildByName("btn_Left")->setColor(Color3B(175,225,200));
	((Button*)upgradeTable->getChildByName("btn_Left"))->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Upgrade_Click, this));
	upgradeTable->getChildByName("btn_Right")->setColor(Color3B::RED);
	upgradeTable->getChildByName("btn_Left")->setName(name);
	
}

void GameScene::UpgradeUnit(string name) {
	BaseUnitClass unitDetails;
	if (name == "btn_UpgradeFarm") {
		unitDetails.upgradeLevelRequired = 1;
		unitDetails.upgradeGoldCost = 100 + ((int)ingamePlayerInfo.foodLimit - 5) * 20;
		unitDetails.upgradeKnowledgeCost = 0;
	}
	else if (name.find("Kingdom") != std::string::npos) {
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
		if (name == "btn_UpgradeFarm") {
			ingamePlayerInfo.foodLimit++;
			GameScene::UpdateIngamePlayerInfo();
		}
		else if (unitDetails.description == "Kingdom") {
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


void GameScene::ChangeUpgradeState()
{
	if (GameScene::BuyingBarMode == "Upgrade") {
		Tool::Button_ChangeState(btn_UpgradeKingdom, true, 0.5);
		Tool::Button_ChangeState(btn_UpgradeFarm, true, 0.5);
		for (int i = 0; i < List_BuyableUnit.size(); i++) {
			if (List_BuyableUnit[i].unitInfo->upgradeName != "" && List_BuyableUnit[i].unitInfo->upgradeLevelRequired <= ingamePlayerInfo.kingdomLevel)
				List_BuyableUnit[i].root->runAction(MoveBy::create(0.25, Vec2(0, 175)));
		}
	}
	else {
		Tool::Button_ChangeState(btn_UpgradeKingdom, false, 0);
		Tool::Button_ChangeState(btn_UpgradeFarm, false, 0);
		for (int i = 0; i < List_BuyableUnit.size(); i++) {
			List_BuyableUnit[i].root->runAction(MoveTo::create(0.25, List_BuyableUnit[i].oldRootPos));
		}
	}
}

void GameScene::btn_Upgrade_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		Button* btn = (Button*)pSender;
		GameScene::UpgradeUnit(btn->getName());
		btn->getParent()->runAction(RemoveSelf::create());
	}
}

GameScene::Item_BuyableUnit::Item_BuyableUnit(string name)
{
	this->unitInfo = ObjectConstructor::InitializeObject(name, 0, 0, 0, -1);
	this->root = Node::create();
	if (unitInfo != nullptr) {
		this->btn_Icon = Button::create("Sprites/" + this->unitInfo->animateName + "/card.png");
		this->btn_Icon->setName(unitInfo->name);
		this->btn_Icon->setPositionY(55);

		this->lbl_Cost = Tool::CreateLabel(to_string(unitInfo->goldCost), Tool::defaultTextSize*0.8, Color4B::YELLOW);
		this->lbl_Cost->enableBold();
		this->lbl_Cost->setPosition(Vec2(45, 112));
		this->btn_Icon->addChild(lbl_Cost);

		this->root->addChild(btn_Icon);
	}
}

void GameScene::CreateChatbox() {

	GameScene::sc_ChatBox = ui::ScrollView::create();
	sc_ChatBox->setContentSize(Size(visibleSize.width*0.285, visibleSize.height*0.45));
	sc_ChatBox->setInnerContainerSize(Size(1000, 200));
	sc_ChatBox->setPosition(Vec2(visibleSize.width*0.985, visibleSize.height*0.08));
	sc_ChatBox->setAnchorPoint(Vec2(1, 0));
	sc_ChatBox->setBounceEnabled(true);
	staticUI->addChild(sc_ChatBox, 10);

	auto sp_ChatBox = Sprite::create("UI/GameScene/bgchat.png");
	sp_ChatBox->setPosition(sc_ChatBox->getPosition());
	sp_ChatBox->setAnchorPoint(Vec2(1, 0));
	Tool::setNodeSize(sp_ChatBox, 285, 243);
	staticUI->addChild(sp_ChatBox, 9);

	GameScene::EditBox_Chat = ui::EditBox::create(Size(visibleSize.width*0.255, visibleSize.height*0.06), "", "");
	EditBox_Chat->setPosition(Vec2(visibleSize.width*0.95, visibleSize.height*0.03));
	EditBox_Chat->setAnchorPoint(Vec2(1, 0));
	EditBox_Chat->setTextHorizontalAlignment(TextHAlignment::LEFT);
	EditBox_Chat->setInputMode(EditBox::InputMode::ANY);
	EditBox_Chat->setFontSize(Tool::defaultTextSize);
	EditBox_Chat->setFontColor(Color3B(175, 225, 200));
	EditBox_Chat->setPlaceHolder("Message");
	EditBox_Chat->setPlaceholderFontColor(Color3B::GRAY);
	EditBox_Chat->setMaxLength(100);
	staticUI->addChild(EditBox_Chat, 10);

	auto sp_EditBox = Sprite::create("UI/GameScene/bgEditBox.png");
	sp_EditBox->setPosition(EditBox_Chat->getPosition());
	sp_EditBox->setAnchorPoint(Vec2(1, 0));
	Tool::setNodeSize(sp_EditBox, EditBox_Chat->getBoundingBox().size.width, EditBox_Chat->getBoundingBox().size.height);
	staticUI->addChild(sp_EditBox, 9);


	GameScene::btn_SendMessage = Button::create("UI/GameScene/Send Message.png");
	btn_SendMessage->setAnchorPoint(Vec2(1, 0));
	btn_SendMessage->setPosition(Vec2(visibleSize.width*0.98, visibleSize.height*0.03));
	btn_SendMessage->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_SendMessage_Click, this));
	staticUI->addChild(btn_SendMessage);

	chatBoxContent.push_back({"ImaginysLight and AnhQuyetVo welcome you to Coding TD !", 0});
	UpdateChatbox();
	

}
void GameScene::UpdateChatbox() {
	vector<int> labelHeight;
	int currentHeight = 10;
	sc_ChatBox->removeAllChildrenWithCleanup(true);
	sc_ChatBox->scrollToBottom(0, false);
	for (int i = 0; i < chatBoxContent.size(); i++) {
		Label* lbl_Content = Tool::CreateLabel(chatBoxContent[i].first,Tool::defaultTextSize*0.8);
		lbl_Content->setMaxLineWidth(sc_ChatBox->getContentSize().width*0.9);
		currentHeight += (lbl_Content->getBoundingBox().size.height / 2);
		labelHeight.push_back(currentHeight);
		currentHeight += (8 + lbl_Content->getBoundingBox().size.height / 2);
	}
	sc_ChatBox->setInnerContainerSize(Size(1000, currentHeight + 20));
	for (int i = 0; i < chatBoxContent.size(); i++) {
		Label* lbl_Content = Tool::CreateLabel(chatBoxContent[i].first, Tool::defaultTextSize*0.8);
		lbl_Content->setMaxLineWidth(sc_ChatBox->getContentSize().width*0.9);
		lbl_Content->setPosition(Vec2(10,sc_ChatBox->getInnerContainerSize().height - labelHeight[i]));
		lbl_Content->setAnchorPoint(Vec2(0, 0.5));
		if (chatBoxContent[i].second == 1) lbl_Content->setTextColor(Color4B::GREEN);
		else if (chatBoxContent[i].second == 2) lbl_Content->setTextColor(Color4B::RED);
		else if (chatBoxContent[i].second == 3) lbl_Content->setTextColor(Color4B(175,225,250,255));
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
		Tool::Socket_Client->_client->emit("Send_Message", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"content\":\"" + content + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
		GameScene::EditBox_Chat->setText("");
	}
}
void GameScene::onReceiveEvent_SendMessage(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		GameScene::chatBoxContent.push_back({ document["content"].GetString(), Player::currentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString()) ? 1 : 2 });
		GameScene::UpdateChatbox();
	}
}

void GameScene::onReceiveEvent_UpgradeKingdom(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect("Audio/Level Up.wav", false);
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["Id"].GetString())) {
			ingamePlayerInfo.kingdom->Upgrade();
			ingamePlayerInfo.kingdomLevel++;
			ingamePlayerInfo.lbl_KingdomLevel->setString(to_string(ingamePlayerInfo.kingdomLevel));
			GameScene::btn_UpgradeKingdom->setName(ingamePlayerInfo.kingdom->name);
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
		string result = document["result"].GetString();
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString())) {
			content = Player::currentPlayer->username;
			if (result == "Correct Answer")
				PassiveSkill::Improve(Player::currentPlayer->elementName);
			Player::currentPlayer->betPositive = false;
			Player::opponentPlayer->betNegative = false;
		}
		else {
			content = Player::opponentPlayer->username;
			if (result == "Correct Answer")
				PassiveSkill::Improve(Player::opponentPlayer->elementName);
			Player::currentPlayer->betNegative = false;
			Player::opponentPlayer->betPositive = false;
		}
		if (Player::currentPlayer->elementName == "Fire")
			ingamePlayerInfo.btn_Skill2->setTitleText((string)"Fiery Spirit: Level " + to_string(PassiveSkill::fireLevel) + ": +" + CCString::createWithFormat("%.1f", PassiveSkill::Bonus_Attack*100)->getCString() +"% Attack");
		else if(Player::currentPlayer->elementName == "Ice")
			ingamePlayerInfo.btn_Skill2->setTitleText((string)"Icy Soul: Level " + to_string(PassiveSkill::iceLevel) + ": +" + CCString::createWithFormat("%.1f", PassiveSkill::Bonus_Health * 100)->getCString() + "% Health and " + CCString::createWithFormat("%.1f", PassiveSkill::Bonus_Defense * 100)->getCString() + "% Defense");
		else if (Player::currentPlayer->elementName == "Nature")
			ingamePlayerInfo.btn_Skill2->setTitleText((string)"Pure Heart: Level " + to_string(PassiveSkill::natureLevel) + ": +" + to_string((int)PassiveSkill::Bonus_AttackSpeed) + " Attack Speed and " + to_string((int)PassiveSkill::Bonus_Regeneration) + " Regeneration");


		content += " received ";
		content += document["gold"].GetString();
		content += " Gold for their ";
		content += result;
		chatBoxContent.push_back({ content,0 });
		GameScene::UpdateChatbox();
	}
}

void GameScene::onReceiveEvent_ActiveBet(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		string content;
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString())) {
			content = Player::currentPlayer->username;
		}
		else {
			content = Player::opponentPlayer->username;
			if (document["betStatus"].GetString() == "Positive") Player::opponentPlayer->betPositive = true;
			else Player::opponentPlayer->betNegative = true;
		}
		content += " activated a ";
		content += document["betStatus"].GetString();
		content += " Bet !!";
		chatBoxContent.push_back({ content,3 });
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
	//button đặt cược
	{
		btn_PositiveBet = Tool::CreateButtonWithoutSprite("btn_PositiveBet", "Positive Bet", Tool::defaultTextSize*1.25, Color3B::GREEN);
		btn_PositiveBet->setPosition(Vec2(visibleSize.width*-0.25, visibleSize.height*0.3));
		btn_PositiveBet->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		questionTable->addChild(btn_PositiveBet, 1);

		btn_NegativeBet = Tool::CreateButtonWithoutSprite("btn_NegativeBet", "Negative Bet", Tool::defaultTextSize*1.25, Color3B::RED);
		btn_NegativeBet->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.3));
		btn_NegativeBet->addTouchEventListener(CC_CALLBACK_2(GameScene::btn_Click, this));
		questionTable->addChild(btn_NegativeBet, 1);
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
				questionContent = document["content"].GetString();
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
		}
	}
};


void GameScene::RunActionNotify(string content)
{
	auto lbl_Notify = Tool::CreateLabel(content, Tool::defaultTextSize, Color4B::MAGENTA);
	lbl_Notify->setPosition(visibleSize / 2);
	staticUI->addChild(lbl_Notify, 10);
	lbl_Notify->runAction(Sequence::create(FadeOut::create(0), FadeIn::create(0.5), DelayTime::create(1), FadeOut::create(0.5), RemoveSelf::create(), nullptr));

}

void GameScene::UpdateIngamePlayerInfo()
{
	ingamePlayerInfo.lbl_Gold->setString(to_string((int)ingamePlayerInfo.gold));
	ingamePlayerInfo.lbl_Knowledge->setString(to_string((int)ingamePlayerInfo.knowledge));
	ingamePlayerInfo.lbl_Food->setString(to_string((int)ingamePlayerInfo.food) + " / " + to_string((int)ingamePlayerInfo.foodLimit));
	auto temp = CCString::createWithFormat("%.1f / %d", ingamePlayerInfo.energy,(int)ingamePlayerInfo.energyCap);
	ingamePlayerInfo.lbl_Energy->setString(temp->getCString());

	for (auto card : GameScene::List_BuyableUnit) {
		if (card.unitInfo->goldCost > ingamePlayerInfo.gold)
			card.btn_Icon->setEnabled(false);
		else
			card.btn_Icon->setEnabled(true);
	}
}

void GameScene::CorrectAnswer()
{
	ResultScene::numOfCorrectAnswer++;

	//( 1 + TimeRemaining % / 1.5) * (0.5 + 0.5 * QuestionLevel) * 150 Gold và 1 Knowledge cho câu đúng
	//Positive Bet (cost 100g): Nếu người cược trả lời đúng ở câu trả lời tiếp theo sẽ nhận gấp 1.8 lần Gold.
	auto TimeRemaining = destinationTime - Tool::currentIngameTime;
	auto QuestionTime = currentQuestionLevel * 10 + 10;
	auto TimeRemainingPercent = TimeRemaining / QuestionTime;
	auto goldReceive = (1 + (TimeRemainingPercent / 1.5)) * (0.5 + 0.5 * currentQuestionLevel) * 150 * ingamePlayerInfo.correctAnswerGoldRate;
	if (Player::currentPlayer->betPositive) goldReceive *= 1.8;
	ingamePlayerInfo.gold += goldReceive;
	ingamePlayerInfo.knowledge += 1;
	GameScene::UpdateIngamePlayerInfo();

	Tool::Socket_Client->_client->emit("Answer_Result", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\", \"result\":\"" + "Correct Answer" + "\", \"gold\":\"" + to_string((int)goldReceive) + "\"}");
}

void GameScene::WrongAnswer()
{
	ResultScene::numOfWrongAnswer++;

	// (0.5 + 0.5 * QuestionLevel) * 100 * Rand[0.4 , 0.7] Gold cho câu sai.
	//Negative Bet (cost 100g): Nếu đối phương trả lời sai ở câu trả lời tiếp theo sẽ không được nhận Gold và bị trừ 50 Gold.
	auto randomNumber = Tool::CreateRandomNumber(4, 7) / 10.0;
	auto goldReceive = (0.5 + 0.5 * currentQuestionLevel) * 100 * randomNumber * ingamePlayerInfo.wrongAnswerGoldRate;
	if (Player::opponentPlayer->betNegative) goldReceive = -50;
	ingamePlayerInfo.gold += goldReceive;
	if (ingamePlayerInfo.gold < 0) ingamePlayerInfo.gold = 0;
	GameScene::UpdateIngamePlayerInfo();

	Tool::Socket_Client->_client->emit("Answer_Result", "{\"Room\":\"" + Player::currentPlayer->room_name + "\", \"id\":\"" + to_string(Player::currentPlayer->id) + "\", \"result\":\"" + "Wrong Answer" + "\", \"gold\":\"" + to_string((int)goldReceive) + "\"}");
}

void GameScene::ShowUnitDetails()
{
	auto details = UnitDetailsTable(*GameScene::choosingUnit, Vec2(visibleSize.width*0.87, visibleSize.height*0.79));
	GameScene::unitDetails->removeAllChildrenWithCleanup(true);
	GameScene::unitDetails->addChild(details.root);
}
