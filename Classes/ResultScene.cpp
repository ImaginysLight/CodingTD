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
	auto sp_Background = Sprite::create("UI/Login/BG.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	if (Player::CalculateLevel(Player::oldPlayerInfo.experience).first < Player::CalculateLevel(Player::currentPlayer->experience).first) {
		auto nodeLevelUp = Tool::CreateNotificationTable("LEVEL UP!!!\nYou receive 1 Friendship Point", "OK");
		this->addChild(nodeLevelUp,100);
		nodeLevelUp->setPosition(visibleSize / 2);
	}

	auto sp_Frame = Sprite::create("Trophy/Trophy Border.png");
	sp_Frame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.4));
	Tool::setNodeSize(sp_Frame, visibleSize.width*0.8, visibleSize.height*0.6);
	this->addChild(sp_Frame, -1);

	if (ResultScene::isVictorious) {
		auto sp_Win = Sprite::create("UI/Lobby/win.png");
		sp_Win->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.8));
		this->addChild(sp_Win);
	}
	else {
		auto sp_Win = Sprite::create("UI/Lobby/lose.png");
		sp_Win->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.8));
		this->addChild(sp_Win);
	}

	Label* lbl_Experience = Label::create("Experience", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_Experience->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.65));
	lbl_Experience->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_Experience);

	auto levelInfo = Player::CalculateLevel(Player::currentPlayer->experience);
	auto expBar = Tool::CreateBar(to_string(Player::currentPlayer->experience) + " / " + to_string(levelInfo.second), Color4B::WHITE, Size(200, 4), Color3B::WHITE);
	((ProgressTimer*)expBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->experience / (float)levelInfo.second *100.0));
	((Label*)expBar->getChildByName("Content"))->setPositionY(14);
	expBar->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.625));
	this->addChild(expBar);

	Label* lbl_BonusExperience = Label::create("( +" + to_string((int)Player::currentPlayer->experience - Player::oldPlayerInfo.experience) + " )", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_BonusExperience->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.65));
	lbl_BonusExperience->setAnchorPoint(Vec2(0, 0.5));
	this->addChild(lbl_BonusExperience);




	Label* lbl_CorrectAnswer = Label::create("Correct", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_CorrectAnswer->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.55));
	lbl_CorrectAnswer->setAnchorPoint(Vec2(0, 0.5));
	lbl_CorrectAnswer->setTextColor(Color4B(175, 225, 200, 255));
	this->addChild(lbl_CorrectAnswer);

	auto knowledge = Trophy::CalculateKnowledgeTrophy(Player::currentPlayer->total_correctAnswer);
	auto correctBar = Tool::CreateBar(to_string(Player::currentPlayer->total_correctAnswer) + " / " + to_string(knowledge.ExpToNext), Color4B(175, 225, 200, 255), Size(200, 4), Color3B(175, 225, 200));
	((ProgressTimer*)correctBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->total_correctAnswer / (float)knowledge.ExpToNext *100.0));
	((Label*)correctBar->getChildByName("Content"))->setPositionY(14);
	correctBar->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.525));
	this->addChild(correctBar);

	Label* lbl_BonusCorrect = Label::create("( +" + to_string((int)Player::currentPlayer->total_correctAnswer - Player::oldPlayerInfo.total_correctAnswer) + " )", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_BonusCorrect->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.55));
	lbl_BonusCorrect->setAnchorPoint(Vec2(0, 0.5));
	lbl_BonusCorrect->setTextColor(Color4B(175, 225, 200, 255));
	this->addChild(lbl_BonusCorrect);



	Label* lbl_Kill = Label::create("Kill", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_Kill->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.45));
	lbl_Kill->setAnchorPoint(Vec2(0, 0.5));
	lbl_Kill->setTextColor(Color4B::RED);
	this->addChild(lbl_Kill);

	auto battle = Trophy::CalculateBattleTrophy(Player::currentPlayer->total_kill);
	auto killBar = Tool::CreateBar(to_string(Player::currentPlayer->total_kill) + " / " + to_string(battle.ExpToNext), Color4B::RED, Size(200, 4), Color3B::RED);
	((ProgressTimer*)killBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->total_kill / (float)battle.ExpToNext *100.0));
	((Label*)killBar->getChildByName("Content"))->setPositionY(14);
	killBar->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.425));
	this->addChild(killBar);

	Label* lbl_BonusKill = Label::create("( +" + to_string((int)Player::currentPlayer->total_kill - Player::oldPlayerInfo.total_kill) + " )", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_BonusKill->setPosition(Vec2(visibleSize.width*0.65, visibleSize.height*0.45));
	lbl_BonusKill->setAnchorPoint(Vec2(0, 0.5));
	lbl_BonusKill->setTextColor(Color4B::RED);
	this->addChild(lbl_BonusKill);

	Label* lbl_Accurary = Label::create("Accurary", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_Accurary->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.3));
	lbl_Accurary->setTextColor(Color4B(175, 225, 250, 255));
	this->addChild(lbl_Accurary);
	
	float accurary = (float)Player::currentPlayer->total_correctAnswer / (Player::currentPlayer->total_correctAnswer + Player::currentPlayer->total_wrongAnswer)*100.0;
	if (accurary != accurary) accurary = 0;
	auto accuraryBar = Tool::CreateBar((string)CCString::createWithFormat("%.1f", accurary)->getCString() + " %", Color4B(175, 225, 250, 255), Size(150, 4), Color3B(175, 225, 250));
	((ProgressTimer*)accuraryBar->getChildByName("Front Bar"))->setPercentage(accurary);
	((Label*)accuraryBar->getChildByName("Content"))->setPositionY(14);
	accuraryBar->setPosition(Vec2(visibleSize.width*0.3, visibleSize.height*0.325));
	this->addChild(accuraryBar);

	Label* lbl_Winrate = Label::create("Win Rate", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_Winrate->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.3));
	lbl_Winrate->setTextColor(Color4B(175, 225, 250, 255));
	this->addChild(lbl_Winrate);

	float winrate = (float)Player::currentPlayer->total_win / (Player::currentPlayer->total_win + Player::currentPlayer->total_lose)*100.0;
	if (winrate != winrate) winrate = 0;
	auto winrateBar = Tool::CreateBar((string)CCString::createWithFormat("%.1f", winrate)->getCString() + " %", Color4B(175, 225, 250, 255), Size(150, 4), Color3B(175, 225, 250));
	((ProgressTimer*)winrateBar->getChildByName("Front Bar"))->setPercentage(winrate);
	((Label*)winrateBar->getChildByName("Content"))->setPositionY(14);
	winrateBar->setPosition(Vec2(visibleSize.width*0.7, visibleSize.height*0.325));
	this->addChild(winrateBar);


	auto btn_LobbyScene = Tool::CreateButtonWithSpirte("btn_LobbyScene", "UI/Lobby/btn_exit.png");
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