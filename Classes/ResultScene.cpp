#include"ResultScene.h"

USING_NS_CC;
int ResultScene::numOfCorrectAnswer = 0;
int ResultScene::numOfWrongAnswer = 0;
int ResultScene::numOfEnemyDefeated = 0;
float ResultScene::goldReceived = 0;
bool ResultScene::isVictorious = false;

Scene* ResultScene::createScene()
{
	return ResultScene::create();
}

bool ResultScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	SetupGUI();
	return true;
}

void ResultScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void ResultScene::SetupGUI()
{
	if (Player::CalculateLevel(Player::oldPlayerInfo.experience).first < Player::CalculateLevel(Player::currentPlayer->experience).first) {
		auto nodeLevelUp = Tool::CreateNotificationTable("LEVEL UP!!!\nYou receive 1 Friendship Point", "");
		this->addChild(nodeLevelUp);
		nodeLevelUp->setPosition(visibleSize / 2);
	}

	auto lbl_Title = Tool::CreateLabel("", Tool::defaultTextSize * 2);
	lbl_Title->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.9));
	this->addChild(lbl_Title);
	if (ResultScene::isVictorious) {
		lbl_Title->setString("You are Victorious");
		lbl_Title->setTextColor(Color4B::GREEN);
	}
	else {
		lbl_Title->setString("You are Defeated");
		lbl_Title->setTextColor(Color4B::RED);
	}

	Label* lbl_CurrentExperience = Tool::CreateLabel("Experience: " + to_string(Player::oldPlayerInfo.experience));
	lbl_CurrentExperience->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.7));
	lbl_CurrentExperience->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_CurrentExperience);
	Label* lbl_BonusExperience = Tool::CreateLabel("+" + to_string((int)Player::currentPlayer->experience - Player::oldPlayerInfo.experience), Tool::defaultTextSize, Color4B(175, 225, 200, 255));
	lbl_BonusExperience->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.7));
	this->addChild(lbl_BonusExperience);

	Label* lbl_CurrentKill = Tool::CreateLabel("Total Kill: " + to_string(Player::oldPlayerInfo.total_kill));
	lbl_CurrentKill->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.6));
	lbl_CurrentKill->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_CurrentKill);
	Label* lbl_BonusKill = Tool::CreateLabel("+" + to_string(ResultScene::numOfEnemyDefeated), Tool::defaultTextSize, Color4B(175, 225, 200, 255));
	lbl_BonusKill->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.6));
	this->addChild(lbl_BonusKill);

	Label* lbl_CurrentCorrectAnswer = Tool::CreateLabel("Correct Answer: " + to_string(Player::oldPlayerInfo.total_correctAnswer));
	lbl_CurrentCorrectAnswer->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.7));
	lbl_CurrentCorrectAnswer->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_CurrentCorrectAnswer);
	Label* lbl_BonusCorrectAnswer = Tool::CreateLabel("+" + to_string(ResultScene::numOfCorrectAnswer), Tool::defaultTextSize, Color4B(175, 225, 200, 255));
	lbl_BonusCorrectAnswer->setPosition(Vec2(visibleSize.width*0.75, visibleSize.height*0.7));
	this->addChild(lbl_BonusCorrectAnswer);

	Label* lbl_CurrentWrongAnswer = Tool::CreateLabel("Wrong Answer: " + to_string(Player::oldPlayerInfo.total_wrongAnswer));
	lbl_CurrentWrongAnswer->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.6));
	lbl_CurrentWrongAnswer->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_CurrentWrongAnswer);
	Label* lbl_BonusWrongAnswer = Tool::CreateLabel("+" + to_string(ResultScene::numOfWrongAnswer), Tool::defaultTextSize, Color4B::RED);
	lbl_BonusWrongAnswer->setPosition(Vec2(visibleSize.width*0.75, visibleSize.height*0.6));
	this->addChild(lbl_BonusWrongAnswer);

	float oldAccurary = Player::oldPlayerInfo.total_correctAnswer / (float)(Player::oldPlayerInfo.total_correctAnswer + Player::oldPlayerInfo.total_wrongAnswer) * 100;
	if (oldAccurary != oldAccurary) oldAccurary = 0;
	float newAccurary = Player::currentPlayer->total_correctAnswer / (float)(Player::currentPlayer->total_correctAnswer + Player::currentPlayer->total_wrongAnswer) * 100;
	Label* lbl_OldAccuraryRate = Tool::CreateLabel((string)CCString::createWithFormat("Accurary Rate: %.1f", oldAccurary)->getCString() + "%");
	lbl_OldAccuraryRate->setPosition(Vec2(visibleSize.width*0.55, visibleSize.height*0.5));
	lbl_OldAccuraryRate->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_OldAccuraryRate);

	Label* lbl_NewAccuraryRate = Tool::CreateLabel((string)CCString::createWithFormat(">> %.1f", newAccurary)->getCString() + "%");
	lbl_NewAccuraryRate->setPosition(Vec2(visibleSize.width*0.82, visibleSize.height*0.5));
	lbl_NewAccuraryRate->setTextColor(newAccurary > oldAccurary ? Color4B::GREEN : Color4B::RED);
	this->addChild(lbl_NewAccuraryRate);

	auto btn_LobbyScene = Tool::CreateButtonWithoutSprite("btn_LobbyScene", "Back To Lobby");
	btn_LobbyScene->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.2));
	btn_LobbyScene->addTouchEventListener(CC_CALLBACK_2(ResultScene::btn_Click, this));
	this->addChild(btn_LobbyScene);

}

void ResultScene::btn_Click(Ref *pSender, cocos2d::ui::Button::Widget::TouchEventType type) {
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Button*)pSender)->getName();
		if (name == "btn_LobbyScene") {
			ResultScene::numOfCorrectAnswer = 0;
			ResultScene::numOfWrongAnswer = 0;
			ResultScene::numOfEnemyDefeated = 0;
			ResultScene::goldReceived = 0;
			ResultScene::isVictorious = false;
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
	}
	
}