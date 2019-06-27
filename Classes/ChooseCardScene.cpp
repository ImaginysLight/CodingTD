#include"ChooseCardScene.h"

USING_NS_CC;
using namespace CocosDenshion;

//Quy trình: lượt 1: cấm 2 lá; lượt 2: chọn 4 lá.
//Trong btn_Click: cần gửi thêm id thằng bị cấm bài
//Select Kingdom onReceive: gán vào GameScene::opponentKingdomName và push vào GameScene::playerPickedUnit
//Prohibit onReceive: push vào mảng bannedCard để disable card ở lượt pick


Scene* ChooseCardScene::createScene()
{
	return ChooseCardScene::create();
}

bool ChooseCardScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	
	//_client = SocketIO::connect("http://127.0.0.1:3000", *this);
 	Tool::Socket_Client->_client->on("_Prohibit_Card_", CC_CALLBACK_2(ChooseCardScene::onReceive_BanCard, this));
	Tool::Socket_Client->_client->on("_Pick_Card_", CC_CALLBACK_2(ChooseCardScene::onReceive_PickCard, this));
	Tool::Socket_Client->_client->on("_Select_Element_", CC_CALLBACK_2(ChooseCardScene::onReceive_SelectElement, this));

	Tool::Socket_Client->_client->on("Get_Player_Info", CC_CALLBACK_2(ChooseCardScene::onReceiveEvent_GetInfoPlayer, this));
	Tool::Socket_Client->_client->emit("Get_Player_Info", "{\"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
	Tool::Socket_Client->_client->emit("Get_Player_Info", "{\"id\":\"" + to_string(Player::opponentPlayer->id) + "\"}");
	
	SetupGUI();

	return true;
}

void ChooseCardScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}  

void ChooseCardScene::onReceive_BanCard(SIOClient* client, const std::string& data) {
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		bannedCard.push_back({ Tool::ConvertStringToInt(document["CurrentId"].GetString()), document["cardName"].GetString() });
	}
}
void ChooseCardScene::onReceive_PickCard(SIOClient* client, const std::string& data) {
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		string cardName = document["cardName"].GetString();
		auto sp_Card = Sprite::create("Sprites/" + cardName + "/card.png");
		this->addChild(sp_Card);
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["Id"].GetString())) {
			Player::currentPlayer->picked_units.push_back(cardName);
			ChooseCardScene::currentPlayerPosition -= Vec2(0, visibleSize.height*0.155);
			sp_Card->setPosition(ChooseCardScene::currentPlayerPosition);
		}
		else {
			Player::opponentPlayer->picked_units.push_back(cardName);
			ChooseCardScene::opponentPlayerPosition -= Vec2(0, visibleSize.height*0.15);
			sp_Card->setPosition(ChooseCardScene::opponentPlayerPosition);
		}
	}
}
void ChooseCardScene::onReceive_SelectElement(SIOClient* client, const std::string& data) {
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["Id"].GetString())) {
			Player::currentPlayer->elementName = document["elementName"].GetString();
			ChooseCardScene::lbl_CurrentPlayerPick->setString(
				lbl_CurrentPlayerPick->getString() +
				IngameObject::GetKingdomByElement(Player::currentPlayer->elementName) + "\n"
			);
		}
		else {
			Player::opponentPlayer->elementName = document["elementName"].GetString();
			ChooseCardScene::lbl_OpponentPlayerPick->setString(
				lbl_OpponentPlayerPick->getString() +
				IngameObject::GetKingdomByElement(Player::opponentPlayer->elementName) + "\n"
			);
		}
	}
}

void ChooseCardScene::onReceiveEvent_GetInfoPlayer(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (Player::currentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString())) {
		Player::currentPlayer->username = document["username"].GetString();
		Player::currentPlayer->password = document["password"].GetString();
		Player::currentPlayer->experience = document["experience"].GetInt();
		Player::currentPlayer->total_correctAnswer = document["correct_answer"].GetInt();
		Player::currentPlayer->total_wrongAnswer = document["wrong_answer"].GetInt();
		Player::currentPlayer->total_win = document["total_win"].GetInt();
		Player::currentPlayer->total_lose = document["total_lose"].GetInt();
		Player::currentPlayer->total_kill = document["total_kill"].GetInt();
		Player::currentPlayer->friendshipPoint = document["friendship_point"].GetInt();
		Player::GetFriendshipLevel(Player::currentPlayer,document["friendship_level"].GetString());
		//Player::currentPlayer->room_name = document["room_name"].GetString();
		Player::currentPlayer->submit_available = document["submit_available"].GetInt();

		ChooseCardScene::lbl_CurrentPlayerName->setString(Player::currentPlayer->username);
	}
	else if (Player::opponentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString())) {
		Player::opponentPlayer->username = document["username"].GetString();
		Player::opponentPlayer->password = document["password"].GetString();
		Player::opponentPlayer->experience = document["experience"].GetInt();
		Player::opponentPlayer->total_correctAnswer = document["correct_answer"].GetInt();
		Player::opponentPlayer->total_wrongAnswer = document["wrong_answer"].GetInt();
		Player::opponentPlayer->total_win = document["total_win"].GetInt();
		Player::opponentPlayer->total_lose = document["total_lose"].GetInt();
		Player::opponentPlayer->total_kill = document["total_kill"].GetInt();
		Player::opponentPlayer->friendshipPoint = document["friendship_point"].GetInt();
		Player::GetFriendshipLevel(Player::opponentPlayer, document["friendship_level"].GetString());
		//Player::opponentPlayer->room_name = document["room_name"].GetString();
		Player::opponentPlayer->submit_available = document["submit_available"].GetInt();

		ChooseCardScene::lbl_OpponentPlayerName->setString(Player::opponentPlayer->username);
	}

}

