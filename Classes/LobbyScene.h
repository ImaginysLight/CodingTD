#pragma once
#include "cocos2d.h"
#include"GlobalClass/Tool.h"
#include"GlobalClass/Player.h"
#include"TutorialScene.h"
#include"LoginScene.h"
#include "GameScene.h"
#include "RankingScene.h"
#include "ListRoomScene.h"
#include "ChooseCardScene.h"
#include"PlayerInformationScene.h"

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
	Button *btn_Room, *btn_Play, *btn_Rank, *btn_Tutorial, *btn_Logout,*btn_Achievement;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void findTheOpponent(SIOClient* client, const std::string& data);
	void UpdateAudio(float time);

};

