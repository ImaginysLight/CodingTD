#include"MyRoomScene.h"

USING_NS_CC;

Scene* MyRoomScene::createScene()
{
	return MyRoomScene::create();
}

bool MyRoomScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();

	//_client = SocketIO::connect("http://127.0.0.1:3000", *this);
	Tool::Socket_Client->_client->on("Join_Room",CC_CALLBACK_2(MyRoomScene::findTheOpponent, this));
	Tool::Socket_Client->_client->on("Update_Room", CC_CALLBACK_2(MyRoomScene::onReceiveEvent_UpdateRoom, this));
	Tool::Socket_Client->_client->on("_Ready_", CC_CALLBACK_2(MyRoomScene::onReceiveEvent_Ready, this));
	Tool::Socket_Client->_client->on("_Chase_Player_", CC_CALLBACK_2(MyRoomScene::onReceiveEvent_Chase_Player, this));

	return true;
}

void MyRoomScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void MyRoomScene::findTheOpponent(SIOClient* client, const std::string& data)
{
	vector <string*> Vec;
	int check;
	std::string *room = new string;
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Room")) {
		*room = document["Room"].GetString();
		check = room->find("_");
		if (check != -1)
		{
			Tool::CutString(room, Vec, "_");
			if (Player::currentPlayer->id == Tool::ConvertStringToInt(*Vec[0]) || Player::currentPlayer->id == Tool::ConvertStringToInt(*Vec[1]))
			{
				Player::currentPlayer->room_name = document["Room"].GetString();
				btn_Roomname->setTitleText(Player::currentPlayer->room_name);
				if(Player::currentPlayer->id != Tool::ConvertStringToInt(*Vec[0]))
				{ 
					Player::opponentPlayer->id = Tool::ConvertStringToInt(*Vec[0]);
				}
				if(Player::currentPlayer->id != Tool::ConvertStringToInt(*Vec[1]))
				{ 
					Player::opponentPlayer->id = Tool::ConvertStringToInt(*Vec[1]);
				}

				Tool::Socket_Client->_client->on("Get_Player_Info", CC_CALLBACK_2(MyRoomScene::onReceiveEvent_GetInfoOpponent, this));
				Tool::Socket_Client->_client->emit("Get_Player_Info", "{\"id\":\"" + to_string(Player::opponentPlayer->id) + "\"}");
				btn_Extend->setEnabled(true);
				btn_Play->setEnabled(true);
				/*Player::opponentPlayer->id = document["id"].GetInt();
				Player::opponentPlayer->username = document["username"].GetString();
				Director::getInstance()->replaceScene(ChooseCardScene::createScene());*/
				CCLOG("MyRoomScene: change Scene");
			}
		}
		else
		{
			CCLOG("Room: %s ", document["Room"].GetString());
		}
	}
}

void MyRoomScene::onReceiveEvent_UpdateRoom(SIOClient* client, const std::string& data)
{
	vector <string*> Vec;
	int check;
	std::string *room = new string;
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Room") && document["Room"].GetString() == Player::currentPlayer->room_name) {
		*room = document["Room"].GetString();
		check = room->find("_");
		if (check != -1)
		{
			Tool::CutString(room, Vec, "_");
			if (Player::currentPlayer->id == Tool::ConvertStringToInt(*Vec[0]) || Player::currentPlayer->id == Tool::ConvertStringToInt(*Vec[1]))
			{
				Player::currentPlayer->room_name = to_string(Player::currentPlayer->id);
				//CCLOG("room %s", Player::currentPlayer->room_name.c_str());
				btn_Roomname->setTitleText(document["CurrentId"].GetString());
				//string id = to_string(Player::currentPlayer->id);
				//Tool::Socket_Client->_client->emit("Create_Room", "{\"id\":\"" + id + "\"}");
				/*Player::opponentPlayer->id = document["id"].GetInt();
				Player::opponentPlayer->username = document["username"].GetString();
				Director::getInstance()->replaceScene(ChooseCardScene::createScene());*/
			}
			btn_Play->setVisible(true);
			btn_Extend->setVisible(true);
			btn_Extend->setEnabled(false);
			btn_Play->setEnabled(false);
			opponentNode->removeAllChildrenWithCleanup(true);
			Player::opponentPlayer = new PlayerInfo();
		}
		else
		{
			CCLOG("Room: %s ", document["Room"].GetString());
		}
	}
}

