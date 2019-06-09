#include"LobbyScene.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include <network/SocketIO.h>
USING_NS_CC;

Scene* LobbyScene::createScene()
{
	return LobbyScene::create();
}

bool LobbyScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();

	//_client = SocketIO::connect("http://127.0.0.1:3000", *this);
	Tool::Socket_Client->_client->on("_Find_The_Opponent_",CC_CALLBACK_2(LobbyScene::findTheOpponent, this));

	return true;
}

void LobbyScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void LobbyScene::findTheOpponent(SIOClient* client, const std::string& data)
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
				if (Player::currentPlayer->id != Tool::ConvertStringToInt(*Vec[0]))
				{
					Player::opponentPlayer->id = Tool::ConvertStringToInt(*Vec[0]);
				}
				if (Player::currentPlayer->id != Tool::ConvertStringToInt(*Vec[1]))
				{
					Player::opponentPlayer->id = Tool::ConvertStringToInt(*Vec[1]);
				}
				Director::getInstance()->replaceScene(ChooseCardScene::createScene());
				//CCLOG("change Scene");
			}
		}
		else
		{
			CCLOG("Room: %s ", document["Room"].GetString());
		}
	}
}

void LobbyScene::SetupGUI()
{
	auto sp_SceneName = Sprite::create("UI/LobbyScene/Lobby.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/LoginScene/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto knowledge = Trophy::CalculateKnowledgeTrophy(Player::currentPlayer->total_correctAnswer);
	Button* btn_Trophy = Button::create("Trophy/Knowledge Trophy " + to_string(knowledge.level) + ".png");
	btn_Trophy->setName("btn_Trophy");
	btn_Trophy->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	btn_Trophy->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
	btn_Trophy->setScale(1.5);
	this->addChild(btn_Trophy, 1);

	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	this->addChild(lbl_Notify,1);

	btn_Play = Button::create("UI/LobbyScene/btn_Play_nomal.png", "UI/LobbyScene/btn_Play_select.png");
	btn_Play->setName("btn_Play");
	btn_Play->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.25));
	btn_Play->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Play);

	btn_Rank = Button::create("UI/LobbyScene/btn_Rank_nomal.png", "UI/LobbyScene/btn_Rank_select.png");
	btn_Rank->setName("btn_Rank");
	btn_Rank->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.8));
	btn_Rank->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Rank);

	btn_Tutorial = Button::create("UI/LobbyScene/btn_Tutorial_nomal.png", "UI/LobbyScene/btn_Tutorial_select.png");
	btn_Tutorial->setName("btn_Tutorial");
	btn_Tutorial->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.6));
	btn_Tutorial->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Tutorial);

	btn_Extend = Button::create("UI/LobbyScene/btn_Extend_nomal.png", "UI/LobbyScene/btn_Extend_select.png");
	btn_Extend->setName("btn_Extend");
	btn_Extend->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.4));
	btn_Extend->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Extend);

	btn_Logout = Button::create("UI/LobbyScene/btn_Logout_nomal.png", "UI/LobbyScene/btn_Logout_select.png");
	btn_Logout->setName("btn_Logout");
	btn_Logout->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.2));
	btn_Logout->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Logout);

	btn_Info = Button::create("UI/LobbyScene/btn_Logout_nomal.png", "UI/LobbyScene/btn_Logout_select.png");
	btn_Info->setName("btn_Info");
	btn_Info->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.7));
	btn_Info->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Info);

	auto lbl_Username = Tool::CreateLabel(Player::currentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_Username->setPosition(visibleSize / 2);
	this->addChild(lbl_Username);

}

void LobbyScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Button*)pSender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		if (name == "btn_Tutorial") {
			Director::getInstance()->replaceScene(TutorialScene::createScene());
		}
		if (name == "btn_Play") {
			Tool::Socket_Client->_client->emit("_Find_The_Opponent_", "{\"id\":\""+ to_string(Player::currentPlayer->id) + "\"}");
		}
		if (name == "btn_Rank")
		{
			Director::getInstance()->replaceScene(RankingScene::createScene());
		}
		if (name == "btn_Extend")
		{
			Director::getInstance()->replaceScene(ListRoomScene::createScene());
		}
		if (name == "btn_Logout")
		{
			Director::getInstance()->replaceScene(LoginScene::createScene());
		}
		if (name == "btn_Trophy") {
			Director::getInstance()->replaceScene(PlayerInformationScene::createScene());
		}
	}
}

void LobbyScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

//void LobbyScene::onConnect(SIOClient* client){}
//void LobbyScene::onMessage(SIOClient* client, const std::string& data){}
//void LobbyScene::onClose(SIOClient* client){}
//void LobbyScene::onError(SIOClient* client, const std::string& data){}