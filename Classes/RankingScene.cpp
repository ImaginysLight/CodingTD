#include"RankingScene.h"

USING_NS_CC;

Scene* RankingScene::createScene()
{
	return RankingScene::create();
}

bool RankingScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	SetupGUI();
	Tool::Socket_Client->_client->on("_Get_List_Rank_", CC_CALLBACK_2(RankingScene::onReceiveEvent, this));
	string id = to_string(Player::currentPlayer->id);
	Tool::Socket_Client->_client->emit("_Get_List_Rank_", "{\"id\":\"" + id + "\"}");
	return true;
}

void RankingScene::onReceiveEvent(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	//CCLOG("RANK: %d ", document["_Get_List_Rank_"]["CountRank"].GetInt());

	auto row = CreateRow_Default();
	row->setPosition(Vec2(visibleSize.width*0.185f, visibleSize.height*0.70f));
	this->addChild(row);

	int size = document["_Get_List_Rank_"]["CountRank"].GetInt();
	int height = size * 50 + 100;
	ScrollView_RankingTable->setInnerContainerSize(Size(1000, height));
	for (int i = 0; i < size; i++)
	{

		std::string stt = to_string(i);
		std::string id = "id";
		id = "username";
		id.insert(id.length(), stt);
		string username = document["_Get_List_Rank_"][id.c_str()].GetString();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetString());
		id = "total_win";
		id.insert(id.length(), stt);
		int total_win = document["_Get_List_Rank_"][id.c_str()].GetInt();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetInt());
		id = "correct_answer";
		id.insert(id.length(), stt);
		int correct_answer = document["_Get_List_Rank_"][id.c_str()].GetInt();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetInt());

		auto row = CreateRow(to_string(i+1), username, to_string(total_win), to_string(correct_answer));
		row->setPosition(Vec2(50, height - 50 * (i+1)));
		ScrollView_RankingTable->addChild(row);

	}

	auto rowCurrentPlayer = CreateRowCurrentPlayer("100","username","total win", "correct answer");
	rowCurrentPlayer->setPosition(Vec2(visibleSize.width*0.185f, visibleSize.height*0.2));
	this->addChild(rowCurrentPlayer);
}

void RankingScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

Node * RankingScene::CreateRow(string stt, string name, string win, string correct_answer)
{
	Node* result = Node::create();

	Label* lbl_stt = Tool::CreateLabel((stt));
	lbl_stt->setPositionX(50);
	result->addChild(lbl_stt);

	Label* lbl_Name = Tool::CreateLabel(name);
	lbl_Name->setPositionX(200);
	result->addChild(lbl_Name);

	Label* lbl_total_score = Tool::CreateLabel((win));
	lbl_total_score->setPositionX(350);
	result->addChild(lbl_total_score);

	Label* lbl_total_question = Tool::CreateLabel((correct_answer));
	lbl_total_question->setPositionX(500);
	result->addChild(lbl_total_question);

	if (stt == "1") {
		auto line = Sprite::create("UI/rank/table1.png");
		line->setPosition(Vec2(visibleSize.width  *0.3f, 0));
		result->addChild(line, -1);
	}
	else if (stt == "2") {
		auto line = Sprite::create("UI/rank/table2.png");
		line->setPosition(Vec2(visibleSize.width  *0.3f, 0));
		result->addChild(line, -1);
	}
	else {
		auto line = Sprite::create("UI/rank/table3.png");
		line->setPosition(Vec2(visibleSize.width  *0.3f, 0));
		result->addChild(line, -1);
	}
	
	
	return result;
}

Node * RankingScene::CreateRowCurrentPlayer(string stt, string name, string win, string correct_answer)
{
	Node* result = Node::create();

	Label* lbl_stt = Tool::CreateLabel((stt));
	lbl_stt->setPositionX(50);
	result->addChild(lbl_stt);

	Label* lbl_Name = Tool::CreateLabel(name);
	lbl_Name->setPositionX(200);
	result->addChild(lbl_Name);

	Label* lbl_total_score = Tool::CreateLabel((win));
	lbl_total_score->setPositionX(350);
	result->addChild(lbl_total_score);

	Label* lbl_total_question = Tool::CreateLabel((correct_answer));
	lbl_total_question->setPositionX(500);
	result->addChild(lbl_total_question);


	auto line = Sprite::create("UI/rank/table4.png");
	line->setPosition(Vec2(visibleSize.width  *0.3f, 0));
	result->addChild(line, -1);



	return result;
}

Node * RankingScene::CreateRow_Default()
{
	Node* result = Node::create();

	Label* lbl_stt = Tool::CreateLabel("Rank");
	lbl_stt->setPositionX(50);
	result->addChild(lbl_stt);

	Label* lbl_Name = Tool::CreateLabel("Name");
	lbl_Name->setPositionX(200);
	result->addChild(lbl_Name);

	Label* lbl_total_score = Tool::CreateLabel("Total Win");
	lbl_total_score->setPositionX(350);
	result->addChild(lbl_total_score);

	Label* lbl_total_question = Tool::CreateLabel("Total Question");
	lbl_total_question->setPositionX(500);
	result->addChild(lbl_total_question);

	return result;
}

void RankingScene::SetupGUI()
{
	auto sp_Background = Sprite::create("UI/Login/BG.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto sp_SceneName = Sprite::create("UI/rank/head_rank.png");
	sp_SceneName->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.8));
	this->addChild(sp_SceneName);

	ScrollView_RankingTable = ui::ScrollView::create();
	ScrollView_RankingTable->setContentSize(Size(700, 200));
	//ScrollView_RankingTable->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	ScrollView_RankingTable->setInnerContainerSize(Size(1000, 2000));
	ScrollView_RankingTable->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.45f));
	ScrollView_RankingTable->setAnchorPoint(Vec2(0.5, 0.5));
	ScrollView_RankingTable->setBounceEnabled(true);
	this->addChild(ScrollView_RankingTable);

	btn_Exit = Button::create("UI/Lobby/btn_exit.png");
	btn_Exit->setPosition(Vec2(visibleSize.width*0.85, visibleSize.height * 0.1));
	btn_Exit->addTouchEventListener(CC_CALLBACK_2(RankingScene::btn_Click, this));
	btn_Exit->setName("btn_Exit");
	this->addChild(btn_Exit);

	//Giả sử có 50 dòng và mỗi dòng chiếm khoảng 50 pixel => tổng cộng 2500 pixel + dư ra tí cho đẹp
	//auto height = 50 * 50 + 500;
	//ScrollView_RankingTable->setInnerContainerSize(Size(1000, height));
	//for (int i = 1; i < 51; i++) {
	//	//Vì gốc của cái ScrollView nằm ở góc trái dưới, nên cái trên đầu sẽ có height cao nhất.
	//	auto row = CreateRow(i, to_string(i), 1, 2);
	//	row->setPosition(Vec2(50, height - 50 * i));
	//	ScrollView_RankingTable->addChild(row);
	//}
}

void RankingScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Button*)pSender)->getName();
	if (name == "btn_Exit")
	{
		//ScrollView_RankingTable->removeAllChildrenWithCleanup(true);
		Director::getInstance()->replaceScene(LobbyScene::createScene());
	}
}

void RankingScene::RunActionNotify(string content)
{
	
}