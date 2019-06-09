﻿#include"Tool.h"
using namespace std;
#include "json\document.h"
#include "json\rapidjson.h"
#include <network/SocketIO.h>

int Tool::defaultTextSize = 20;
float Tool::currentIngameTime = 0;

SocketClient* Tool::Socket_Client = new SocketClient();

void Tool::setNodeSize(Node* node, int width, int height){
	node->setScaleX(width/ node->getBoundingBox().size.width);
	node->setScaleY(height / node->getBoundingBox().size.height);
}

void Tool::updateScale(Vector<Node*> node, int scaleX, int scaleY){
	for (auto x : node){
		x->setScaleX(x->getScaleX()*scaleX);
		x->setScaleY(x->getScaleY()*scaleY);
	}
}


string Tool::ConvertUTF16ToString(wstring utf16) {
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> convert;
	std::string result = convert.to_bytes(utf16);
	return result;
}


void Tool::CutString(string* str, vector <string*> &vec, string cutPoint) {
	int root = 0;
	size_t pos = str->find(cutPoint);
	while (pos != std::string::npos) {
		string* temp = new string;
		*temp = str->substr(root, pos - root);
		vec.push_back(temp);
		root = pos + cutPoint.size();
		pos = str->find(cutPoint, pos + 1);
	}
	string* temp = new string;
	*temp = str->substr(root, str->size() - root);
	vec.push_back(temp);
}

int Tool::ConvertStringToInt(string a) {
	int result = 0;
	for (int i = 0; i < a.size(); i++) {
		result += ((int)a[a.size() - i - 1] - 48) * pow(10.0, i);
	}
	return result;
}

Label * Tool::CreateLabel(string content, int size, Color4B color, CCTextAlignment align)
{
	auto lbl_Result = Label::create(content, "fonts/arial.ttf", size);
	lbl_Result->setTextColor(color);
	lbl_Result->setAlignment(align);
	return lbl_Result;
}

Button * Tool::CreateButtonWithoutSprite(string name, string titleText, int size, Color3B color)
{
	Button* btn_Result = Button::create();
	btn_Result->setName(name);
	btn_Result->setTitleText(titleText);
	btn_Result->setTitleFontSize(size);
	btn_Result->setTitleColor(color);
	return btn_Result;
}

void Tool::Button_ChangeState(Button *& btn, bool isShow, float fadeTime)
{
	if (isShow) {
		btn->setVisible(true);
		btn->setEnabled(true);
		btn->runAction(FadeIn::create(fadeTime));
	}
	else {
		btn->setEnabled(false);
		btn->runAction(FadeOut::create(fadeTime));
	}
}

int Tool::CreateRandomNumber(int begin, int end)
{
	srand(time(NULL));
	return rand() % (end - begin + 1) + begin;
}

pair<ProgressTimer*, DrawNode*> Tool::CreateBar(int width, int height, Color3B frontColor, Color4F backColor)
{
	auto frontBar = ProgressTimer::create(Sprite::create("Sprites/Health Bar.png"));
	frontBar->setType(ProgressTimer::Type::BAR);
	frontBar->setBarChangeRate(Vec2(1, 0));
	frontBar->setMidpoint(Vec2(0, 0));
	frontBar->setPercentage(100);
	frontBar->setAnchorPoint(Vec2(0, 0));
	frontBar->setColor(frontColor);
	Tool::setNodeSize(frontBar, width, height);

	auto background = DrawNode::create();
	background->clear();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(0, 0);
	rectangle[1] = Vec2(0, frontBar->getBoundingBox().size.height);
	rectangle[2] = Vec2(frontBar->getBoundingBox().size.width, frontBar->getBoundingBox().size.height);
	rectangle[3] = Vec2(frontBar->getBoundingBox().size.width, 0);
	background->drawPolygon(rectangle, 4, backColor, 1, backColor);
	return { frontBar,background };
}
