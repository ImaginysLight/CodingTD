#include "Player.h"
#include"Tool.h"
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
	if (player->friendshipLevel.size() != 14) return "";
	for (auto card : player->friendshipLevel) {
		result += card.first + ":" + to_string(card.second) + ",";
	}
	return result.substr(0, result.size() - 1);
}

