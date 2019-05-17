#pragma once
#include "cocos2d.h"
#include"Global Class/Tool.h"
#include"network/HttpClient.h"
#include"Ingame Object/IngameObject.h"
#include"Ingame Object/Unit/BaseUnitClass.h"
#include"Ingame Object/ObjectConstructor.h"
#include"Ingame Object/Skill/BaseSkillClass.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
	
	Size visibleSize;
	Node* staticUI, *questionTable, *buyingBar, *unitDetails, *upgradeTable;
	Label* lbl_Notify;
	void RunActionNotify(string content);

	//Thông số trong game của người chơi
	struct IngamePlayer {
		float gold = 500;
		float mana = 0;
		float manaCap = 50;
		int energy = 3;
		int numOfCorrectQuestion = 0;
		int numOfWrongQuestion = 0;
		int kingdomLevel = 1;
		Label* lbl_Gold;
		Label* lbl_Energy;
		Label* lbl_Mana;
		Label* lbl_KingdomLevel;
		Button* btn_UpgradeMainTower;
		IngamePlayer();
	};
	IngamePlayer ingamePlayerInfo;
	void UpdateIngamePlayerInfo();
	

	//Các vấn đề về bảng câu hỏi
	Button *btn_DropDownQuestionTable, *btn_Answer1, *btn_Answer2, *btn_Answer3, *btn_Answer4,
		*btn_Level1, *btn_Level2, *btn_Level3;
	ListView* lv_QuestionContent;
	Text* txt_Question;
	string questionContent = "";
	Label* lbl_Level;
	string answer;
	string nextQuestionLevel = "";
	int currentQuestionLevel;
	float destinationTime = 0;
	bool questionAvailable = true;
	void CorrectAnswer();
	void WrongAnswer();
	void btn_AnswerClick(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void ChangeQuestionTableState(bool questionAvailable);
	bool isAllowedToChooseQuestion = false;
	void CreateQuestionTable();
	
	//Khởi tạo object
	void InitializeIngameObject(string objectName, int line, int playerId);

	//Xem thông tin unit khi click
	BaseUnitClass* choosingUnit = new BaseUnitClass();
	struct UnitDetails {
		Node* details;
		Label* lbl_Name;
		Label* lbl_Health;
		Label* lbl_Attack;
		Label* lbl_Defense;
		Label* lbl_AttackRate;
		Label* lbl_Speed;
		UnitDetails(BaseUnitClass object, Vec2 position);
	};
	void ShowUnitDetails();

	//Mua lính
	struct Item_BuyableUnit {
		Node* root;
		Label* lbl_Cost;
		Button* btn_Icon;
		BaseUnitClass* unitInfo;
		Item_BuyableUnit(string name);
	};
	vector<string> ChoosedUnit;
	Item_BuyableUnit* choosingBuyableUnit = nullptr;
	Node* ghostItem = Node::create();
	void AddDragAndDropItem(Node*& root);
	void onCardMoved(Touch* touch, Event* event);
	Vec2 oldRootPos;
	vector<Item_BuyableUnit> List_BuyableUnit;
	void CreateBuyingBar();
	void btn_BuyUnit_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void BuyUnit(string name, int line);

	//Nâng cấp lính
	void btn_Upgrade_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	Button* btn_ViewDetail, *btn_CloseViewDetail, *btn_ProcessUpgrade, *btn_CancelUpgrade, *btn_Upgrade;
	Label* lbl_UpgradeInfo;
	void CreateUpgradeTable(string name);
	ui::ScrollView* sc_ViewDetail = nullptr;
	bool isViewDetail = false;
	bool isUpgrade = false;
	void UpgradeUnit(string name);

	//Các vấn đề server
	void Request_RandomQuestion(string level);
	void Respone_ReadQuestion(cocos2d::network::HttpClient * sender, cocos2d::network::HttpResponse * response);
	void Request_ReadQuestion();

	//Setup trong init
	void SetupCamera();
	void SetupGUI();

	//Các hàm update
	void update(float time);
	void UpdateIngameObject(float time);
	void UpdateQuestionInfo(float time);
	void UpdatePlayerResource(float time);


	//Các hàm cơ bản
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene);
};

