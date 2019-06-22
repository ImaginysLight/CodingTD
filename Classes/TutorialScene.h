#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include <vector>
#include "GlobalClass/Tool.h"
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
	vector<Label*> vecLabel;
	vector<Sprite*> vecSprite;
	vector<string> labelContent;
	Button *btn_Exit;
	ui::ScrollView *ScrollView_TutorialList;
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
};
