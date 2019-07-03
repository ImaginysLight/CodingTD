#pragma once
#include "cocos2d.h"
#include "GlobalClass/Tool.h"
#include "GlobalClass/Audio.h"
#include "LobbyScene.h"
#include "ui/CocosGUI.h"
#include"RegisterScene.h"
using namespace cocos2d::ui;
using namespace std;
using namespace cocos2d::network;

USING_NS_CC;
class LoginScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LoginScene);

	Size visibleSize;
	Label* lbl_Notify;
	EditBox *editBox_Username, *editBox_Password, *editBox_Domain;
	Button *btn_Login, *btn_Register;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void onReceiveEvent(SIOClient* client, const std::string& data);
	void onReceiveEvent_GetPlayerInfo(SIOClient * client, const std::string & data);

};

