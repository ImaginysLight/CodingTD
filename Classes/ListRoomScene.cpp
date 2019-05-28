#include"ListRoomScene.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include <network/SocketIO.h>
#include "Global Class/Tool.h"

USING_NS_CC;



Scene* ListRoomScene::createScene()
{
	return ListRoomScene::create();
}

bool ListRoomScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	SetupGUI();
 	Tool::Socket_Client->_client->on("_Get_List_Room_", CC_CALLBACK_2(ListRoomScene::onReceiveEvent, this));
	return true;
}

void ListRoomScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}  

void ListRoomScene::onReceiveEvent(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	CCLOG("ROOM: %d ", document["_Get_List_Room_"]["CountRoom"].GetInt());
	for (int i = 0; i < document["_Get_List_Room_"]["CountRoom"].GetInt(); i++)
	{
		std::string id = to_string(i);
		std::string Room = "Room";
		Room.insert(Room.length(), id);
		auto *button = ui::Button::create("CloseNormal.png", "CloseSelected.png");
		button->setTitleText(to_string(document["_Get_List_Room_"][Room.c_str()].GetInt()));
		button->setTitleColor(Color3B::RED);
		button->setTitleFontSize(30);
		scrollView->addChild(button);
		CCLOG("Room_id: %d ", document["_Get_List_Room_"][Room.c_str()].GetInt());
	}
}
void ListRoomScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	Button* term;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		term = (Button*)pSender;
		if (term->getName() == "btn_Login") {
			string id = to_string(Tool::currentPlayer->id);
			Tool::Socket_Client->_client->emit("_Get_List_Room_", "{\"id\":\"" + id + "\"}");
		}
		else if (term->getName() == "btn_Register") {
			Director::getInstance()->end();
		}
	}
	default: break;
	}
}

void ListRoomScene::SetupGUI()
{
	auto sp_SceneName = Sprite::create("UI/LoginScene/Login.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.9));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/LoginScene/background.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	editBox_Username = ui::EditBox::create(Size(visibleSize.width/2, 30),"", "");
	editBox_Username->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
	editBox_Username->setTextHorizontalAlignment(TextHAlignment::CENTER);
	editBox_Username->setFontSize(Tool::defaultTextSize);
	editBox_Username->setFontColor(Color3B(175,225,200));
	editBox_Username->setPlaceHolder("Username");
	editBox_Username->setPlaceholderFontColor(Color3B::GRAY);
	editBox_Username->setMaxLength(20);
	this->addChild(editBox_Username);

	//scroll view
	Size scollFrameSize = Size(visibleSize.width - 30.f, visibleSize.height - 10.f);
	scrollView = ScrollView::create();
	//scrollView->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	scrollView->setBackGroundColor(Color3B(200, 200, 200));
	scrollView->setSize(scollFrameSize);
	scrollView->setPosition(Point(15, 5));
	scrollView->setDirection(SCROLLVIEW_DIR_VERTICAL);

	auto containerSize = Size(scollFrameSize.width, scollFrameSize.height * 2);
	scrollView->setInnerContainerSize(containerSize);

	scrollView->setLayoutType(LAYOUT_LINEAR_VERTICAL);

	/*for (int i = 0; i < 30; i++) {
		auto *button = ui::Button::create("CloseNormal.png", "CloseSelected.png");
		scrollView->addChild(button);
	}*/
	addChild(scrollView);

	btn_Login = Button::create("UI/LoginScene/btn_Login_nomal.png", "UI/LoginScene/btn_Login_select.png");
	btn_Login->setPosition(Vec2(visibleSize.width*0.4, visibleSize.height*0.3));
	btn_Login->setName("btn_Login");
	btn_Login->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
	this->addChild(btn_Login);

}



void ListRoomScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}