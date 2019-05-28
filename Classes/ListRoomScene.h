#pragma once
#include "cocos2d.h"
#include"Global Class/Tool.h"
#include <network/SocketIO.h>
using namespace cocos2d::network;
using namespace cocos2d::ui;

#include "ui/CocosGUI.h"

USING_NS_CC;
//USING_NS_CC_EXT; 

class ListRoomScene : public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(ListRoomScene);

	Size visibleSize;
	Label* lbl_Notify;
	EditBox *editBox_Username, *editBox_Password;
	Button *btn_Login, *btn_Register;
	ScrollView *scrollView;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void onReceiveEvent(SIOClient* client, const std::string& data);

};