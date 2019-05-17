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

	return true;
}

void RankingScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

Node * RankingScene::CreateRow(int id, string name, int stat1, int stat2)
{
	Node* result = Node::create();
	Label* lbl_Id = Tool::CreateLabel("ID: " + to_string(id));
	result->addChild(lbl_Id);

	Label* lbl_Name = Tool::CreateLabel("Name: " + name);
	lbl_Name->setPositionX(100);
	result->addChild(lbl_Name);

	Label* lbl_stat1 = Tool::CreateLabel("Stat1: " + to_string(stat1));
	lbl_stat1->setPositionX(200);
	result->addChild(lbl_stat1);

	Label* lbl_stat2 = Tool::CreateLabel("Stat2: " + to_string(stat2));
	lbl_stat2->setPositionX(300);
	result->addChild(lbl_stat2);
	
	return result;
}

void RankingScene::SetupGUI()
{
	ScrollView_RankingTable = ui::ScrollView::create();
	ScrollView_RankingTable->setContentSize(Size(700, 300));
	ScrollView_RankingTable->setInnerContainerSize(Size(1000, 2000));
	ScrollView_RankingTable->setPosition(visibleSize / 2);
	ScrollView_RankingTable->setAnchorPoint(Vec2(0.5, 0.5));
	ScrollView_RankingTable->setBounceEnabled(true);
	this->addChild(ScrollView_RankingTable);

	//Giả sử có 50 dòng và mỗi dòng chiếm khoảng 50 pixel => tổng cộng 2500 pixel + dư ra tí cho đẹp
	auto height = 50 * 50 + 500;
	ScrollView_RankingTable->setInnerContainerSize(Size(1000, height));
	for (int i = 1; i < 51; i++) {
		//Vì gốc của cái ScrollView nằm ở góc trái dưới, nên cái trên đầu sẽ có height cao nhất.
		auto row = CreateRow(i, to_string(i), 1, 2);
		row->setPosition(Vec2(50, height - 50 * i));
		ScrollView_RankingTable->addChild(row);
	}
}

void RankingScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	string name = ((Button*)pSender)->getName();
	
}

void RankingScene::RunActionNotify(string content)
{
	
}