#pragma once
#include "cocos2d.h"
#include"Object/Tool.h"
#include"network/HttpClient.h"
#include"Object/IngameObject.h"
#include"Object/IngameObject/ObjectConstructor.h"
USING_NS_CC;
class GameScene : public cocos2d::Scene
{
public:
	
	Size visibleSize;
	Node* staticUI, *questionTable, *buyingBar, *objectDetails;
	Label* lbl_Notify;
	void RunActionNotify(string content);

	//Thông số trong game của người chơi
	struct IngamePlayer {
		int gold = 500;
		int energy = 3;
		int numOfCorrectQuestion = 0;
		int numOfWrongQuestion = 0;
		int mainTowerLevel = 1;
		Label* lbl_Gold;
		Label* lbl_Energy;
		Label* lbl_MainTowerLevel;
		Button* btn_UpgradeMainTower;
		IngamePlayer();
	};
	IngamePlayer ingamePlayerInfo;
	

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

	int choosingLine = 1;
	Button *btn_ChooseLine1, *btn_ChooseLine2, *btn_ChooseLine3;
	int objectId = 1;
	void InitializeIngameObject(string objectName, int line, bool isLeft);

	//Thanh mua linh
	Button* btn_SwitchBuyingBar;
	struct Item_BuyableObject {
		Node* item;
		Label* lbl_Cost;
		Button* btn_Icon;
		Button* btn_Upgrade;
		Item_BuyableObject(string name);
	};
	vector<Item_BuyableObject> List_BuyableObject;
	void GetBuyableObject();
	int currentPositionOfBuyingBar = 0, numOfVisibleItem = 4;
	float distanceBetweenItems = 0.1;
	void CreateBuyingBar();
	void btn_BuyObjectClick(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void btn_UpgradeObjectClick(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	void RunActionButtonBuyingBack();
	void RunActionButtonBuyingNext();

	//Bảng thông tin chi tiết của object click vào
	struct ObjectDetails {
		Node* details;
		Label* lbl_Name;
		Label* lbl_Health;
		Label* lbl_Attack;
		Label* lbl_Defense;
		Label* lbl_AttackRate;
		Label* lbl_Speed;
		ObjectDetails(BaseObjectClass object, Vec2 position);
	};
	void ShowObjectDetails(BaseObjectClass object, Vec2 position);
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

	//Các hàm cơ bản
	void btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);

	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(GameScene);
};

