#include "Player.h"
#include"Tool.h"
PlayerInfo *Player::currentPlayer = new PlayerInfo();
PlayerInfo *Player::opponentPlayer = new PlayerInfo();

void Player::GetFriendshipLevel(string friendship)
{
	vector<string*> result;
	Tool::CutString(&friendship, result, ",");
	for (auto x : result) {
		vector<string*> vec;
		Tool::CutString(x, vec, ":");
		Player::currentPlayer->friendshipLevel[*vec[0]] = Tool::ConvertStringToInt(*vec[1]);
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

