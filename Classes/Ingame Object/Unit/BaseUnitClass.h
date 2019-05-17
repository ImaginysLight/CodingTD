#pragma once
#include "cocos2d.h"
#include"../../Global Class/Tool.h"
#include"../IngameObject.h" 
#include"../Skill/BaseSkillClass.h"
class BaseSkillClass;
USING_NS_CC;
using namespace std;

extern struct DamageReceive {
	int attackerId = 0;
	float damage = 0;
	float triggerTime = 0;
	string animateName = "";
	string special = ""; // Sát thương gây thêm hiệu ứng đặc biệt khác với công thức thường sẽ được xử lý riêng.
	DamageReceive(int attackerId, float damage, float triggerTime, string animateName, string special);
};

extern struct StatusReceive {
	string statusName = "";
	string statusInfluence = "";
	float value = 0;
	float releaseStatusTime = 0;
	int statusOrder = 0; // thứ tự apply status: tăng thẳng vào base > tăng % > tăng bonus
	StatusReceive(string statusName, string statusInfluence, float value, float releaseStatusTime, int statusOrder);
};

extern struct HardEffect {
	string effectName = "";
	float triggerTime = 0;
	float releaseTime = 0;
	HardEffect(string effectName, float triggerTime, float releaseTime);
};

// Thể hiện đối tượng bất kỳ thuộc về 1 người chơi trong game scene
class BaseUnitClass {
public:
	//Các thứ static
	static vector<BaseUnitClass*> AllIngameUnit_Vector;
	static bool SortByHealth(BaseUnitClass* unit1, BaseUnitClass* unit2);
	static bool SortStatus(StatusReceive stt1, StatusReceive stt2);
	static BaseUnitClass* GetUnitById(int id);
	static int Unit_Id_Counter;
	static void ProcessSpecial(int id, DamageReceive &dmg); //Xử lý các thứ ngoại lệ
	static void onStatusTrigger(int id, StatusReceive &stt);

	//Các thông số cơ bản
	string name = "";
	string description = "";
	int goldCost = 0;
	int levelRequired = 0;
	int maxHealth = 0;
	int currentHealth = maxHealth;
	float baseAttack = 0;
	float attack = 0;
	float baseDefense = 0;
	float defense = 0;
	float baseMoveSpeed = 0;
	float moveSpeed = 0;
	float baseAttackSpeed = 0;
	float attackSpeed = 0;
	float range = 0;
	float baseRegeneration = 0;
	float regeneration = 0;

	//Các thông số nâng cấp
	string upgradeName = "";
	int upgradeGoldCost = 0;
	int upgradeEnergyCost = 0;
	int upgradeLevelRequired = 0;

	//Các node biểu hiện unit trong game
	Node* root;
	Sprite* sprite;
	ProgressTimer* healthBar;

	//Các thông số trong game
	float delayTimeAfterAttack = 0.15; // Dừng lại 0.15s sau khi thực hiện animate attack
	int animationIndexOnTriggerAttack = 0; //Tức là khi nó thực hiện tới cái sprite attack thứ mấy thì đạn mới bay ra
	int unitId = 0;
	int ownerPlayerId = 0;
	string animateName = "";
	int line = 0;
	bool isAlive = true;
	bool isOwned = true;

	//Khởi tạo nhân vật
	void UpdateIngameInfo(string spriteName, int unitId, int ownerPlayerId, bool isOwned, string animateName, int line);

	//Update nhân vật mỗi frame
	string action = "Idle";
	virtual void Update();

	//Các hàm action
	virtual void Die();
	virtual void Move();
	virtual void Attack(vector<BaseUnitClass*>& targets);
	virtual vector<BaseUnitClass*> FindTargets();
	virtual void StotpAction(string actionName);

	//Hồi máu mỗi giây
	float nextRegenerationTriggerTime = Tool::currentIngameTime + 1;
	virtual void Regeneration();
	void UpdateHealthBar();

	//Các sát thương gây lên unit sẽ trigger bị động cho giống như đạn bay trúng
	//Giả sử tốc độ đạn của mọi unit là 0.2s / 100 distance
	vector<DamageReceive> damageReceive;
	virtual void onDamageReceive(DamageReceive dmg);

	//Các hiệu ứng trên unit liên quan tới stat, như trừ damage, tăng hồi máu, slow speed....
	vector<StatusReceive> statusReceive;
	void ClearStatusStat(string statusInfluence);
	virtual void ReprocessAllStatus(string influence);
	virtual void ApplyStatus(StatusReceive stt);
	
	//Các hiệu ứng cứng mà không biết xử lý như nào (Stun, hoảng sợ,...)
	vector<HardEffect> hardEffect;


	BaseUnitClass();
	~BaseUnitClass();

};