#include "PlayerInformationScene.h"
using namespace CocosDenshion;
USING_NS_CC;
cocos2d::Scene * PlayerInformationScene::createScene()
{
	return PlayerInformationScene::create();
}

bool PlayerInformationScene::init()
{
	visibleSize = Director::getInstance()->getVisibleSize();

	auto sp_Background = Sprite::create("UI/Login/BG.png");
	sp_Background->setPosition(visibleSize / 2);
	this->addChild(sp_Background, -1);

	auto border1 = Sprite::create("Trophy/Trophy Border.png");
	border1->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.45));
	//Tool::setNodeSize(border1, visibleSize.width*0.32, visibleSize.height*0.6);
	this->addChild(border1);

	auto border2 = Sprite::create("Trophy/Trophy Border.png");
	border2->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.45));
	//Tool::setNodeSize(border2, visibleSize.width*0.32, visibleSize.height*0.6);
	this->addChild(border2);

	auto border3 = Sprite::create("Trophy/Trophy Border.png");
	border3->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.45));
	//Tool::setNodeSize(border3, visibleSize.width*0.32, visibleSize.height*0.6);
	this->addChild(border3);

	auto playerInfo = Player::CreatePlayerOutgameInfoGUI();
	playerInfo->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.9));
	this->addChild(playerInfo);

	auto btn_LobbyScene = Tool::CreateButtonWithSpirte("btn_LobbyScene", "UI/rank/btn_back.png");
	btn_LobbyScene->setPosition(Vec2(visibleSize.width*0.1, visibleSize.height*0.9));
	btn_LobbyScene->addTouchEventListener(CC_CALLBACK_2(PlayerInformationScene::btn_Click, this));
	this->addChild(btn_LobbyScene);

	auto knowledge = Trophy::CalculateKnowledgeTrophy(Player::currentPlayer->total_correctAnswer);
	auto lbl_Knowledge = Tool::CreateLabel("Knowledge Trophy\n\n\n\n\n\n\n" + knowledge.name, Tool::defaultTextSize*1.2, Color4B(175, 225, 200, 255), cocos2d::TextHAlignment::CENTER);
	lbl_Knowledge->setAnchorPoint(Vec2(0.5, 1));
	lbl_Knowledge->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.625));
	this->addChild(lbl_Knowledge);

	auto battle = Trophy::CalculateBattleTrophy(Player::currentPlayer->total_kill);
	auto lbl_Battle = Tool::CreateLabel("Battle Trophy\n\n\n\n\n\n\n" + battle.name, Tool::defaultTextSize*1.2, Color4B(175, 225, 250, 255), cocos2d::TextHAlignment::CENTER);
	lbl_Battle->setAnchorPoint(Vec2(0.5, 1));
	lbl_Battle->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.625));
	this->addChild(lbl_Battle);

	auto conquest = Trophy::CalculateConquestTrophy(Player::currentPlayer->total_win);
	auto lbl_Conquest = Tool::CreateLabel("Conquest Trophy\n\n\n\n\n\n\n" + conquest.name, Tool::defaultTextSize*1.22, Color4B::WHITE, cocos2d::TextHAlignment::CENTER);
	lbl_Conquest->setAnchorPoint(Vec2(0.5, 1));
	lbl_Conquest->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.625));
	this->addChild(lbl_Conquest);

	if (knowledge.level != 0) {
		auto sp_Knowledge = Sprite::create("Trophy/Knowledge Trophy " + to_string(knowledge.level) + ".png");
		sp_Knowledge->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.45));
		this->addChild(sp_Knowledge, 1);

		auto lbl_BonusKnowledge = Tool::CreateLabel(
			"+" + to_string(knowledge.correctGoldRate) + "% Gold for Correct Answer\n\n" +
			"+" + to_string(knowledge.wrongGoldRate) + "% Gold for Wrong Answer",
			Tool::defaultTextSize*0.69, Color4B(175, 225, 200, 255), cocos2d::TextHAlignment::CENTER);
		lbl_BonusKnowledge->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.17));
		lbl_BonusKnowledge->enableBold();
		lbl_BonusKnowledge->enableItalics();
		this->addChild(lbl_BonusKnowledge);
	}
	if (battle.level != 0) {
		auto sp_Battle = Sprite::create("Trophy/Battle Trophy " + to_string(battle.level) + ".png");
		sp_Battle->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.45));
		this->addChild(sp_Battle, 1);

		auto lbl_Battle = Tool::CreateLabel(
			"+" + to_string(battle.defeatGoldRate) + "% Gold when Defeat Enemy\n\n" +
			"+" + CCString::createWithFormat("%.1f",(float)battle.defeatEnergyRate/10)->getCString() + "% Energy when Defeat Enemy",
			Tool::defaultTextSize*0.69, Color4B(175, 225, 250, 255), cocos2d::TextHAlignment::CENTER);
		lbl_Battle->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.17));
		lbl_Battle->enableBold();
		lbl_Battle->enableItalics();
		this->addChild(lbl_Battle);
	}
	if (conquest.level != 0) {
		auto sp_Conquest = Sprite::create("Trophy/Conquest Trophy " + to_string(conquest.level) + ".png");
		sp_Conquest->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.45));
		Tool::setNodeSize(sp_Conquest, 120, 120);
		this->addChild(sp_Conquest, 1);

		auto lbl_Conquest = Tool::CreateLabel(
			(string)"+" + CCString::createWithFormat("%.1f", conquest.bonusGold)->getCString() + " Gold per second\n\n" +
			"+" + CCString::createWithFormat("%.1f", conquest.bonusEnergy)->getCString() + " Energy per second",
			Tool::defaultTextSize*0.69, Color4B::WHITE, cocos2d::TextHAlignment::CENTER);
		lbl_Conquest->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.17));
		lbl_Conquest->enableBold();
		lbl_Conquest->enableItalics();
		this->addChild(lbl_Conquest);
	}

	auto lbl_TotalCorrectAnswer = Tool::CreateLabel("Total Correct Answer");
	lbl_TotalCorrectAnswer->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.75));
	this->addChild(lbl_TotalCorrectAnswer);

	auto correntAnswerBar = Tool::CreateBar(to_string(Player::currentPlayer->total_correctAnswer) + " / " + to_string(knowledge.ExpToNext), Color4B::MAGENTA, Size(200, 25), Color3B(175, 225, 200));
	((ProgressTimer*)correntAnswerBar->getChildByName("Front Bar"))->setPercentage(Player::currentPlayer->total_correctAnswer / (float)knowledge.ExpToNext * 100);
	correntAnswerBar->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.7));
	this->addChild(correntAnswerBar);

	string accurary = CCString::createWithFormat("Correct Rate: %.2f", Player::currentPlayer->total_correctAnswer / (float)(Player::currentPlayer->total_correctAnswer + Player::currentPlayer->total_wrongAnswer) * 100.0)->getCString();
	accurary += CCString::create("%")->getCString();
	auto lbl_AnswerAccurary = Tool::CreateLabel(accurary);
	lbl_AnswerAccurary->setPosition(Vec2(visibleSize.width*0.175, visibleSize.height*0.65));
	this->addChild(lbl_AnswerAccurary);

	auto lbl_TotalWin = Tool::CreateLabel("Total Win");
	lbl_TotalWin->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.75));
	this->addChild(lbl_TotalWin);

	auto winBar = Tool::CreateBar(to_string(Player::currentPlayer->total_win) + " / " + to_string(conquest.ExpToNext), Color4B::MAGENTA, Size(200, 25), Color3B::WHITE);
	((ProgressTimer*)winBar->getChildByName("Front Bar"))->setPercentage(Player::currentPlayer->total_win / (float)conquest.ExpToNext * 100);
	winBar->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.7));
	this->addChild(winBar);

	string winRate = CCString::createWithFormat("Winrate: %.2f", Player::currentPlayer->total_win / (float)(Player::currentPlayer->total_lose + Player::currentPlayer->total_win) * 100.0)->getCString();
	winRate += CCString::create("%")->getCString();
	auto lbl_Winrate = Tool::CreateLabel(winRate);
	lbl_Winrate->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.65));
	this->addChild(lbl_Winrate);

	auto lbl_TotalKill = Tool::CreateLabel("Total Kill");
	lbl_TotalKill->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.75));
	this->addChild(lbl_TotalKill);

	auto killBar = Tool::CreateBar(to_string(Player::currentPlayer->total_kill) + " / " + to_string(battle.ExpToNext),Color4B::MAGENTA,Size(200,25),Color3B(175,225,250));
	((ProgressTimer*)killBar->getChildByName("Front Bar"))->setPercentage(Player::currentPlayer->total_kill / (float)battle.ExpToNext * 100);
	killBar->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.7));
	this->addChild(killBar);

	string killPerMatch = CCString::createWithFormat("Kill / Match: %.2f", Player::currentPlayer->total_kill / (float)(Player::currentPlayer->total_win + Player::currentPlayer->total_lose))->getCString();
	auto lbl_KillPerMatch = Tool::CreateLabel(killPerMatch);
	lbl_KillPerMatch->setPosition(Vec2(visibleSize.width*0.825, visibleSize.height*0.65));
	this->addChild(lbl_KillPerMatch);
	

	return true;
}

void PlayerInformationScene::menuCloseCallback(cocos2d::Ref * pSender)
{
	Director::getInstance()->end();
}

void PlayerInformationScene::btn_Click(Ref * pSender, cocos2d::ui::Button::Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::ENDED) {
		auto audio = SimpleAudioEngine::getInstance();
		audio->playEffect(Audio::GetButtonClickAudio().c_str(), false);
		string name = ((Node*)pSender)->getName();
		if (name == "btn_LobbyScene") {
			Director::getInstance()->replaceScene(LobbyScene::createScene());
		}
	}
}
