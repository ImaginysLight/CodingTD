#pragma once
#include "cocos2d.h"
#include"Global Class/Tool.h"
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
	ui::ScrollView *ScrollView_RankingTable;

	Node* CreateRow(int id, string name, int stat1, int stat2);
	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

};

