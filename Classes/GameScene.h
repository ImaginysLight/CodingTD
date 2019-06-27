#pragma once
#include "cocos2d.h"
#include"CardScene.h"
#include"GlobalClass/Tool.h"
#include"GlobalClass/Player.h"
#include"GlobalClass/Trophy.h"
#include"GlobalClass/Audio.h"
#include"network/HttpClient.h"
#include"IngameObject/IngameObject.h"
#include"IngameObject/Unit/BaseUnitClass.h"
#include"IngameObject/ObjectConstructor.h"
#include"IngameObject/SkillConstructor.h"
#include"IngameObject/Skill/BaseSkillClass.h"

#include"ResultScene.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
	Size visibleSize;
	Node* staticUI, *questionTable, *buyingBar, *unitDetails, *tooltip;
	void RunActionNotify(string content);

	//Nâng cấp quân đội
	struct ArmyBonus {
		int health = 0;
		int attack = 0;
		int defense = 0;
		int attackSpeed = 0;
	};
	ArmyBonus army_CurrentPlayer, army_OpponentPlayer;
	void ExcuteArmyEffect(BaseUnitClass* &object);
	void CreateTableUpgradeArmy(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_UpgradeArmy_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	//Thông số trong game của người chơi
	struct IngamePlayer {
		float gold = 200;
		float energy = 0;
		float energyCap = 100;
		int knowledge = 1;
		float foodLimit = 5;
		float food = -1;
		float Gps = 5;
		float Eps = 1;
		float correctAnswerGoldRate = 1.0;
		float wrongAnswerGoldRate = 1.0;
		float defeatGoldRate = 0.1;
		float defeatEnergyRate = 0;
		Sprite* sp_Background;
		Label* lbl_PlayerName;
		Label* lbl_Gold; Sprite* sp_Gold;
		Label* lbl_Knowledge; Sprite* sp_Knowledge;
		Label* lbl_Energy; Sprite* sp_Energy;
		Label* lbl_KingdomLevel; Sprite* sp_KingdomLevel;
		Label* lbl_Food; Sprite* sp_Food;
		int kingdomLevel = 1;
		Button *btn_Skill1, *btn_Skill2, *btn_Skill3, *btn_Army;
		BaseUnitClass* kingdom, *opponentKingdom;
		Node* root;
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
		Vec2 oldRootPos;
		Item_BuyableUnit(string name);
	};
	Item_BuyableUnit* choosingBuyableUnit = nullptr;
	Node* ghostItem = Node::create();
	void AddDragAndDropItem(Node*& root);
	void onCardMoved(Touch* touch, Event* event);
	vector<Item_BuyableUnit> List_BuyableUnit;
	void CreateBuyingBar();
	void btn_BuyUnit_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void BuyUnit(string name, int line);

	
	//Nâng cấp
	void ChangeUpgradeState();
	string BuyingBarMode = "Buy";
	void btn_Upgrade_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	Button* btn_UpgradeKingdom, *btn_TurnOnUpgrade, * btn_UpgradeFarm;
	void CreateUpgradeTable(string name);
	void UpgradeUnit(string name);

	//Khởi tạo object
	void InitializeIngameObject(string objectName, int line, int playerId);

	//Endgame
	void Endgame(bool isVictorious);
	void ClearAllVariables();
	Button* btn_Surrender;

	//Xem thông tin unit khi click
	BaseUnitClass* choosingUnit = new BaseUnitClass();
	void ShowUnitDetails();

	//Các vấn đề về Chatbox
	vector<pair<string, int>> chatBoxContent;
	ui::ScrollView *sc_ChatBox;
	EditBox* EditBox_Chat;
	Button* btn_SendMessage, *btn_General, *btn_Notify, *btn_Chat, *btn_Hide;
	void CreateChatbox();
	string chatboxMode = "General";
	void UpdateChatbox();
	void btn_ChatBox_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);

	//Các vấn đề về bảng câu hỏi
	Button *btn_DropDownQuestionTable, *btn_Answer1, *btn_Answer2, *btn_Answer3, *btn_Answer4,
		*btn_Level1, *btn_Level2, *btn_Level3, *btn_ActiveChallenge;
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
	void onReceiveEvent_AnswerResult(SIOClient* client, const std::string& data);
	void onReceiveEvent_ActiveChallenge(SIOClient* client, const std::string& data);
	void onReceiveEvent_UpgradeArmy(SIOClient* client, const std::string& data);
	void onReceiveEvent_EndGame(SIOClient* client, const std::string& data);

	//Setup trong init
	void SetupCamera();
	void SetupGUI();

	//Các hàm update
	void update(float time);
	void UpdateIngameObject(float time);
	void UpdateQuestionInfo(float time);
	void UpdatePlayerResourcePerSecond(float time);
	void UpdateAudio(float time);
	Label* lbl_GameTime;

	//Các hàm cơ bản
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	void onTouchEnded(Touch* touch, Event* event);
	void onMouseMove(Event *event);
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene);
};

