#pragma once
#include "cocos2d.h"
#include"../IngameObject.h"
#include"../Unit/BaseUnitClass.h"
USING_NS_CC;
using namespace std;

// Thể hiện đối tượng bất kỳ thuộc về 1 người chơi trong game scene
struct SkillRequired {
	int energy;
	int level;
	bool needToSelect;
	SkillRequired(int energy, int level, bool needToSelect = false);
	SkillRequired();
};
class BaseSkillClass {
public:
	//Các thứ static
	static vector<BaseSkillClass*> AllIngameSkill_Vector;
	static unordered_map<string, SkillRequired> SkillRequirement;
	static void LoadSkillRequirement();
	

	//Các thông số cơ bản
	string name = "";
	string description = "";
	int areaOfEffect = 0;
	int lineOfEffect = 0;
	float damage = 0;
	float nextTriggerTime = 0;
	float expiredTime = 0;
	bool isReleased = false;

	bool isOwned = true;
	//Các node biểu hiện unit trong game
	Node* root;
	Sprite* sprite;
	string animateName = "";
	bool isAddedChild = false;

	virtual void Update();
	virtual void onTrigger();

	BaseSkillClass();
	~BaseSkillClass();

};