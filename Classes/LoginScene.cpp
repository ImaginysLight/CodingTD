﻿#include"LoginScene.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include <network/SocketIO.h>
//#include "Object/SocketClient.h"
#include "Global Class/Tool.h"
USING_NS_CC;



Scene* LoginScene::createScene()
{
	return LoginScene::create();
}

bool LoginScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();
	
	//_client = SocketIO::connect("http://127.0.0.1:3000", *this);
 	Tool::Socket_Client->_client->on("_Check_Login_", CC_CALLBACK_2(LoginScene::onReceiveEvent, this));
	Tool::Socket_Client->_client->on("Get_infor_Player", CC_CALLBACK_2(LoginScene::onReceiveEvent_GetInfoPlayer, this));
	return true;
}

void LoginScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}  



void LoginScene::onReceiveEvent(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	if (document.HasMember("Check")) {
		//CCLOG("Check: %d ", document["Check"].GetInt());
		if (document["Check"].GetInt() != 0)
		{
			RunActionNotify(editBox_Username->getText());
			Player::currentPlayer->username = editBox_Username->getText();
			Player::currentPlayer->password = editBox_Password->getText();
			Player::currentPlayer->id = document["Check"].GetInt();
			//CCLOG("ID: %d ",document["id"].GetInt());
			//_client->disconnect();
			Tool::Socket_Client->_client->emit("Get_infor_Player", "{\"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
		else
		{
			CCLOG("Login Fail");
		}
	}
}
void LoginScene::onReceiveEvent_GetInfoPlayer(SIOClient * client, const std::string & data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	Player::currentPlayer->id = Tool::ConvertStringToInt(document["id"].GetString());
	Player::currentPlayer->username = document["username"].GetString();
	Player::currentPlayer->password = document["password"].GetString();
	Player::currentPlayer->experience = document["experience"].GetInt();
	Player::currentPlayer->total_correctAnswer = document["correct_answer"].GetInt();
	Player::currentPlayer->total_wrongAnswer = document["wrong_answer"].GetInt();
	Player::currentPlayer->total_win = document["total_win"].GetInt();
	Player::currentPlayer->total_lose = document["total_lose"].GetInt();
	Player::currentPlayer->total_kill = document["total_kill"].GetInt();
	Player::currentPlayer->friendshipPoint = document["friendship_point"].GetInt();
	Player::GetFriendshipLevel(document["friendship_level"].GetString());
	Player::currentPlayer->room_name = document["room_name"].GetString();
	Player::currentPlayer->submit_available = document["submit_available"].GetInt();
}
void LoginScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	Button* term;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		term = (Button*)pSender;
		if (term->getName() == "btn_Login") {
			if (editBox_Username->getText() == "" || editBox_Password->getText() == "")
			{
				CCLOG("Fail");
			}
			else
			{
				std::string username = editBox_Username->getText();
				std::string password = editBox_Password->getText();
				Tool::Socket_Client->_client->emit("_Log_in_", "{\"username\":\"" + username + "\", \"password\":\"" + password + "\"}");
			}

		}
		else if (term->getName() == "btn_Register") {
			//LoginScene::onClose(_client);
			Director::getInstance()->end();
		}
	}
	default: break;
	}
}

void LoginScene::SetupGUI()
{
	auto sp_SceneName = Sprite::create("UI/LoginScene/Login.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/GameScene/static background.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	editBox_Username = ui::EditBox::create(Size(visibleSize.width/3, 30),"", "");
	editBox_Username->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
	editBox_Username->setTextHorizontalAlignment(TextHAlignment::CENTER);
	editBox_Username->setFontSize(Tool::defaultTextSize);
	editBox_Username->setFontColor(Color3B(175,225,200));
	editBox_Username->setPlaceHolder("Username");
	editBox_Username->setPlaceholderFontColor(Color3B::GRAY);
	editBox_Username->setMaxLength(20);
	editBox_Username->setText("Player001");
	this->addChild(editBox_Username);

	editBox_Password = ui::EditBox::create(Size(visibleSize.width / 3, 30), "", "");
	editBox_Password->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.45));
	editBox_Password->setTextHorizontalAlignment(TextHAlignment::CENTER);
	editBox_Password->setFontSize(Tool::defaultTextSize);
	editBox_Password->setFontColor(Color3B(175, 225, 250));
	editBox_Password->setPlaceHolder("Password");
	editBox_Password->setPlaceholderFontColor(Color3B::GRAY);
	editBox_Password->setMaxLength(20);
	editBox_Password->setText("Player001");
	this->addChild(editBox_Password);

	auto sp_EditBox_Username = Sprite::create("UI/GameScene/bgEditBox.png");
	sp_EditBox_Username->setPosition(editBox_Username->getPosition());
	Tool::setNodeSize(sp_EditBox_Username, editBox_Username->getBoundingBox().size.width, editBox_Username->getBoundingBox().size.height);
	this->addChild(sp_EditBox_Username, -1);

	auto sp_EditBox_Password = Sprite::create("UI/GameScene/bgEditBox.png");
	sp_EditBox_Password->setPosition(editBox_Password->getPosition());
	Tool::setNodeSize(sp_EditBox_Password, editBox_Password->getBoundingBox().size.width, editBox_Password->getBoundingBox().size.height);
	this->addChild(sp_EditBox_Password, -1);

	btn_Login = Button::create("UI/LobbyScene/btn_Login_nomal.png","UI/LobbyScene/btn_Login_select.png");
	btn_Login->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.3));
	btn_Login->setName("btn_Login");
	btn_Login->addTouchEventListener(CC_CALLBACK_2(LoginScene::btn_Click, this));
	this->addChild(btn_Login);

	btn_Register = Button::create("UI/LobbyScene/btn_Register_nomal.png", "UI/LobbyScene/btn_Register_select.png");
	btn_Register->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.3));
	btn_Register->setName("btn_Register");
	btn_Register->addTouchEventListener(CC_CALLBACK_2(LoginScene::btn_Click, this));
	this->addChild(btn_Register);

	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	this->addChild(lbl_Notify,1);
}



void LoginScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}
