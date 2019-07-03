#include"LobbyScene.h"

USING_NS_CC;
using namespace CocosDenshion;

string LobbyScene::notify = "";

Scene* LobbyScene::createScene()
{
	return LobbyScene::create();
}

bool LobbyScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	Audio::audio->stopAllEffects();

	if (LobbyScene::notify != "") {
		auto node_Notify = Tool::CreateNotificationTable(notify,"OK");
		node_Notify->setPosition(visibleSize / 2);
		this->addChild(node_Notify, 10);
		LobbyScene::notify = "";
	}

	LobbyScene::SetupGUI();

	Tool::Socket_Client->_client->on("_Find_The_Opponent_",CC_CALLBACK_2(LobbyScene::findTheOpponent, this));
	this->schedule(CC_CALLBACK_1(LobbyScene::UpdateAudio, this), "Audio");
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



void LobbyScene::UpdateAudio(float time)
{
	Audio::UpdateAudio();
}



void LobbyScene::SetupGUI()
{

	auto sp_Background = Sprite::create("UI/Background/Default Background.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto conquest = Trophy::CalculateConquestTrophy(Player::currentPlayer->total_win);
	Sprite* sp_Trophy = Sprite::create("Trophy/Conquest Trophy " + to_string(conquest.level) + ".png");
	sp_Trophy->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
	sp_Trophy->setScale(1.5);
	this->addChild(sp_Trophy, 1);

	auto nodePlayer = Player::CreatePlayerOutgameInfoGUI();
	nodePlayer->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.8));
	this->addChild(nodePlayer);

	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.15));
	this->addChild(lbl_Notify,1);

	btn_Rank = Tool::CreateButtonWithoutSprite("btn_Rank", "Ranking");
	btn_Rank->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.4));
	btn_Rank->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Rank);

	btn_Tutorial = Tool::CreateButtonWithSpirte("btn_Tutorial", "UI/LobbyScene/btn_Tutorial.png");
	btn_Tutorial->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.4));
	btn_Tutorial->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Tutorial);

	auto btn_Achievement = Tool::CreateButtonWithSpirte("btn_Achievement", "UI/LobbyScene/btn_Achievement.png");
	btn_Achievement->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.15));
	btn_Achievement->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Achievement);

	auto btn_Card = Tool::CreateButtonWithSpirte("btn_Card", "UI/LobbyScene/btn_Card.png");
	btn_Card->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.15));
	btn_Card->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Card);

	btn_Logout = Tool::CreateButtonWithoutSprite("btn_Logout", "Logout");
	btn_Logout->setPosition(Vec2(visibleSize.width*0.9, visibleSize.height*0.15));
	btn_Logout->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Logout);

	btn_Room = Tool::CreateButtonWithSpirte("btn_Room", "UI/LobbyScene/btn_Room.png");
	btn_Room->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.15));
	btn_Room->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Room);

	btn_Play = Tool::CreateButtonWithSpirte("btn_Play", "UI/LobbyScene/btn_Play.png");
	btn_Play->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.15));
	btn_Play->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Play);

	


}

void LobbyScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Button*)pSender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		Audio::audio->playEffect(Audio::GetButtonClickAudio().c_str(), false);

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
		if (name == "btn_Room")
		{
			Director::getInstance()->replaceScene(ListRoomScene::createScene());
		}
		if (name == "btn_Logout")
		{
			Tool::Socket_Client->_client->emit("Logout", "{\"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
			Player::currentPlayer = new PlayerInfo(); 
			Director::getInstance()->replaceScene(LoginScene::createScene());
			
		}
		if (name == "btn_Achievement") {
			Director::getInstance()->replaceScene(PlayerInformationScene::createScene());
		}
		if (name == "btn_Card") {
			Director::getInstance()->replaceScene(CardScene::createScene());
		}
	}
}

void LobbyScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

