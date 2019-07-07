#pragma once
#include "cocos2d.h"
#include"GlobalClass/Tool.h"
#include"LobbyScene.h"
USING_NS_CC;
class RankingScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(RankingScene);

	Size visibleSize;
	Button *btn_Exit;
	ui::ScrollView *ScrollView_RankingTable;
	

	Node* CreateRow(string stt, string name, string score, string question, string total_kill);
	Node* CreateRow_Default();
	Node* CreateRowCurrentPlayer(string stt, string name, string win, string correct_answer, string total_kill);
	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

	void onReceiveEvent(SIOClient* client, const std::string& data);

};