void MyRoomScene::onReceiveEvent_Ready(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Room") && document["Room"].GetString() == Player::currentPlayer->room_name)
	{
		Director::getInstance()->replaceScene(ChooseCardScene::createScene());
	}
}

void MyRoomScene::onReceiveEvent_Chase_Player(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Room") && document["Room"].GetString() == Player::currentPlayer->room_name && to_string(Player::currentPlayer->id) == document["CurrentId"].GetString())
	{
		Tool::Socket_Client->_client->emit("Update_Room", "{\"CurrentId\":\"" + to_string(Player::currentPlayer->id) + "\", \"OppenontId\":\"" + to_string(Player::opponentPlayer->id) + "\" ,\"Room\":\"" + Player::currentPlayer->room_name + "\"}");
		Player::opponentPlayer->id = 0;
		Player::currentPlayer->room_name = "0";
		Director::getInstance()->replaceScene(ListRoomScene::createScene());
	}
}

void MyRoomScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Button*)pSender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		if (name == "btn_Tutorial") {
			Director::getInstance()->replaceScene(TutorialScene::createScene());
		}
		if (name == "btn_Play") {
			Tool::Socket_Client->_client->emit("_Ready_", "{\"Room\":\""+ (Player::currentPlayer->room_name) + "\"}");
		}
		if (name == "btn_Rank")
		{
			Director::getInstance()->replaceScene(RankingScene::createScene());
		}
		if (name == "btn_Chase")
		{
			Tool::Socket_Client->_client->emit("_Chase_Player_", "{\"OppenontId\":\"" + to_string(Player::opponentPlayer->id) + "\", \"Room\":\"" + Player::currentPlayer->room_name + "\"}");
			opponentNode->removeAllChildrenWithCleanup(true);
			Player::opponentPlayer = new PlayerInfo();
			//Director::getInstance()->replaceScene(ListRoomScene::createScene());
		}
		if (name == "btn_Exit")
		{
			string id = to_string(Player::currentPlayer->id);
			if(Player::currentPlayer->room_name.find("_") != -1)//nếu trong room name không có kí tự "_"
			{
				Tool::Socket_Client->_client->emit("Update_Room", "{\"CurrentId\":\"" + to_string(Player::currentPlayer->id) + "\", \"OppenontId\":\"" + to_string(Player::opponentPlayer->id) + "\" ,\"Room\":\"" + Player::currentPlayer->room_name + "\"}");
				Player::opponentPlayer->id = 0;
			}
			else
			{
				Tool::Socket_Client->_client->emit("Destroy_Room", "{\"id\":\"" + id + "\", \"Room\":\"" + Player::currentPlayer->room_name + "\"}");
			}
			Player::currentPlayer->room_name = id;
			Director::getInstance()->replaceScene(ListRoomScene::createScene());
		}
	}
}

void MyRoomScene::LoadOpponentInfo()
{
	opponentNode->removeAllChildrenWithCleanup(true);
	auto lbl_Username = Tool::CreateLabel(Player::opponentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_Username->setPosition(visibleSize.width*0.8, visibleSize.height*0.825);
	opponentNode->addChild(lbl_Username);

	auto conquest = Trophy::CalculateConquestTrophy(Player::opponentPlayer->total_win);
	if (conquest.level != 0) {
		auto sp_Trophy = Sprite::create("Trophy/Conquest Trophy " + to_string(conquest.level) + ".png");
		sp_Trophy->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*.55));
		opponentNode->addChild(sp_Trophy);
	}

	auto lbl_Level = Label::create("Level " + to_string(Player::CalculateLevel(Player::opponentPlayer->experience).first), "custom_font.ttf", Tool::defaultTextSize*1.5);
	lbl_Level->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*.25));
	opponentNode->addChild(lbl_Level);
	vector <string*> Vec;
	string* room = new string;
	*room = Player::currentPlayer->room_name;
	Tool::CutString(room, Vec, "_");
	if (to_string(Player::currentPlayer->id) != (*Vec[0])) {
		btn_Play->setVisible(false);
		btn_Extend->setVisible(false);
	}
}

