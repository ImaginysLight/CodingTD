#pragma once
#include "cocos2d.h"
#include"../Tool.h"
#include"../IngameObject.h"

USING_NS_CC;
using namespace std;

// Thể hiện đối tượng bất kỳ thuộc về 1 người chơi trong game scene
class BaseObjectClass {
public:
	//Các thứ static
	static vector<BaseObjectClass*> player1_Object;
	static vector<BaseObjectClass*> player2_Object;
	static bool SortByHealth(BaseObjectClass* object1, BaseObjectClass* object2);
	static BaseObjectClass* GetObjectById(int id);


	struct DamageReceive {
		int healthLose = 0;
		float triggerTime = 0;
		string animateName = "";
		int sourceId = 0;
		DamageReceive(int healthLose, float triggerTime, string animateName, int sourceId);
	};

	struct StatusReceive {
		int sourceId = 0;
		string statusName = "";
		float endTime = 0;
		StatusReceive(int sourceId, string statusName, float endTime);

	};
	// thông số cơ bản
	string objectName = "";
	int levelRequired = 1;
	string description = "";
	int cost = 0;
	int maxHealth = 0;
	int currentHealth = maxHealth;
	float attack = 0;
	int defense = 0;
	int speed = 0;
	float attackRate = 1.0;
	int range = 0;
	int regeneration = 0;
	string special = "";

	string upgradeTo = "";
	int upgradeGold = 0;
	int upgradeEnergy = 0;
	int upgradeLevelRequired = 1;

	// thông tin trong game
	int id = 0;
	float spawnTime = Tool::currentIngameTime;
	float nextRegeneration = spawnTime + 1;
	string animateName = "";
	string action = "Idle";
	Node* root;
	ProgressTimer* healthBar;
	Sprite* sprite;
	bool isLeft = true;
	bool isAlive = true;
	int line = 0;
	int isStand = false; // Object ko có quyền di chuyển

	
	void UpdateIngameInfo(string spriteName, bool isStand);
	void UpdateHealthBar();
	void CreateHealthBar();

	vector<DamageReceive> damageReceive;
	vector<StatusReceive> statusReceive;
	void RemoveStatus(string statusName);
	virtual vector<BaseObjectClass*> FindTargets(vector<BaseObjectClass*>& targets);
	virtual void ExcuteDamageReceive(DamageReceive dmg);
	virtual void CheckStatusEnd();
	virtual void Regeneration();
	virtual void UpdateAction(vector<BaseObjectClass*>& vec);
	virtual void StopMove();
	virtual void Move();
	virtual void Attack(BaseObjectClass* &target);
	virtual void Die();
	

	BaseObjectClass();
	~BaseObjectClass();

};