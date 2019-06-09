#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
using namespace std;

extern struct PlayerInfo {
	//Phần lấy từ cơ sở dữ liệu
	int id = 0;
	string username = "";
	string password = "";
	string room_name = "";

	int experience = 0;
	int total_kill = 0;
	int total_correctAnswer = 0;
	int total_wrongAnswer = 0;
	int total_win = 0;
	int total_lose = 0;
	int friendshipPoint = 0;
	unordered_map<string, int> friendshipLevel = unordered_map<string, int>{
		{"Frost Wyvern", 0},
		{"Polar Bear", 0},
		{"Volcarona", 0},
		{"Enraged Ursa", 0},
		{"Poisonous Butterfly", 0},
		{"Vampire Dragon", 0},
		{"Hotheaded Gunner", 0},
		{"UFO Driver", 0},
		{"Winged Orc", 0},
		{"Helicopter", 0},
		{"Crazy Wolf", 0},
		{"Dead Walker", 0},
		{"Liquid Assassin", 0},
		{"Elemental Alien", 0}
	};

	int submit_available = 0;
	int status = 0;

	//Phần trong gameplay
	string elementName = "";
	vector<string> picked_units;
};

static class Player {
public:
	static PlayerInfo *currentPlayer, *opponentPlayer;
	static void ClearOpponentInfo();
	static void GetOpponentPlayerInfo(int id);
	static void GetCurrentPLayerInfo(int id);

	static void GetFriendshipLevel(string friendship);
	static pair<int, int> CalculateLevel(int exp);

};