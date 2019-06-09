#pragma once

#include"Ingame Object/ObjectConstructor.h"
#include"Global Class/Player.h"
#include"Global Class/Tool.h"
#include"cocos2d.h"
#include"PlayerInformationScene.h"
using namespace cocos2d::ui;
USING_NS_CC;

extern struct UnitDetailsTable {
	Node* root;
	Label* lbl_Name;
	Label* lbl_Health;
	Label* lbl_Attack;
	Label* lbl_Defense;
	Label* lbl_AttackSpeed;
	Label* lbl_MoveSpeed;
	Label* lbl_Range;
	Label* lbl_Regeneration;
	Sprite* sp_Background;
	UnitDetailsTable(BaseUnitClass object, Vec2 position);
};

//root = Vec2(0,1)
extern struct FriendShipUpgrade {
	Node* root;
	Button* btn_Up, *btn_Down;
	Label* lbl_Level1, *lbl_Level2, *lbl_Level3, *lbl_Level4, *lbl_Level5;
	int currentLevel;
	FriendShipUpgrade(string unitName, int currentLevel);
};

class CardScene : public cocos2d::Scene //, public SocketIO::SIODelegate
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(CardScene);

	Size visibleSize;
	static Node* GetUnitInfo(BaseUnitClass* unit);
	Node* friendshipNode, *detailNode_Before, *detailNode_After, *spriteNode, *skillNode, *processUpgradeNode;
	Button* btn_Process, *btn_Cancel;
	Label* lbl_Notify, *lbl_ConfirmUpgrade,*lbl_Friendship;
	ui::ScrollView* scroll_Navigator;
	unordered_map<string, Button*> vec_Card;
	void btn_UpFriendship_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_DownFriendship_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_Navigator_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);
	vector<string> GetSkillDetail(string unitName);
	void RefreshScene(string unitName);
};