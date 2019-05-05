﻿#pragma once
#include"Player.h"
#include"Question.h"
#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include<vector>
#include<unordered_map>
#include<codecvt>
#include <cstdlib>
#include <ctime>
#include<algorithm>
#include<string>





USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;


static class Tool{
public:
	//Các biến toàn cục
	static Player* currentPlayer, *opponentPlayer;
	static int defaultTextSize; // Để thay đổi độ lớn text hàng loạt cho dễ
	static float currentIngameTime; //  Thời gian hiện tại trong game

	//Các hàm xử lý chuỗi
	static void CutString(string* str, vector <string*> &vec, string cutPoint); //muốn cắt tại @ thì CutString(a, Vec, "@");
	static void CutString(string str, vector <string> &vec, string cutPoint);
	static string ConvertUTF16ToString(wstring utf16);
	static int ConvertStringToInt(string a);

	//Các hàm tạo node tổng quát
	static Label* CreateLabel(string content, int size = Tool::defaultTextSize, Color4B color = Color4B::WHITE, CCTextAlignment align = CCTextAlignment::LEFT);
	static Button* CreateButtonWithoutSprite(string name, string titleText, int size = Tool::defaultTextSize, Color3B color = Color3B::WHITE);

	//Xử lý size
	static void setNodeSize(Node* node, int width, int height);
	static void updateScale(Vector<Node*> node, int scaleX, int scaleY);
	
	
};