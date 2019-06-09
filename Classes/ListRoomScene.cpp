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

	string id = to_string(Player::currentPlayer->id);
	Tool::Socket_Client->_client->emit("_Get_List_Room_", "{\"id\":\"" + id + "\"}");

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

	auto row = CreateRow_Default();
	row->setPosition(Vec2(visibleSize.width*0.2f, visibleSize.height*0.7f));
	this->addChild(row);

	if (document["_Get_List_Room_"]["CountRoom"].GetInt() != 0)
	{
		//check name has member in json
		CCLOG("ROOM: %d ", document["_Get_List_Room_"]["CountRoom"].GetInt());
		for (int i = 0; i <= document["_Get_List_Room_"]["CountRoom"].GetInt(); i++)
		{
			if (i == 0)
			{
				auto height = 50 * 50 + 500;
				scrollView_ListRoom->setInnerContainerSize(Size(1000, height));
				auto row = CreateRow(" ", " ", " ");
				row->setPosition(Vec2(50, height - 50 * i));
				scrollView_ListRoom->addChild(row);
			}
			else
			{
				std::string id = to_string(i - 1);
				std::string Room = "Room";
				Room.insert(Room.length(), id);
				Room = to_string(document["_Get_List_Room_"][Room.c_str()].GetInt());
				string username = "username";
				username.insert(username.length(), id);
				username = document["_Get_List_Room_"][username.c_str()].GetString();

				//CCLOG("Room_id: %d ", document["_Get_List_Room_"][Room.c_str()].GetInt());

				auto height = 50 * 50 + 500;
				scrollView_ListRoom->setInnerContainerSize(Size(1000, height));
				auto row = CreateRow(to_string(i), username, Room);
				row->setPosition(Vec2(50, height - 50 * i));
				scrollView_ListRoom->addChild(row);
			}
		}
	}
	else
	{
		Label* lbl_ThongBao = Tool::CreateLabel("No Room");
		lbl_ThongBao->setPosition(visibleSize / 2);
		lbl_ThongBao->setSystemFontSize(30);
		lbl_ThongBao->setColor(Color3B::GRAY);
		this->addChild(lbl_ThongBao);
	}
}
void ListRoomScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	Button* term;
	switch (type)
	{
	case Widget::TouchEventType::ENDED:
	{
		term = (Button*)pSender;
		if (term->getName() == "btn_CreateRoom") {
			string id = to_string(Player::currentPlayer->id);
			Tool::Socket_Client->_client->emit("Create_Room", "{\"id\":\"" + id + "\"}");
			Director::getInstance()->replaceScene(MyRoomScene::createScene());
		}
		else if (term->getName() == "btn_Exit") {
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
		else
		{
			Tool::Socket_Client->_client->emit("Join_Room", "{\"CurrentId\":\"" + to_string(Player::currentPlayer->id) +"\", \"OppenontId\":\"" + term->getName() + "\"}");
			Director::getInstance()->replaceScene(MyRoomScene::createScene());
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

	auto sp_Background = Sprite::create("UI/LoginScene/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	//scroll view
	scrollView_ListRoom = ui::ScrollView::create();
	scrollView_ListRoom->setContentSize(Size(700, 300));
	//ScrollView_RankingTable->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	scrollView_ListRoom->setInnerContainerSize(Size(1000, 2000));
	scrollView_ListRoom->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.4f));
	scrollView_ListRoom->setAnchorPoint(Vec2(0.5, 0.5));
	scrollView_ListRoom->setBounceEnabled(true);
	this->addChild(scrollView_ListRoom);

	btn_Exit = Button::create("UI/LobbyScene/btn_Exit_nomal.png", "UI/LobbyScene/btn_Exit_select.png");
	btn_Exit->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.1));
	btn_Exit->setName("btn_Exit");
	btn_Exit->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
	this->addChild(btn_Exit);

}


void ListRoomScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

Node * ListRoomScene::CreateRow(string stt, string name, string id)
{
	Node* result = Node::create();

	Label* lbl_stt = Tool::CreateLabel((stt));
	//lbl_stt->setPositionX();
	result->addChild(lbl_stt);

	Label* lbl_Name = Tool::CreateLabel(name);
	lbl_Name->setPositionX(250);
	result->addChild(lbl_Name);

	if (id != " ")
	{
		auto btn_room = Button::create("UI/LobbyScene/btn_Join_nomal.png", "UI/LobbyScene/btn_Join_select.png");
		btn_room->setPositionX(550);
		btn_room->setName(id);
		btn_room->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
		result->addChild(btn_room);
	}

	auto line = Sprite::create("UI/BG/line.png");
	line->setPositionX(visibleSize.width  *0.3f);
	result->addChild(line);

	return result;
}

Node * ListRoomScene::CreateRow_Default()
{
	Node* result = Node::create();

	Label* lbl_stt = Tool::CreateLabel("Numerical Order");
	//lbl_stt->setPositionX();
	result->addChild(lbl_stt);

	Label* lbl_Name = Tool::CreateLabel("Name");
	lbl_Name->setPositionX(250);
	result->addChild(lbl_Name);

	auto btn_CreateRoom = Button::create("UI/LobbyScene/btn_Create_nomal.png", "UI/LobbyScene/btn_Create_select.png");
	btn_CreateRoom->setPositionX(540);
	btn_CreateRoom->setName("btn_CreateRoom");
	btn_CreateRoom->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
	result->addChild(btn_CreateRoom);

	return result;
}