void ChooseCardScene::btn_BanCard_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	Button* term;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect(Audio::GetButtonClickAudio().c_str(), false);
		term = (Button*)pSender;
		term->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_Click, this));
		string card = term->getName();
		if (turn == 2 && counter-- > 0) { // BAN card
			term->setColor(Color3B::RED);
			Tool::Socket_Client->_client->emit("_Prohibit_Card_", "{\"cardName\":\"" + card + "\", \"Room\":\"" + Player::currentPlayer->room_name + "\", \"OpponentId\":\"" + to_string(Player::opponentPlayer->id) + "\"}");
		}
		if (turn == 3 && counter-- > 0) {//PICK card
			Tool::Socket_Client->_client->emit("_Pick_Card_", "{\"cardName\":\"" + card + "\", \"Room\":\"" + Player::currentPlayer->room_name + "\", \"Id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
			term->setColor(Color3B::GREEN);
		}
	}
	default: break;
	}
}


void ChooseCardScene::btn_ChooseKingdom_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		for (auto kingdom : vecButton) {
			kingdom->setEnabled(false);
		}
		((Button*)pSender)->setEnabled(true);
		((Button*)pSender)->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_Click, this));
		Tool::Socket_Client->_client->emit("_Select_Element_", "{\"elementName\":\"" + name + "\", \"Room\":\"" + Player::currentPlayer->room_name + "\", \"Id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
	}
}

void ChooseCardScene::SetupGUI()
{
	auto frame1 = Sprite::create("UI/Background/frame1.png");
	frame1->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.5));
	this->addChild(frame1);

	auto frame2 = Sprite::create("UI/Background/frame2.png");
	frame2->setPosition(Vec2(visibleSize.width * 0.15f, visibleSize.height*0.5));
	this->addChild(frame2);

	auto frame3 = Sprite::create("UI/Background/frame2.png");
	frame3->setPosition(Vec2(visibleSize.width * 0.85f, visibleSize.height*0.5));
	this->addChild(frame3);

	ChooseCardScene::lbl_CurrentPlayerName = Tool::CreateLabel("");
	lbl_CurrentPlayerName->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.88));
	this->addChild(lbl_CurrentPlayerName, 1);

	ChooseCardScene::lbl_OpponentPlayerName = Tool::CreateLabel("");
	lbl_OpponentPlayerName->setPosition(Vec2(visibleSize.width*0.85, visibleSize.height*0.88));
	this->addChild(lbl_OpponentPlayerName, 1);

	ChooseCardScene::lbl_Cooldown = Tool::CreateLabel("");
	lbl_Cooldown->setPosition(Vec2(visibleSize.width *0.65, visibleSize.height*0.88));
	this->addChild(lbl_Cooldown);

	ChooseCardScene::lbl_Turn = Tool::CreateLabel("");
	lbl_Turn->setPosition(Vec2(visibleSize.width *0.45, visibleSize.height*0.88));
	this->addChild(lbl_Turn);

	currentPlayerPosition = Vec2(visibleSize.width*0.15, visibleSize.height*0.82);
	opponentPlayerPosition = Vec2(visibleSize.width*0.85, visibleSize.height*0.82);

	ChooseCardScene::lbl_CurrentPlayerPick = Tool::CreateLabel("", Tool::defaultTextSize*0.9, Color4B::GREEN);
	lbl_CurrentPlayerPick->setPosition(visibleSize.width*0.15, visibleSize.height*0.775);
	this->addChild(lbl_CurrentPlayerPick);

	ChooseCardScene::lbl_OpponentPlayerPick = Tool::CreateLabel("", Tool::defaultTextSize*0.9, Color4B::RED);
	lbl_OpponentPlayerPick->setPosition(visibleSize.width*0.85, visibleSize.height*0.775);
	lbl_OpponentPlayerPick->setVisible(false);
	this->addChild(lbl_OpponentPlayerPick);

	/*auto sp_SceneName = Sprite::create("UI/LoginScene/Login.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);*/

	auto sp_Background = Sprite::create("UI/Background/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	this->schedule(schedule_selector(ChooseCardScene::UpdateEachSecond), 1);
}

void ChooseCardScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
}



void ChooseCardScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

void ChooseCardScene::UpdateEachSecond(float time)
{
	ChooseCardScene::lbl_Cooldown->setString(to_string(--timer));
	if (timer < 0) ChangeTurn();

}

void ChooseCardScene::ChangeTurn() {
	turn++;
	//Turn 1: chọn Kingdom: 10 giây
	if (turn == 1) {
		//Setup GUI
		{
			vecButton = vector<Button*>();
			vector<pair<string,string>> kingdomName;
			kingdomName.push_back({ "Fire", "Flamed Kingdom" });
			kingdomName.push_back({ "Nature", "Blessed Kingdom" });
			kingdomName.push_back({ "Ice", "Frozen Kingdom" });
			for (int i = 0; i < 3; i++) {
				auto btn_Kingdom = Button::create("Sprites/" + kingdomName[i].second + "/default.png");
				btn_Kingdom->setName(kingdomName[i].first);
				Tool::setNodeSize(btn_Kingdom, 160, 170);
				btn_Kingdom->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_ChooseKingdom_Click, this));
				this->addChild(btn_Kingdom);
				vecButton.push_back(btn_Kingdom);
			}
			vecButton[0]->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.3));
			vecButton[1]->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.3));
			vecButton[2]->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
		}
	
		ChooseCardScene::lbl_Turn->setString("Select your Kingdom");
		timer = 10;
		ChooseCardScene::lbl_Cooldown->setString(to_string(timer));
	}
	//Turn 2: BAN card: 10 giây
	if (turn == 2) {
		if (Player::currentPlayer->elementName == "" || Player::opponentPlayer->elementName == "") {
			LobbyScene::notify = "The game was canceled due to someone did not choose the Kingdom";
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
		//Setup GUI
		{
			lbl_OpponentPlayerPick->setVisible(true);
			for (auto child : vecButton) {
				Tool::Button_ChangeState(child, false, 0.5);
			}
			vecButton = vector<Button*>();
			vector<string> cardName;
			cardName.push_back("Hotheaded Gunner");
			cardName.push_back("Crazy Wolf");
			cardName.push_back("Helicopter");
			cardName.push_back("Dead Walker");
			cardName.push_back("UFO Driver");
			cardName.push_back("Winged Orc");
			cardName.push_back("Liquid Assassin");
			cardName.push_back("Elemental Alien");
			for (int i = 0; i < 8; i++)
			{
				auto btn_Card = Button::create("Sprites/"+cardName[i]+"/card.png");
				btn_Card->setName(cardName[i]);
				btn_Card->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_BanCard_Click, this));
				this->addChild(btn_Card);
				auto lbl_Gold = Tool::CreateLabel(to_string(ObjectConstructor::InitializeObject(cardName[i] + " 1", 0, 1, 0, -1)->goldCost), Tool::defaultTextSize*0.8, Color4B::YELLOW);
				lbl_Gold->setPosition(Vec2(40,112));
				btn_Card->addChild(lbl_Gold);
				vecButton.push_back(btn_Card);
			}
			vecButton[0]->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.6));
			vecButton[1]->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.6));
			vecButton[2]->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.6));
			vecButton[3]->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.6));
			vecButton[4]->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.3));
			vecButton[5]->setPosition(Vec2(visibleSize.width*0.45, visibleSize.height*0.3));
			vecButton[6]->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.3));
			vecButton[7]->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.3)); 
		}
		counter = 2;
		ChooseCardScene::lbl_Turn->setString("Select 2 cards to BAN");
		lbl_Turn->setTextColor(Color4B::RED);
		timer = 10;
		ChooseCardScene::lbl_Cooldown->setString(to_string(timer));
	}
	//Turn 3: PICK card: 20 giây
	if (turn == 3) {
		//SetupGUI
		{
			for (auto button : ChooseCardScene::vecButton) {
				for (auto card : bannedCard) {
					if (Player::currentPlayer->id == card.first && button->getName() == card.second) {
						button->setEnabled(false);
					}
				}
				button->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_BanCard_Click, this));
				button->setColor(Color3B::WHITE);
			}
		}
		counter = 4;
		ChooseCardScene::lbl_Turn->setString("Select 4 cards to PICK");
		lbl_Turn->setTextColor(Color4B::GREEN);
		timer = 20;
		ChooseCardScene::lbl_Cooldown->setString(to_string(timer));
	}
	if (turn == 4) {
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
}

