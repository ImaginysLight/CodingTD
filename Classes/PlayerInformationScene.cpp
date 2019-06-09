#include "PlayerInformationScene.h"

USING_NS_CC;
cocos2d::Scene * PlayerInformationScene::createScene()
{
	return PlayerInformationScene::create();
}

bool PlayerInformationScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	auto sp_Background = Sprite::create("UI/GameScene/static background.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto lbl_PlayerName = Tool::CreateLabel(Player::currentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_PlayerName->setPosition(Vec2(visibleSize.width*0.15, visibleSize.height*0.9));
	this->addChild(lbl_PlayerName);

	auto levelInfo = Player::CalculateLevel(Player::currentPlayer->experience);

	auto lbl_Level = Tool::CreateLabel("Level: " + to_string(levelInfo.first));
	lbl_Level->setPosition(Vec2(visibleSize.width*0.385, visibleSize.height*0.93));
	this->addChild(lbl_Level);

	auto expBar = Tool::CreateBar(200, 25, Color3B(175, 225, 200));
	expBar.first->setPosition(Vec2(visibleSize.width*0.28, visibleSize.height*0.85));
	expBar.first->setPercentage(Player::currentPlayer->experience / (float)levelInfo.second *100.0);
	expBar.second->setPosition(Vec2(visibleSize.width*0.28, visibleSize.height*0.85));
	this->addChild(expBar.first);
	this->addChild(expBar.second, -1);

	auto lbl_Exp = Tool::CreateLabel(to_string(Player::currentPlayer->experience) + " / " + to_string(levelInfo.second), Tool::defaultTextSize, Color4B::RED);
	lbl_Exp->setPosition(Vec2(visibleSize.width*0.385, visibleSize.height*0.87));
	this->addChild(lbl_Exp);

	auto lbl_Friendship = Tool::CreateLabel("Friendship: " + to_string(Player::currentPlayer->friendshipPoint));
	lbl_Friendship->setPosition(Vec2(visibleSize.width*0.6, visibleSize.height*0.9));
	this->addChild(lbl_Friendship);
	
	auto btn_CardScene = Tool::CreateButtonWithoutSprite("btn_CardScene", "Card Info >>", Tool::defaultTextSize*1.5);
	btn_CardScene->runAction(RepeatForever::create(Sequence::create(
		MoveBy::create(1, Vec2(25, 0)),
		MoveBy::create(1, Vec2(-25, 0)), 
		nullptr)));
	btn_CardScene->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.9));
	btn_CardScene->addTouchEventListener(CC_CALLBACK_2(PlayerInformationScene::btn_Click, this));
	this->addChild(btn_CardScene);

	auto lbl_TotalKill = Tool::CreateLabel("Kill: " + to_string(Player::currentPlayer->total_kill));
	lbl_TotalKill->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.75));
	this->addChild(lbl_TotalKill);

	string killPerMatch = CCString::createWithFormat("Kill per Match: %.2f", Player::currentPlayer->total_kill / (float)(Player::currentPlayer->total_win + Player::currentPlayer->total_lose))->getCString();
	auto lbl_KillPerMatch = Tool::CreateLabel(killPerMatch);
	lbl_KillPerMatch->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.7));
	this->addChild(lbl_KillPerMatch);

	auto lbl_TotalWin = Tool::CreateLabel("Win: " + to_string(Player::currentPlayer->total_win));
	lbl_TotalWin->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.75));
	this->addChild(lbl_TotalWin);

	auto lbl_TotalLose = Tool::CreateLabel("Lose: " + to_string(Player::currentPlayer->total_lose));
	lbl_TotalLose->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.7));
	this->addChild(lbl_TotalLose);

	string winRate = CCString::createWithFormat("Winrate: %.2f", Player::currentPlayer->total_win / (float)(Player::currentPlayer->total_lose + Player::currentPlayer->total_win) * 100.0)->getCString();
	winRate += CCString::create("%")->getCString();
	auto lbl_Winrate = Tool::CreateLabel(winRate);
	lbl_Winrate->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.65));
	this->addChild(lbl_Winrate);

	auto lbl_CorrectAnswer = Tool::CreateLabel("Correct Answer: " + to_string(Player::currentPlayer->total_correctAnswer));
	lbl_CorrectAnswer->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.75));
	this->addChild(lbl_CorrectAnswer);

	auto lbl_WrongAnswer = Tool::CreateLabel("Wrong Answer: " + to_string(Player::currentPlayer->total_wrongAnswer));
	lbl_WrongAnswer->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.7));
	this->addChild(lbl_WrongAnswer);
	
	string accurary = CCString::createWithFormat("Answer Accurary: %.2f", Player::currentPlayer->total_correctAnswer / (float)(Player::currentPlayer->total_correctAnswer + Player::currentPlayer->total_wrongAnswer) * 100.0)->getCString();
	accurary += CCString::create("%")->getCString();
	auto lbl_AnswerAccurary = Tool::CreateLabel(accurary);
	lbl_AnswerAccurary->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.65));
	this->addChild(lbl_AnswerAccurary);



	auto knowledge = Trophy::CalculateKnowledgeTrophy(Player::currentPlayer->total_correctAnswer);
	auto lbl_Knowledge = Tool::CreateLabel("Knowledge Trophy\n\n\n\n\n\n\n" + knowledge.name, Tool::defaultTextSize*1.2, Color4B(175, 225, 200, 255), cocos2d::CCTextAlignment::CENTER);
	lbl_Knowledge->setAnchorPoint(Vec2(0.5, 1));
	lbl_Knowledge->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.6));
	this->addChild(lbl_Knowledge);

	auto battle = Trophy::CalculateBattleTrophy(Player::currentPlayer->total_kill);
	auto lbl_Battle = Tool::CreateLabel("Battle Trophy\n\n\n\n\n\n\n" + battle.name, Tool::defaultTextSize*1.2, Color4B(175, 225, 250, 255), cocos2d::CCTextAlignment::CENTER);
	lbl_Battle->setAnchorPoint(Vec2(0.5, 1));
	lbl_Battle->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.6));
	this->addChild(lbl_Battle);

	auto conquest = Trophy::CalculateConquestTrophy(Player::currentPlayer->total_win);
	auto lbl_Conquest = Tool::CreateLabel("Conquest Trophy\n\n\n\n\n\n\n" + conquest.name, Tool::defaultTextSize*1.22, Color4B::WHITE, cocos2d::CCTextAlignment::CENTER);
	lbl_Conquest->setAnchorPoint(Vec2(0.5, 1));
	lbl_Conquest->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.6));
	this->addChild(lbl_Conquest);

	if (knowledge.level != 0) {
		auto sp_Knowledge = Sprite::create("Trophy/Knowledge Trophy " + to_string(knowledge.level) + ".png");
		sp_Knowledge->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.4));
		this->addChild(sp_Knowledge, 1);

		auto lbl_BonusKnowledge = Tool::CreateLabel(
			"+" + to_string(knowledge.correctGoldRate) + "% Gold for Correct Answer\n\n" +
			"+" + to_string(knowledge.wrongGoldRate) + "% Gold for Wrong Answer",
			Tool::defaultTextSize*0.69, Color4B(175, 225, 200, 255), cocos2d::CCTextAlignment::CENTER);
		lbl_BonusKnowledge->setPosition(Vec2(visibleSize.width*0.2, visibleSize.height*0.12));
		lbl_BonusKnowledge->enableBold();
		lbl_BonusKnowledge->enableItalics();
		this->addChild(lbl_BonusKnowledge);
	}
	if (battle.level != 0) {
		auto sp_Battle = Sprite::create("Trophy/Battle Trophy " + to_string(battle.level) + ".png");
		sp_Battle->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.4));
		this->addChild(sp_Battle, 1);

		auto lbl_Battle = Tool::CreateLabel(Tool::ConvertUTF16ToString(
			L"+" + to_wstring(battle.defeatGoldRate) + L"% Gold when Defeat Enemy\n\n" +
			L"+" + to_wstring(battle.defeatEnergyRate) + L"‰ Energy per Value when Defeat Enemy"),
			Tool::defaultTextSize*0.69, Color4B(175, 225, 250, 255), cocos2d::CCTextAlignment::CENTER);
		lbl_Battle->setPosition(Vec2(visibleSize.width*0.8, visibleSize.height*0.12));
		lbl_Battle->enableBold();
		lbl_Battle->enableItalics();
		this->addChild(lbl_Battle);
	}
	if (conquest.level != 0) {
		auto sp_Conquest = Sprite::create("Trophy/Conquest Trophy " + to_string(conquest.level) + ".png");
		sp_Conquest->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.4));
		this->addChild(sp_Conquest, 1);

		auto temp = CCString::createWithFormat("%.1f", conquest.bonusEnergy);
		auto lbl_Conquest = Tool::CreateLabel(
			"+" + to_string(conquest.bonusGold) + " Gold per second\n\n" +
			"+" + temp->getCString() + " Energy per second",
			Tool::defaultTextSize*0.69, Color4B::WHITE, cocos2d::CCTextAlignment::CENTER);
		lbl_Conquest->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.12));
		lbl_Conquest->enableBold();
		lbl_Conquest->enableItalics();
		this->addChild(lbl_Conquest);
	}

	return true;
}

void PlayerInformationScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void PlayerInformationScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		string name = ((Node*)pSender)->getName();
		if (name == "btn_CardScene") {
			Director::getInstance()->replaceScene(CardScene::createScene());
		}
	}
}
