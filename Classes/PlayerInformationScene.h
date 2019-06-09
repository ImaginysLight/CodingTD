#pragma once
#include"Global Class/Trophy.h"
#include"Global Class/Player.h"
#include"Global Class/Tool.h"
#include"CardScene.h"
#include"cocos2d.h"
using namespace cocos2d::ui;
USING_NS_CC;

class PlayerInformationScene : public cocos2d::Scene //, public SocketIO::SIODelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(PlayerInformationScene);

	Size visibleSize;
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
};