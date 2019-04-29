#include"TutorialScene.h"
#include "SimpleAudioEngine.h"
using namespace cocos2d::ui;
USING_NS_CC;


Scene* TutorialScene::createScene()
{
	return TutorialScene::create();
}


bool TutorialScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();

	//Label chữ tutorial (tạo cái sprite coi)
	{
		Label* lbl_Tutorial = Label::createWithTTF("Tutorial", "fonts/arial.ttf", Tool::defaultTextSize*2);
		lbl_Tutorial->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*.9));
		this->addChild(lbl_Tutorial);
	}

	// Button ← →
	{
		btn_Back = Button::create();
		btn_Back->setTitleText(Tool::ConvertUTF16ToString(L"← Back"));
		btn_Back->setTitleFontSize(Tool::defaultTextSize * 1.5);
		btn_Back->setTitleColor(Color3B::GREEN);
		btn_Back->setPosition(Vec2(visibleSize.width*0.08, visibleSize.height / 2));
		btn_Back->addTouchEventListener(CC_CALLBACK_2(TutorialScene::onClick, this));
		btn_Back->setName("btn_Back");
		this->addChild(btn_Back);

		btn_Next = Button::create();
		btn_Next->setTitleText(Tool::ConvertUTF16ToString(L"Next →"));
		btn_Next->setTitleFontSize(Tool::defaultTextSize * 1.5);
		btn_Next->setTitleColor(Color3B::GREEN);
		btn_Next->setPosition(Vec2(visibleSize.width*0.92, visibleSize.height / 2));
		btn_Next->addTouchEventListener(CC_CALLBACK_2(TutorialScene::onClick, this));
		btn_Next->setName("btn_Next");
		this->addChild(btn_Next);
	}

	// Thông tin hướng dẫn
	{
		//Trang 1 
		{
			Label* lbl = Label::createWithTTF(Tool::ConvertUTF16ToString(L"Đây là hướng dẫn game, và đây là trang 1!"),"fonts/arial.ttf",Tool::defaultTextSize);
			vecLabel.push_back(lbl);

			Sprite* sp = Sprite::create("UI/TutorialScene/background.png");
			vecSprite.push_back(sp);
		}

		//Trang 2
		{
			Label* lbl = Label::createWithTTF(Tool::ConvertUTF16ToString(L"Đây là hướng dẫn game, và đây là trang 2!"), "fonts/arial.ttf", Tool::defaultTextSize);
			vecLabel.push_back(lbl);

			Sprite* sp = Sprite::create("UI/TutorialScene/background.png");
			vecSprite.push_back(sp);
		}

		//Trang 2
		{
			Label* lbl = Label::createWithTTF(Tool::ConvertUTF16ToString(L"Đây là hướng dẫn game, và đây là trang 3!"), "fonts/arial.ttf", Tool::defaultTextSize);
			vecLabel.push_back(lbl);

			Sprite* sp = Sprite::create("UI/TutorialScene/background.png");
			vecSprite.push_back(sp);
		}

	}

	//Set thông số cho các Label và Sprite trong Tutorial
	{
		for (auto lbl : vecLabel) {
			lbl->setVisible(false);
			lbl->setWidth(500);
			lbl->setAlignment(CCTextAlignment::CENTER);
			lbl->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.2));
			lbl->setAnchorPoint(Vec2(0.5, 1));
			this->addChild(lbl);
		}
		for (auto sp : vecSprite) {
			sp->setVisible(false);
			Tool::setNodeSize(sp, 550, 300);
			sp->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.5));
			this->addChild(sp);
		}
		
	}

	//Hiển thị trang 1
	{
		vecLabel[currentPage]->setVisible(true);
		vecSprite[currentPage]->setVisible(true);
	}

	return true;
}


void TutorialScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

void TutorialScene::onClick(Ref * sender, Widget::TouchEventType type)
{
	string name = ((Node*)sender)->getName();
	if (type == Widget::TouchEventType::ENDED) {
		// Back
		if (name == "btn_Back") {
			if (currentPage > 0) {
				//Khóa button trong lúc chuyển trang
				btn_Back->setEnabled(false);
				btn_Next->setEnabled(false);
				vecLabel[currentPage]->runAction(Sequence::create(DelayTime::create(2.5),
					CallFunc::create([&]() {	btn_Back->setEnabled(true);
												btn_Next->setEnabled(true);
												currentPage--;
					}),
				nullptr));

				// Hiệu ứng chuyển trang cũ
				vecLabel[currentPage]->runAction(Sequence::create(MoveBy::create(1, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false);
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage]->runAction(Sequence::create(MoveBy::create(1, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false);
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));

				// Hiệu ứng đổi trang mới

				vecLabel[currentPage - 1]->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage - 1]->setVisible(true);
												vecSprite[currentPage - 1]->setVisible(true);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage - 1]->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage - 1]->setVisible(true);
												vecSprite[currentPage - 1]->setVisible(true);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));
			}
		}
		// Next
		else if (name == "btn_Next") {
			if (currentPage < vecLabel.size()-1) {
				//Khóa button trong lúc chuyển trang
				btn_Back->setEnabled(false);
				btn_Next->setEnabled(false);
				vecLabel[currentPage]->runAction(Sequence::create(DelayTime::create(2.5),
					CallFunc::create([&]() {	btn_Back->setEnabled(true);
												btn_Next->setEnabled(true);
												currentPage++;
					}), 
				nullptr));

				// Hiệu ứng chuyển trang cũ
				vecLabel[currentPage]->runAction(Sequence::create(MoveBy::create(1, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false); 
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage]->runAction(Sequence::create(MoveBy::create(1, Vec2(-1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage]->setVisible(false);
												vecSprite[currentPage]->setVisible(false);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));
				
				// Hiệu ứng đổi trang mới

				vecLabel[currentPage+1]->runAction(Sequence::create(MoveBy::create(0.5, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage+1]->setVisible(true);
												vecSprite[currentPage+1]->setVisible(true);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.2)),
				nullptr));

				vecSprite[currentPage+1]->runAction(Sequence::create(MoveBy::create(0.5, Vec2(1000, 0)),
					CallFunc::create([&]() {	vecLabel[currentPage+1]->setVisible(true);
												vecSprite[currentPage+1]->setVisible(true);
					}),
					MoveTo::create(1, Vec2(visibleSize.width / 2, visibleSize.height*0.5)),
				nullptr));
			}
		}
	}

}

