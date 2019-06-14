#pragma once
#include "cocos2d.h"
#include"Global Class/Tool.h"
#include"Global Class/Player.h"
#include"LobbyScene.h"
#include"GameScene.h"

#include <network/SocketIO.h>
using namespace cocos2d::network;
using namespace cocos2d::ui;

USING_NS_CC;
class ChooseCardScene : public cocos2d::Scene //, public SocketIO::SIODelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(ChooseCardScene);

	Size visibleSize;
	int timer = 0, turn = 0, counter = 0;
	Label* lbl_Notify, *lbl_Turn, *lbl_Cooldown, *lbl_CurrentPlayerPick, *lbl_OpponentPlayerPick,*lbl_CurrentPlayerName,*lbl_OpponentPlayerName;
	Vec2 currentPlayerPosition, opponentPlayerPosition;
	EditBox *editBox_Username, *editBox_Password;
	Button *btn_Login, *btn_Register;
	vector<Button*> vecButton;
	vector<pair<int, string>> bannedCard;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_BanCard_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_ChooseKingdom_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);
	void UpdateEachSecond(float time);
	void ChangeTurn();

	void onReceive_BanCard(SIOClient* client, const std::string& data);
	void onReceive_PickCard(SIOClient* client, const std::string& data);
	void onReceive_SelectElement(SIOClient* client, const std::string& data);
	void onReceiveEvent_GetInfoPlayer(SIOClient* client, const std::string& data);
};