void MyRoomScene::SetupGUI()
{

	//auto sp_SceneName = Sprite::create("UI/LobbyScene/Lobby.png");
	//sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	//this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/Login/BG.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto sp_frame1 = Sprite::create("UI/Upgrade/frame.png");
	sp_frame1->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.5));
	this->addChild(sp_frame1);

	auto sp_frame2 = Sprite::create("UI/Upgrade/frame.png");
	sp_frame2->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.5));
	this->addChild(sp_frame2);

	btn_Logout = Button::create("UI/Lobby/btn_exit.png");
	btn_Logout->setName("btn_Exit");
	btn_Logout->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.2));
	btn_Logout->addTouchEventListener(CC_CALLBACK_2(MyRoomScene::btn_Click, this));
	this->addChild(btn_Logout);


	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	this->addChild(lbl_Notify, 1);

	btn_Play = Button::create("UI/Lobby/btn_start.png");
	btn_Play->setName("btn_Play");
	btn_Play->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
	btn_Play->addTouchEventListener(CC_CALLBACK_2(MyRoomScene::btn_Click, this));
	btn_Play->setEnabled(false);
	this->addChild(btn_Play);

	btn_Extend = Button::create("UI/Lobby/btn_kick.png");
	btn_Extend->setEnabled(false);
	btn_Extend->setName("btn_Chase");
	btn_Extend->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.4));
	btn_Extend->addTouchEventListener(CC_CALLBACK_2(MyRoomScene::btn_Click, this));
	this->addChild(btn_Extend);

	auto lbl_Username = Tool::CreateLabel(Player::currentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_Username->setPosition(visibleSize.width*0.2,visibleSize.height*0.825);
	this->addChild(lbl_Username);

	//auto knowledge = Trophy::CalculateKnowledgeTrophy(Player::currentPlayer->total_correctAnswer);
	//if (knowledge.level != 0) {
	//	auto sp_Trophy1_1 = Sprite::create("Trophy/Knowledge Trophy " + to_string(knowledge.level) + ".png");
	//	sp_Trophy1_1->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*.65));
	//	this->addChild(sp_Trophy1_1);
	//}

	auto conquest = Trophy::CalculateConquestTrophy(Player::currentPlayer->total_win);
	if (conquest.level != 0) {
		auto sp_Trophy = Sprite::create("Trophy/Conquest Trophy " + to_string(conquest.level) + ".png");
		sp_Trophy->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*.55));
		this->addChild(sp_Trophy);
	}

	auto lbl_Level = Label::create("Level " + to_string(Player::CalculateLevel(Player::currentPlayer->experience).first), "custom_font.ttf", Tool::defaultTextSize*1.5);
	lbl_Level->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*.25));
	this->addChild(lbl_Level);

	/*auto battle = Trophy::CalculateBattleTrophy(Player::currentPlayer->total_kill);
	if (battle.level != 0) {
		auto sp_Trophy3_1 = Sprite::create("Trophy/Battle Trophy " + to_string(battle.level) + ".png");
		sp_Trophy3_1->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*.45));
		this->addChild(sp_Trophy3_1);
	}*/
	btn_Roomname = Button::create();
	btn_Roomname->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height*0.8f));
	btn_Roomname->setTitleText(to_string(Player::currentPlayer->id));
	btn_Roomname->setTitleFontSize(40);
	btn_Roomname->setTitleColor(Color3B::GREEN);
	btn_Roomname->setVisible(false);
	this->addChild(btn_Roomname);

	opponentNode = Node::create();
	this->addChild(opponentNode);

}

void MyRoomScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

//void MyRoomScene::onConnect(SIOClient* client){}
//void MyRoomScene::onMessage(SIOClient* client, const std::string& data){}
//void MyRoomScene::onClose(SIOClient* client){}
//void MyRoomScene::onError(SIOClient* client, const std::string& data){}
void MyRoomScene::onReceiveEvent_GetInfoOpponent(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (Player::opponentPlayer->id == Tool::ConvertStringToInt(document["id"].GetString())) {
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
		LoadOpponentInfo();
	}
}