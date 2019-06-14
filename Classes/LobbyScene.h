#pragma once
#include "cocos2d.h"
#include"Global Class/Tool.h"
#include"TutorialScene.h"
#include"LoginScene.h"
//#include "Object\SocketClient.h" 
#include "GameScene.h"
#include "RankingScene.h"
#include "ListRoomScene.h"
#include "ChooseCardScene.h"
#include"PlayerInformationScene.h"

#include <network/SocketIO.h>
using namespace cocos2d::network;
using namespace cocos2d::ui;

USING_NS_CC;
class LobbyScene : public cocos2d::Scene //, public SocketIO::SIODelegate
{
public:
	//SIOClient *_client;
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LobbyScene);

	static string notify;
	Size visibleSize;
	Label* lbl_Notify;
	Button *btn_Extend, *btn_Play, *btn_Rank, *btn_Tutorial, *btn_Logout,*btn_Info;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void findTheOpponent(SIOClient* client, const std::string& data);
	void onReceiveEvent_GetPlayerInfo(SIOClient* client, const std::string& data);
};

