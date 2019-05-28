﻿#include"ChooseCardScene.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include <network/SocketIO.h>
//#include "Object/SocketClient.h"
#include "Global Class/Tool.h"
USING_NS_CC;

//Quy trình: lượt 1: cấm 2 lá; lượt 2: chọn 4 lá.
//Trong btn_Click: cần gửi thêm id thằng bị cấm bài
//Select Kingdom onReceive: gán vào GameScene::opponentKingdomName và push vào GameScene::playerPickedUnit
//Prohibit onReceive: push vào mảng bannedCard để disable card ở lượt pick


Scene* ChooseCardScene::createScene()
{
	GameScene::ClearStaticVariables();
	return ChooseCardScene::create();
}

bool ChooseCardScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();
	
	//_client = SocketIO::connect("http://127.0.0.1:3000", *this);
 	Tool::Socket_Client->_client->on("_Prohibit_Card_", CC_CALLBACK_2(ChooseCardScene::onReceive_BanCard, this));
	Tool::Socket_Client->_client->on("_Pick_Card_", CC_CALLBACK_2(ChooseCardScene::onReceive_PickCard, this));
	Tool::Socket_Client->_client->on("_Select_Element_", CC_CALLBACK_2(ChooseCardScene::onReceive_SelectElement, this));
	return true;
}

void ChooseCardScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}  

void ChooseCardScene::onReceive_BanCard(SIOClient* client, const std::string& data) {
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Tool::currentPlayer->room_name)
	{
		bannedCard.push_back({ Tool::ConvertStringToInt(document["CurrentId"].GetString()), document["cardName"].GetString() });
	}
}
void ChooseCardScene::onReceive_PickCard(SIOClient* client, const std::string& data) {
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Tool::currentPlayer->room_name)
	{
		if (Tool::currentPlayer->id == Tool::ConvertStringToInt(document["Id"].GetString())) {
			GameScene::playerPickedUnit.push_back(document["cardName"].GetString());
			ChooseCardScene::lbl_CurrentPlayerPick->setString(
				lbl_CurrentPlayerPick->getString() +
				document["cardName"].GetString() + "\n"
			);
		}
		else {
			ChooseCardScene::lbl_OpponentPlayerPick->setString(
				lbl_OpponentPlayerPick->getString() +
				document["cardName"].GetString() + "\n"
			);
		}
	}
}
void ChooseCardScene::onReceive_SelectElement(SIOClient* client, const std::string& data) {
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	if (document["Room"].GetString() == Tool::currentPlayer->room_name)
	{
		if (Tool::currentPlayer->id == Tool::ConvertStringToInt(document["Id"].GetString())) {
			Tool::currentPlayer->elementName = document["elementName"].GetString();
			ChooseCardScene::lbl_CurrentPlayerPick->setString(
				lbl_CurrentPlayerPick->getString() +
				IngameObject::GetKingdomByElement(Tool::currentPlayer->elementName) + "\n"
			);
		}
		else {
			Tool::opponentPlayer->elementName = document["elementName"].GetString();
			ChooseCardScene::lbl_OpponentPlayerPick->setString(
				lbl_OpponentPlayerPick->getString() +
				IngameObject::GetKingdomByElement(Tool::opponentPlayer->elementName) + "\n"
			);
		}
	}
}

void ChooseCardScene::btn_BanCard_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	Button* term;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		term = (Button*)pSender;
		term->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_Click, this));
		string card = term->getName();
		if (turn == 2 && counter-- > 0) { // BAN card
			term->setColor(Color3B::RED);
			Tool::Socket_Client->_client->emit("_Prohibit_Card_", "{\"cardName\":\"" + card + "\", \"Room\":\"" + Tool::currentPlayer->room_name + "\", \"OpponentId\":\"" + to_string(Tool::opponentPlayer->id) + "\"}");
		}
		if (turn == 3 && counter-- > 0) {//PICK card
			Tool::Socket_Client->_client->emit("_Pick_Card_", "{\"cardName\":\"" + card + "\", \"Room\":\"" + Tool::currentPlayer->room_name + "\", \"Id\":\"" + to_string(Tool::currentPlayer->id) + "\"}");
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
		Tool::Socket_Client->_client->emit("_Select_Element_", "{\"elementName\":\"" + name + "\", \"Room\":\"" + Tool::currentPlayer->room_name + "\", \"Id\":\"" + to_string(Tool::currentPlayer->id) + "\"}");
	}
}

void ChooseCardScene::SetupGUI()
{
	ChooseCardScene::lbl_Cooldown = Tool::CreateLabel("");
	lbl_Cooldown->setPosition(Vec2(visibleSize.width *0.65, visibleSize.height*0.05));
	this->addChild(lbl_Cooldown);

	ChooseCardScene::lbl_Turn = Tool::CreateLabel("");
	lbl_Turn->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height*0.05));
	this->addChild(lbl_Turn);

	ChooseCardScene::lbl_CurrentPlayerPick = Tool::CreateLabel("", Tool::defaultTextSize*0.9, Color4B::GREEN);
	lbl_CurrentPlayerPick->setMaxLineWidth(150);
	lbl_CurrentPlayerPick->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.8));
	lbl_CurrentPlayerPick->setAnchorPoint(Vec2(0.5, 1));
	this->addChild(lbl_CurrentPlayerPick);

	ChooseCardScene::lbl_OpponentPlayerPick = Tool::CreateLabel("", Tool::defaultTextSize*0.9, Color4B::RED);
	lbl_OpponentPlayerPick->setMaxLineWidth(150);
	lbl_OpponentPlayerPick->setPosition(Vec2(visibleSize.width*0.85, visibleSize.height*0.8));
	lbl_OpponentPlayerPick->setAnchorPoint(Vec2(0.5, 1));
	this->addChild(lbl_OpponentPlayerPick);

	auto sp_SceneName = Sprite::create("UI/LoginScene/Login.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/BG/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto frame1 = Sprite::create("UI/BG/frame1.png");
	frame1->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.5));
	this->addChild(frame1);

	auto frame2 = Sprite::create("UI/BG/frame2.png");
	frame2->setPosition(Vec2(visibleSize.width * 0.15f, visibleSize.height*0.5));
	this->addChild(frame2);

	auto frame3 = Sprite::create("UI/BG/frame2.png");
	frame3->setPosition(Vec2(visibleSize.width * 0.85f, visibleSize.height*0.5));
	this->addChild(frame3);

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
				Tool::setNodeSize(btn_Kingdom, 200, 200);
				btn_Kingdom->addTouchEventListener(CC_CALLBACK_2(ChooseCardScene::btn_ChooseKingdom_Click, this));
				this->addChild(btn_Kingdom);
				vecButton.push_back(btn_Kingdom);
			}
			vecButton[0]->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.5));
			vecButton[1]->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
			vecButton[2]->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.5));
		}
	
		ChooseCardScene::lbl_Turn->setString("Select your Kingdom");
		timer = 10;
		ChooseCardScene::lbl_Cooldown->setString(to_string(timer));
	}
	//Turn 2: BAN card: 10 giây
	if (turn == 2) {
		//Setup GUI
		{
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
				vecButton.push_back(btn_Card);
			}
			vecButton[0]->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.7));
			vecButton[1]->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.7));
			vecButton[2]->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.7));
			vecButton[3]->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.45));
			vecButton[4]->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.45));
			vecButton[5]->setPosition(Vec2(visibleSize.width*0.35, visibleSize.height*0.2));
			vecButton[6]->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.2));
			vecButton[7]->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.2)); 
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
					if (Tool::currentPlayer->id == card.first && button->getName() == card.second) {
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

