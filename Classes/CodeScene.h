#pragma once
#include "cocos2d.h"
#include"Global Class/Tool.h"
#include"LobbyScene.h"
//#include "Object/SocketClient.h"

#include <network/SocketIO.h>
using namespace cocos2d::network;
using namespace cocos2d::ui;

USING_NS_CC;
class CodeScene : public cocos2d::Scene //, public SocketIO::SIODelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(CodeScene);

	Size visibleSize;
	Label* lbl_Notify;
	EditBox *editBox_Username, *editBox_Password;
	Button *btn_Login, *btn_Register;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void onReceiveEvent(SIOClient* client, const std::string& data);
};

