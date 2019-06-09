#pragma once

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "extensions/cocos-ext.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "Global Class/Tool.h"
#include "LobbyScene.h"
USING_NS_CC;

using namespace cocos2d::ui;
using namespace std;

class TutorialScene : public cocos2d::Scene
{
private:
	

public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(TutorialScene);

	Size visibleSize;
	int currentPage = 0;
	void onClick(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	vector<Label*> vecLabel;
	vector<Sprite*> vecSprite;
	Button* btn_Back, *btn_Next, *btn_Exit;
};
