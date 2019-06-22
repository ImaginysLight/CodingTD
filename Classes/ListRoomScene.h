#pragma once
#include "cocos2d.h"
#include"GlobalClass/Tool.h"
#include "LobbyScene.h"
#include "MyRoomScene.h"
using namespace cocos2d::network;
using namespace cocos2d::ui;

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
	Button *btn_Login, *btn_Register, *btn_Exit;
	ScrollView *scrollView_ListRoom;

	Node* CreateRow(string stt, string name, string id);
	Node* CreateRow_Default();
	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void onReceiveEvent(SIOClient* client, const std::string& data);

};