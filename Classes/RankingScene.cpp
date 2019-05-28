﻿#include"RankingScene.h"

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
	string id = to_string(Tool::currentPlayer->id);
	Tool::Socket_Client->_client->emit("_Get_List_Rank_", "{\"id\":\"" + id + "\"}");
	return true;
}

void RankingScene::onReceiveEvent(SIOClient* client, const std::string& data)
{
	rapidjson::Document document;
	document.Parse<0>(data.c_str());
	//check name has member in json
	//CCLOG("RANK: %d ", document["_Get_List_Rank_"]["CountRank"].GetInt());
	for (int i = 0; i < document["_Get_List_Rank_"]["CountRank"].GetInt(); i++)
	{
		std::string stt = to_string(i);
		std::string id = "id";
		id.insert(id.length(), stt);
		int Id = document["_Get_List_Rank_"][id.c_str()].GetInt();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetInt());
		id = "username";
		id.insert(id.length(), stt);
		string username = document["_Get_List_Rank_"][id.c_str()].GetString();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetString());
		id = "total_score";
		id.insert(id.length(), stt);
		int total_score = document["_Get_List_Rank_"][id.c_str()].GetInt();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetInt());
		id = "total_question";
		id.insert(id.length(), stt);
		int total_question = document["_Get_List_Rank_"][id.c_str()].GetInt();
		//CCLOG("Rank_id: %d ", document["_Get_List_Rank_"][id.c_str()].GetInt());

		

		auto height = 50 * 50 + 500;
		ScrollView_RankingTable->setInnerContainerSize(Size(1000, height));
		auto row = CreateRow(i+1, Id, username, total_score, total_question);
		row->setPosition(Vec2(50, height - 50 * i));
		ScrollView_RankingTable->addChild(row);
	}
}

void RankingScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

Node * RankingScene::CreateRow(int stt, int id, string name, int score, int question)
{
	Node* result = Node::create();

	Label* lbl_stt = Tool::CreateLabel("stt: " + to_string(stt));
	//lbl_stt->setPositionX();
	result->addChild(lbl_stt);

	Label* lbl_Id = Tool::CreateLabel("ID: " + to_string(id));
	lbl_Id->setPositionX(150);
	result->addChild(lbl_Id);

	Label* lbl_Name = Tool::CreateLabel("Name: " + name);
	lbl_Name->setPositionX(300);
	result->addChild(lbl_Name);

	Label* lbl_total_score = Tool::CreateLabel("Score: " + to_string(score));
	lbl_total_score->setPositionX(450);
	result->addChild(lbl_total_score);

	Label* lbl_total_question = Tool::CreateLabel("Question: " + to_string(question));
	lbl_total_question->setPositionX(600);
	result->addChild(lbl_total_question);

	auto line = Sprite::create("UI/BG/line.png");
	line->setPositionX(visibleSize.width/2);
	result->addChild(line);
	
	return result;
}

void RankingScene::SetupGUI()
{
	auto sp_Background = Sprite::create("UI/BG/background1.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	ScrollView_RankingTable = ui::ScrollView::create();
	ScrollView_RankingTable->setContentSize(Size(700, 300));
	//ScrollView_RankingTable->setBackGroundColorType(LAYOUT_COLOR_SOLID);
	ScrollView_RankingTable->setInnerContainerSize(Size(1000, 2000));
	ScrollView_RankingTable->setPosition(visibleSize / 2);
	ScrollView_RankingTable->setAnchorPoint(Vec2(0.5, 0.5));
	ScrollView_RankingTable->setBounceEnabled(true);
	this->addChild(ScrollView_RankingTable);

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
	
}

void RankingScene::RunActionNotify(string content)
{
	
}