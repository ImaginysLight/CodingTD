#pragma once
#include"cocos2d.h"
#include"ui\CocosGUI.h"
#include<vector>
#include<unordered_map>
#include<codecvt>
#include <cstdlib>
#include <ctime>
#include<algorithm>
#include<string>
#include "SocketClient.h"
#include "json\document.h"
#include "json\rapidjson.h"
#include<random>

#include <network/SocketIO.h>
using namespace cocos2d::network;


USING_NS_CC;
using namespace std;
using namespace cocos2d::ui;


class Tool{
public:
	Tool() {};
	//Các biến toàn cục
	static SocketClient* Socket_Client;
	static int defaultTextSize; // Để thay đổi độ lớn text hàng loạt cho dễ
	static float currentIngameTime; //  Thời gian hiện tại trong game

	//Các hàm xử lý chuỗi
	static void CutString(string* str, vector <string*> &vec, string cutPoint); //muốn cắt tại @ thì CutString(a, Vec, "@");
	static string ConvertUTF16ToString(wstring utf16);
	static int ConvertStringToInt(string a);

	//Các hàm tạo node tổng quát
	static Label* CreateLabel(string content, int size = Tool::defaultTextSize, Color4B color = Color4B::WHITE, TextHAlignment align = TextHAlignment::LEFT);
	static Button* CreateButtonWithoutSprite(string name, string titleText, int size = Tool::defaultTextSize, Color3B color = Color3B::WHITE);
	static Button* CreateButtonWithSpirte(string name, string spritePath);
	static Node* CreateBar(string content = "", Color4B textColor = Color4B::WHITE, Size size = Size(200,25), Color3B frontColor = Color3B::WHITE, Color4F backColor = Color4F(0.69, 0.69, 0.69, 0.33));
	static Node* CreateNotificationTable(string lblContent, string btnRightContent, string btnLeftContent = "", Size tableSize = Size(384,135));
	static EditBox* CreateEditBox(string placeholder, Size size = Size(300,35));

	//Xử lý size
	static void setNodeSize(Node* node, int width, int height);
	static void updateScale(Vector<Node*> node, int scaleX, int scaleY);

	static void Button_ChangeState(Button*& btn, bool isShow, float fadeTime);
	static int CreateRandomNumber(int begin, int end);
};
