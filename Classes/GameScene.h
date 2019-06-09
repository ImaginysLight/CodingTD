#pragma once
#include "cocos2d.h"
#include"CardScene.h"
#include"Global Class/Tool.h"
#include"network/HttpClient.h"
#include"Ingame Object/IngameObject.h"
#include"Ingame Object/Unit/BaseUnitClass.h"
#include"Ingame Object/ObjectConstructor.h"
#include"Ingame Object/SkillConstructor.h"
#include"Ingame Object/Skill/BaseSkillClass.h"
#include"Global Class/Player.h"
#include"Global Class/Trophy.h"
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
		float gold = 200;
		float energy = 0;
		float energyCap = 100;
		int knowledge = 1;
		float Gps = 5;
		float Eps = 1;
		float correctAnswerGoldRate = 1.0;
		float wrongAnswerGoldRate = 1.0;
		float defeatGoldRate = 0.1;
		float defeatEnergyRate = 0;
		int numOfCorrectQuestion = 0;
		int numOfWrongQuestion = 0;
		int numOfEnemyDefeated = 0;
		Sprite* sp_Background;
		Label* lbl_PlayerName;
		Label* lbl_Gold;
		Label* lbl_Knowledge;
		Label* lbl_Energy;
		Button* btn_UpgradeKingdom;
		Label* lbl_KingdomLevel;
		int kingdomLevel = 1;
		Button *btn_Skill1, *btn_Skill2;
		BaseUnitClass* kingdom, *opponentKingdom;
	};
	IngamePlayer ingamePlayerInfo;
	void UpdateIngamePlayerInfo();
	void LoadIngamePlayerInfo();

	//Dùng skill
	void btn_ExecuteSkill_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	bool CheckSkillCondition(string name);
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
	Button *btn_CloseViewDetail, *btn_ProcessUpgrade, *btn_CancelUpgrade, *btn_Mode;
	Label* lbl_UpgradeInfo;
	void CreateUpgradeTable(string name);
	ui::ScrollView* sc_ViewDetail = nullptr;
	void UpgradeUnit(string name);
	void btn_UpgradeKingdom(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);

	//Khởi tạo object
	void InitializeIngameObject(string objectName, int line, int playerId);

	//Endgame
	void Endgame(bool isVictorious);

	//Xem thông tin unit khi click
	BaseUnitClass* choosingUnit = new BaseUnitClass();
	void ShowUnitDetails();

	//Các vấn đề về Chatbox
	vector<string> chatBoxContent;
	ui::ScrollView *sc_ChatBox;
	EditBox* EditBox_Chat;
	Button* btn_SendMessage;
	void CreateChatbox();
	void UpdateChatbox();
	void btn_SendMessage_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);

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
	bool isAllowedToChooseQuestion = true;
	void CreateQuestionTable();

	//Các vấn đề server
	void onReceiveEvent_Question(SIOClient* client, const std::string& data);  // click chọn độ khó xong vẫn phải chờ hết giờ mới chuyển qua câu hỏi, ko phải chuyển ngay @@
	void onReceiveEvent_InitializeIngameObject(SIOClient* client, const std::string& data);
	void onReceiveEvent_ExcuteSkill(SIOClient* client, const std::string& data);
	void onReceiveEvent_SendMessage(SIOClient* client, const std::string& data);
	void onReceiveEvent_UpgradeKingdom(SIOClient* client, const std::string& data);

	//Setup trong init
	void SetupCamera();
	void SetupGUI();

	//Các hàm update
	void update(float time);
	void UpdateIngameObject(float time);
	void UpdateQuestionInfo(float time);
	void UpdatePlayerResourcePerSecond(float time);


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

