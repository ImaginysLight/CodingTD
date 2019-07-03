#pragma once
#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "GlobalClass/Tool.h"
#include "LoginScene.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace std;

class RegisterScene : public cocos2d::Scene
{
private:
	

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(RegisterScene);
	Label* lbl_Notify;
	Size visibleSize;
	EditBox *editBox_Username, *editBox_Password, *editBox_RetypePassword, *editBox_SecurityCode;
	string code = "";
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void SetupGUI();
	void RunActionNotify(string content);
	void onReceiveEvent_Register(SIOClient* client, const std::string& data);
};
