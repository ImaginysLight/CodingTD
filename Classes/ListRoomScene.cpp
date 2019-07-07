#include"ListRoomScene.h"


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

	if (document["_Get_List_Room_"]["CountRoom"].GetInt() != 0)
	{
		//check name has member in json
		CCLOG("ROOM: %d ", document["_Get_List_Room_"]["CountRoom"].GetInt());
		int size = document["_Get_List_Room_"]["CountRoom"].GetInt();
		int height = 50 * size;
		scrollView_ListRoom->setInnerContainerSize(Size(1000, height));
		for (int i = 0; i < document["_Get_List_Room_"]["CountRoom"].GetInt(); i++)
		{
				std::string id = to_string(i);
				std::string Room = "Room";
				Room.insert(Room.length(), id);
				Room = to_string(document["_Get_List_Room_"][Room.c_str()].GetInt());
				string username = "username";
				username.insert(username.length(), id);
				username = document["_Get_List_Room_"][username.c_str()].GetString();

				//CCLOG("Room_id: %d ", document["_Get_List_Room_"][Room.c_str()].GetInt());
				auto row = CreateRow(to_string(i), username, Room);
				row->setPosition(Vec2(50, scrollView_ListRoom->getInnerContainerSize().height - 50 * i - 50));
				scrollView_ListRoom->addChild(row);
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
		else if (term->getName() == "btn_Refresh") {
			scrollView_ListRoom->removeAllChildrenWithCleanup(true);
			string id = to_string(Player::currentPlayer->id);
			Tool::Socket_Client->_client->emit("_Get_List_Room_", "{\"id\":\"" + id + "\"}");
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
	auto sp_SceneName = Sprite::create("UI/Room/head_room.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height*0.8));
	this->addChild(sp_SceneName);

	auto sp_Background = Sprite::create("UI/Login/BG.png");
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

	btn_Exit = Button::create("UI/Room/btn_back.png");
	btn_Exit->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.1));
	btn_Exit->setName("btn_Exit");
	btn_Exit->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
	this->addChild(btn_Exit);

	auto btn_CreateRoom = Button::create("UI/Room/btn_create.png");
	btn_CreateRoom->setPosition(Vec2(visibleSize.width*0.40, visibleSize.height*0.1));
	btn_CreateRoom->setName("btn_CreateRoom");
	btn_CreateRoom->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
	this->addChild(btn_CreateRoom);

	auto btn_Refresh = Button::create("UI/Room/btn_refresh.png");
	btn_Refresh->setPosition(Vec2(visibleSize.width*0.60, visibleSize.height*0.1));
	btn_Refresh->setName("btn_Refresh");
	btn_Refresh->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
	this->addChild(btn_Refresh);
}


void ListRoomScene::RunActionNotify(string content)
{
	lbl_Notify->setString(content);
	lbl_Notify->runAction(Sequence::create(FadeIn::create(0.75), DelayTime::create(0.75), FadeOut::create(1), nullptr));
}

Node * ListRoomScene::CreateRow(string stt, string name, string id)
{
	Node* result = Node::create();

	if (id != " ")
	{
		auto btn_join = Button::create("UI/Room/btn_Join.png");
		btn_join->setPositionX(550);
		btn_join->setName(id);
		btn_join->addTouchEventListener(CC_CALLBACK_2(ListRoomScene::btn_Click, this));
		result->addChild(btn_join);

		auto line = Sprite::create("UI/Room/table.png");
		line->setPositionX(visibleSize.width  *0.25f);
		result->addChild(line);

		Label* lbl_Name = Tool::CreateLabel(name);
		lbl_Name->setPositionX(250);
		result->addChild(lbl_Name);
	}

	return result;
}