#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include"cocos2d.h"
#include"SimpleAudioEngine.h"
#include"Tool.h"
USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

class Audio {
public:
	static string GetBackgroundAudio();
	static string GetBrightAudio();
	static string GetSadAudio();
	static string GetButtonClickAudio();
	static SimpleAudioEngine* audio;
	static string GetSpawnAudio();
};