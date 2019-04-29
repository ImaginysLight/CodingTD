#pragma once
#include "cocos2d.h"
#include"Object/Tool.h"
#include"TutorialScene.h"
USING_NS_CC;
class LobbyScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(LobbyScene);

	Size visibleSize;
	Label* lbl_Notify;
	Button *btn_Extend, *btn_Play, *btn_Rank, *btn_Tutorial;

	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);

};

