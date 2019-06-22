#pragma once
#include"GlobalClass/Trophy.h"
#include"GlobalClass/Player.h"
#include"GlobalClass/Tool.h"
#include"GlobalClass/Audio.h"
#include"LobbyScene.h"
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