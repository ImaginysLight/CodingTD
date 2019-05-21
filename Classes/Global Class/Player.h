#pragma once
#include<iostream>
#include<vector>
using namespace std;

class Player {
public:
	//Phần trên csdl
	int id = 0;
	string username = "";
	string password = "";
	string character_name = "";
	string room_name = "";
	int submit_available = 0;
	int status = 0;

	//Phần trong gameplay
	string elementName = "";

};