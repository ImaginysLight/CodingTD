#pragma once

#include"IngameObject/ObjectConstructor.h"
#include"GlobalClass/Player.h"
#include"GlobalClass/Tool.h"
#include"GlobalClass/Audio.h"
#include"cocos2d.h"
#include"PlayerInformationScene.h"
using namespace cocos2d::ui;
USING_NS_CC;

struct UnitDetailsTable {
	Node* root;
	Label* lbl_Name;
	Label* lbl_Health;
	Label* lbl_Attack;
	Label* lbl_Defense;
	Label* lbl_AttackSpeed;
	Label* lbl_MoveSpeed;
	Label* lbl_Range;
	Label* lbl_Regeneration;
	Sprite* sp_Health;
	Sprite* sp_Attack;
	Sprite* sp_Defense;
	Sprite* sp_AttackSpeed;
	Sprite* sp_MoveSpeed;
	Sprite* sp_Range;
	Sprite* sp_Regeneration;
	Sprite* sp_Background;
	UnitDetailsTable(BaseUnitClass object, Vec2 position);
};

//root = Vec2(0,1)
struct FriendShipUpgrade {
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
	Node* friendshipNode, *detailNode_Before, *detailNode_After, *spriteNode, *skillNode, *dynamicUI, *playerInfoNode;
	ui::ScrollView* scroll_Navigator, *scroll_UI;
	unordered_map<string, Button*> vec_Card;
	Label* lbl_Friendship;
	void btn_UpFriendship_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_DownFriendship_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_Navigator_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionNotify(string content);
	vector<string> GetSkillDetail(string unitName);
	void RefreshScene(string unitName);
	void RefreshSceneKingdom(string unitName);
};