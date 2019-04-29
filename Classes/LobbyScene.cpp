#include"LobbyScene.h"
USING_NS_CC;

Scene* LobbyScene::createScene()
{
	return LobbyScene::create();
}

bool LobbyScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();

	return true;
}

void LobbyScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void LobbyScene::SetupGUI()
{
	auto sp_SceneName = Sprite::create("UI/LobbyScene/Lobby.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/LoginScene/background.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	lbl_Notify = Label::createWithTTF("", "fonts/arial.ttf", Tool::defaultTextSize);
	lbl_Notify->setTextColor(Color4B::RED);
	lbl_Notify->runAction(FadeOut::create(0));
	lbl_Notify->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.1));
	this->addChild(lbl_Notify,1);

	btn_Play = Button::create("UI/LobbyScene/btn_Play_nomal.png", "UI/LobbyScene/btn_Play_select.png");
	btn_Play->setName("btn_Play");
	btn_Play->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.25));
	btn_Play->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Play);

	btn_Rank = Button::create("UI/LobbyScene/btn_Rank_nomal.png", "UI/LobbyScene/btn_Rank_select.png");
	btn_Rank->setName("btn_Rank");
	btn_Rank->setPosition(Vec2(visibleSize.width*0.25, visibleSize.height*0.08));
	btn_Rank->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Rank);

	btn_Tutorial = Button::create("UI/LobbyScene/btn_Tutorial_nomal.png", "UI/LobbyScene/btn_Tutorial_select.png");
	btn_Tutorial->setName("btn_Tutorial");
	btn_Tutorial->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.08));
	btn_Tutorial->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Tutorial);

	btn_Extend = Button::create("UI/LobbyScene/btn_Extend_nomal.png", "UI/LobbyScene/btn_Extend_select.png");
	btn_Extend->setName("btn_Extend");
	btn_Extend->setPosition(Vec2(visibleSize.width*0.75, visibleSize.height*0.08));
	btn_Extend->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btn_Click, this));
	this->addChild(btn_Extend);

	auto lbl_Username = Tool::CreateLabel(Tool::currentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_Username->setPosition(visibleSize / 2);
	this->addChild(lbl_Username);

}

void LobbyScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Button*)pSender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		if (name == "btn_Tutorial") {
			Director::getInstance()->replaceScene(TutorialScene::createScene());
		}
	}
}

void LobbyScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}