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

	auto lbl_Username = Label::create(Player::currentPlayer->username, "fonts/custom_font.ttf", Tool::defaultTextSize*1.5);
	lbl_Username->setPositionX(-300);
	lbl_Username->setAnchorPoint(Vec2(0, 0.5));
	result->addChild(lbl_Username);

	auto levelInfo = Player::CalculateLevel(Player::currentPlayer->experience);
	
	string level = to_string(Player::CalculateLevel(Player::currentPlayer->experience).first);
	auto levelBar = Tool::CreateBar("Level", Color4B::WHITE, Size(200, 4), Color3B(175, 225, 250));
	((ProgressTimer*)levelBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->experience / (float)levelInfo.second *100.0));
	((Label*)levelBar->getChildByName("Content"))->setPositionY(14);
	levelBar->setPositionX(75);
	result->addChild(levelBar);

	auto lbl_Level = Label::create(level + " / 25", "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_Level->setPosition(Vec2(75, -18));
	result->addChild(lbl_Level);

	auto expBar = Tool::CreateBar("Experience", Color4B::WHITE, Size(200, 4), Color3B(175, 225, 250));
	((ProgressTimer*)expBar->getChildByName("Front Bar"))->setPercentage((Player::currentPlayer->experience / (float)levelInfo.second *100.0));
	((Label*)expBar->getChildByName("Content"))->setPositionY(14);
	expBar->setPositionX(300);
	result->addChild(expBar);
	
	auto lbl_Exp = Label::create(to_string(Player::currentPlayer->experience) + " / " + to_string(levelInfo.second), "fonts/custom_font.ttf", Tool::defaultTextSize);
	lbl_Exp->setPosition(Vec2(300, -18));
	result->addChild(lbl_Exp);

	return result;
}

void Player::Logout()
{
	Tool::Socket_Client->_client->emit("Logout", "{\"id\":\"" + to_string(Player::currentPlayer->id) + "\"}");
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

