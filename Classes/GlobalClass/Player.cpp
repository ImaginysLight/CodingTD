#include "Player.h"

PlayerInfo *Player::currentPlayer = new PlayerInfo();
PlayerInfo *Player::opponentPlayer = new PlayerInfo();
PlayerInfo Player::oldPlayerInfo;

void Player::GetFriendshipLevel(PlayerInfo* player, string friendship)
{
	vector<string*> result;
	Tool::CutString(&friendship, result, ",");
	for (auto x : result) {
		vector<string*> vec;
		Tool::CutString(x, vec, ":");
		player->friendshipLevel[*vec[0]] = Tool::ConvertStringToInt(*vec[1]);
	}
}
pair<int,int> Player::CalculateLevel(int exp)
{
	vector<int> expAtLevel = vector<int>{
		0,
			100, 225, 375, 550, 750,
			975, 1225, 1500, 1800, 2125,
			2475, 2850, 3250, 3675, 4125,
			4600, 5100, 5625, 6175, 6750,
			7350, 7975, 8625, 9300, 10000
	};
	for (int i = 1; i < expAtLevel.size(); i++) {
		if (exp < expAtLevel[i])
			return { (i - 1) , expAtLevel[i] };
	}
	return { expAtLevel.size() - 1,expAtLevel[expAtLevel.size() - 1] };
}

void Player::UploadPlayerInfo(PlayerInfo * player)
{
	auto friendship = Player::GetFriendshipLevelString(player);
	Tool::Socket_Client->_client->emit("Upload_Player_Info", "{\"id\":\"" + to_string(player->id) + "\""
		+ ", \"username\":\"" + player->username + "\""
		+ ", \"password\":\"" + player->password + "\""
		+ ", \"room_name\":\"" + player->room_name + "\""
		+ ", \"experience\":\"" + to_string(player->experience) + "\""
		+ ", \"correct_answer\":\"" + to_string(player->total_correctAnswer) + "\""
		+ ", \"wrong_answer\":\"" + to_string(player->total_wrongAnswer) + "\""
		+ ", \"total_win\":\"" + to_string(player->total_win) + "\""
		+ ", \"total_lose\":\"" + to_string(player->total_lose) + "\""
		+ ", \"total_kill\":\"" + to_string(player->total_kill) + "\""
		+ ", \"friendship_point\":\"" + to_string(player->friendshipPoint) + "\""
		+ ", \"friendship_level\":\"" + friendship + "\""
		+ ", \"submit_available\":\"" + to_string(player->submit_available) + "\""
		+ ", \"status\":\"" + to_string(player->status) + "\""
	+ "}");
}

cocos2d::Node * Player::CreatePlayerOutgameInfoGUI()
{
	Node* result = Node::create();

	auto levelInfo = Player::CalculateLevel(Player::currentPlayer->experience);

	auto sp_Level = Sprite::create("UI/LobbyScene/btn_Level.png");
	sp_Level->setScale(1.25);
	result->addChild(sp_Level);

	auto lbl_Level = Tool::CreateLabel(to_string(levelInfo.first),Tool::defaultTextSize*0.8,Color4B::RED);
	lbl_Level->enableBold();
	result->addChild(lbl_Level);
	
	auto expBar = Tool::CreateBar(to_string(Player::currentPlayer->experience) + " / " + to_string(levelInfo.second), Color4B::WHITE, Size(200, 4), Color3B(175, 225, 250));
	((ProgressTimer*)expBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->experience / (float)levelInfo.second *100.0));
	((Label*)expBar->getChildByName("Content"))->setPositionY(12);
	expBar->setPosition(Vec2(0, -50));
	result->addChild(expBar);
	
	auto lbl_PlayerName = Tool::CreateLabel(Player::currentPlayer->username, Tool::defaultTextSize*1.5);
	lbl_PlayerName->setPosition(Vec2(0, 75));
	result->addChild(lbl_PlayerName);

	/*auto lbl_PlayerName = Tool::CreateLabel(Player::currentPlayer->username, Tool::defaultTextSize*1.5);
	result->addChild(lbl_PlayerName);

	auto levelInfo = Player::CalculateLevel(Player::currentPlayer->experience);

	auto lbl_Level = Tool::CreateLabel("Level: " + to_string(levelInfo.first));
	lbl_Level->setPosition(Vec2(lbl_PlayerName->getBoundingBox().size.width, 0));
	result->addChild(lbl_Level);

	auto lbl_Exp = Tool::CreateLabel("Experience");
	lbl_Exp->setPosition(Vec2(lbl_Level->getPositionX() +  175, 12));
	result->addChild(lbl_Exp);

	auto expBar = Tool::CreateBar(to_string(Player::currentPlayer->experience) + " / " + to_string(levelInfo.second), Color4B::RED, Size(200, 25), Color3B(250, 250, 200));
	((ProgressTimer*)expBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->experience / (float)levelInfo.second *100.0));
	expBar->setPosition(Vec2(lbl_Level->getPositionX() + 175, -12));
	result->addChild(expBar);

	auto lbl_Friendship = Tool::CreateLabel("Friendship: " + to_string(Player::currentPlayer->friendshipPoint));
	lbl_Friendship->setPosition(Vec2(lbl_Level->getPositionX() + 350, 0));
	lbl_Friendship->setName("lbl_Friendship");
	result->addChild(lbl_Friendship);*/
	return result;
}

void Player::ClearOpponentInfo()
{
	Player::opponentPlayer = new PlayerInfo();
}

void Player::GetOpponentPlayerInfo(int id)
{

}

void Player::GetCurrentPLayerInfo(int id)
{
}

string Player::GetFriendshipLevelString(PlayerInfo * player)
{
	string result = "";
	for (auto card : player->friendshipLevel) {
		result += card.first + ":" + to_string(card.second) + ",";
	}
	return result.substr(0, result.size() - 1);
}

