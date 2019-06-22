#pragma once
#include "cocos2d.h"
#include"GlobalClass/Tool.h"
#include"GlobalClass/Audio.h"
#include"LobbyScene.h"
USING_NS_CC;
class ResultScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(ResultScene);

	static int numOfCorrectAnswer;
	static int numOfWrongAnswer;
	static int numOfEnemyDefeated;
	static float goldReceived;
	static bool isVictorious;

	Size visibleSize;
	void SetupGUI();
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
};

