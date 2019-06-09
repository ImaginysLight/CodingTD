#pragma once
#include "cocos2d.h"
#include "../Global Class/Tool.h"
USING_NS_CC;


static class IngameObject {
public:
	static void loadIngameObjectStaticVariables();
	//Bảng màu skill cho từng element
	static unordered_map<string, Color3B> elementColor;
	//Điểm xuất phát
	static unordered_map<string, Vec2> spawnPoint;


	
	//Preload animation
	static Animate* CreateAnimate(string prefix, string suffix, int numBegin, int numEnd, float delay);
	static void loadAnimate();
	static pair<string, Animate*> CreateAnimateWithKey(string characterName, string action, int numBegin, int numEnd);
	static unordered_map<string, Animate*> animate;
	static string GetKingdomByElement(string element);
	
};