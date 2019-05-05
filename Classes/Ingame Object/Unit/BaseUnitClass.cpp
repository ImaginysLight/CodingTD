#include "BaseUnitClass.h"
using namespace std;


vector<BaseUnitClass*> BaseUnitClass::AllIngameUnit_Vector;

int BaseUnitClass::Unit_Id_Counter = 0;
BaseUnitClass* BaseUnitClass::GetUnitById(int id)
{
	for (auto unit : BaseUnitClass::AllIngameUnit_Vector) {
		if (unit->unitId == id) return unit;
	}
	return nullptr;
}


bool BaseUnitClass::SortByHealth(BaseUnitClass* unit1, BaseUnitClass* unit2) {
	return (unit1->currentHealth < unit2->currentHealth);
}

bool BaseUnitClass::SortStatus(StatusReceive stt1, StatusReceive stt2) {
	return (stt1.statusOrder < stt2.statusOrder);
}

void BaseUnitClass::UpdateIngameInfo(string spriteName, int unitId, int ownerPlayerId, bool isOwned, string animateName, int line) {
	attack = baseAttack;
	defense = baseDefense;
	attackSpeed = baseAttackSpeed;
	moveSpeed = baseMoveSpeed;
	regeneration = baseRegeneration;

	this->isOwned = isOwned;
	this->ownerPlayerId = ownerPlayerId;
	this->unitId = unitId;
	this->line = line;
	this->animateName = animateName;
	root = Node::create();
	sprite = Sprite::create(spriteName);
	healthBar = ProgressTimer::create(Sprite::create("Sprites/Health Bar.png"));
	healthBar->setType(ProgressTimer::Type::BAR);
	healthBar->setBarChangeRate(Vec2(1, 0));
	healthBar->setMidpoint(Vec2(0, 0));
	healthBar->setPercentage(100);
	healthBar->setPosition(this->sprite->getPosition() + Vec2(0, this->sprite->getBoundingBox().size.height*0.5 + 10));
	if (this->isOwned) this->healthBar->setColor(Color3B::GREEN);
	else  this->healthBar->setColor(Color3B::RED);
	Tool::setNodeSize(healthBar, sprite->getBoundingBox().size.width*0.35, 8);
	root->addChild(sprite, 1);
	root->addChild(healthBar, 1);

	auto rectNode = DrawNode::create();
	rectNode->clear();
	Vec2 rectangle[4];
	rectangle[0] = Vec2(0, 0);
	rectangle[1] = Vec2(0, healthBar->getBoundingBox().size.height);
	rectangle[2] = Vec2(healthBar->getBoundingBox().size.width, healthBar->getBoundingBox().size.height);
	rectangle[3] = Vec2(healthBar->getBoundingBox().size.width, 0);

	Color4F grey(0.69, 0.69, 0.69, 0.33);
	rectNode->drawPolygon(rectangle, 4, grey, 1, grey);
	rectNode->setPosition(Vec2(healthBar->getPositionX() -  healthBar->getBoundingBox().size.width / 2,
		healthBar->getPositionY() - healthBar->getBoundingBox().size.height / 2));
	this->root->addChild(rectNode);

	string spawnPosition = this->isOwned ? "1_" : "2_";
	spawnPosition += to_string(line);
	root->setPosition(IngameObject::spawnPoint[spawnPosition]);
	if (this->isOwned) {
		root->setRotation3D(Vec3(0, 180, 0));
		this->healthBar->setMidpoint(Vec2(1, 0));
	}
}

void BaseUnitClass::Update()
{
	//Nếu chết rồi thì hủy đối tượng
	if (!this->isAlive) {
		delete this;
		return;
	}

	//Kiểm tra trigger damage
	for (int i = 0; i < damageReceive.size(); i++) {
		if (damageReceive[i].triggerTime <= Tool::currentIngameTime) {
			this->onDamageReceive(damageReceive[i]);
			damageReceive.erase(damageReceive.begin() + i);
		}
	}

	//Kiểm tra release status
	for (int i = 0; i < statusReceive.size(); i++) {
		if (statusReceive[i].releaseStatusTime <= Tool::currentIngameTime) {
			string influence = statusReceive[i].statusInfluence;
			statusReceive.erase(statusReceive.begin() + i);
			this->ReprocessAllStatus(influence);
		}
	}

	//Regeneration
	if (this->nextRegenerationTriggerTime < Tool::currentIngameTime) {
		this->Regeneration();
		this->nextRegenerationTriggerTime++;
	}


	//Action Die
	if (this->currentHealth < 1 && this->action != "Die") {
		this->Die();
		return;
	}

	//Kiểm tra hiệu ứng cứng
	for (int i = 0; i < hardEffect.size(); i++) {
		if (hardEffect[i].releaseTime < Tool::currentIngameTime) {
			hardEffect.erase(hardEffect.begin() + i);
			continue;
		}
		if (hardEffect[i].triggerTime < Tool::currentIngameTime) {
			if (hardEffect[i].effectName == "Stun" && this->action != "Die") {
				this->StotpAction("Move");
				this->StotpAction("Attack");
				this->action = "Idle";
				return;
			}
		}
	}

	//Action Attack
	if (this->action == "Move" || this->action == "Idle") {
		vector<BaseUnitClass*> targetList = this->FindTargets();
		if (targetList.size() > 0) {
			this->StotpAction("Move");
			this->Attack(targetList);
			return;
		}
		
	}

	//Action Move
	if (this->action == "Idle") this->Move();
}

void BaseUnitClass::Die() {
	this->StotpAction("All");
	this->action = "Die";
	auto animate = IngameObject::animate[this->animateName + "_die"]->clone();
	this->sprite->runAction(Sequence::create(
		animate,
		RemoveSelf::create(),
		CallFunc::create([&]() {	
			this->root->runAction(RemoveSelf::create());
			this->healthBar->runAction(RemoveSelf::create());
			this->action = "Idle";
			this->isAlive = false;
		}),
		nullptr
	));
}

void BaseUnitClass::Attack(vector<BaseUnitClass*>& targets) {
	this->action = "Attack";
	auto animate = IngameObject::animate[this->animateName + "_attack"]->clone();
	animate->setDuration(60 / this->attackSpeed - 0.15); //Cho nó đánh xong dừng lại 0.15s trước khi đánh phát tiếp theo
	this->sprite->runAction(Sequence::create(
		animate,
		DelayTime::create(0.15),
		CallFunc::create([&]() {	this->action = "Idle"; }),
		nullptr
	))->setFlags(1);

	auto delayShootTime = animate->getDuration() *((float)this->animationIndexOnTriggerAttack / animate->getAnimation()->getFrames().size());
	for (auto target : targets) {
		float damage = this->attack;
		//string animateName = this->animateName + "_explosion";
		string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
		float distance = abs(this->root->getPositionX() - target->root->getPositionX());
		float triggerTime = Tool::currentIngameTime + delayShootTime + distance * 0.002;
		target->damageReceive.push_back(DamageReceive(this->unitId, damage, triggerTime, animateName, ""));
	}
}

vector<BaseUnitClass*> BaseUnitClass::FindTargets() {
	vector<BaseUnitClass*> result;
	vector<BaseUnitClass*> shotableTargets;
	//Tìm danh sách địch có thể bắn tới
	for (auto target : BaseUnitClass::AllIngameUnit_Vector) {
		if(
			(this->isOwned != target->isOwned)									// Xem có phải đối thủ không
			&& (target->isAlive && target->action != "Die")						//Xem target còn sống không
			&& (this->line == target->line || target->description == "Kingdom")	//Xem có cùng hàng không || là Kingdom
			&& (abs(target->root->getPositionX() - this->root->getPositionX()) < this->range) // Xem có trong range không
		)
			shotableTargets.push_back(target);
	}
	//Sắp xếp theo máu tăng dần
	std::sort(shotableTargets.begin(), shotableTargets.end(), BaseUnitClass::SortByHealth);

	//Lấy 1 thằng máu thấp nhất
	if (shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	return result;

}

void BaseUnitClass::Move()
{
	this->action = "Move";
	auto animate = IngameObject::animate[this->animateName + "_move"]->clone();
	int direction = this->isOwned ? 1 : -1;
	this->StotpAction("Move");
	this->root->runAction(RepeatForever::create(MoveBy::create(1, Vec2(this->moveSpeed * 10 * direction, 0))))->setFlags(2);
	this->sprite->runAction(RepeatForever::create(animate))->setFlags(2);
}


void BaseUnitClass::StotpAction(string actionName) {
	if (actionName == "Attack") {
		this->root->stopActionsByFlags(1);
		this->sprite->stopActionsByFlags(1);
	}
	else if (actionName == "Move") {
		this->root->stopActionsByFlags(2);
		this->sprite->stopActionsByFlags(2);
	}
	else if (actionName == "All") {
		this->root->stopAllActions();
		this->sprite->stopAllActions();
	}
}

void BaseUnitClass::Regeneration()
{
	if (this->currentHealth < this->maxHealth && this->currentHealth > 0) {
		this->currentHealth += this->regeneration;
		this->currentHealth = currentHealth > maxHealth ? maxHealth : currentHealth;
		this->UpdateHealthBar();
	}
}

void BaseUnitClass::UpdateHealthBar()
{
	this->healthBar->runAction(ProgressTo::create(0.5, this->currentHealth * 100 / this->maxHealth));
}

DamageReceive::DamageReceive(int attackerId, float damage, float triggerTime, string animateName, string special)
{
	this->attackerId = attackerId;
	this->damage = damage;
	this->triggerTime = triggerTime;
	this->animateName = animateName;
	this->special = special;
}

void BaseUnitClass::onDamageReceive(DamageReceive dmg) {
	if (dmg.special != "") {
		this->ProcessSpecial(this->unitId, dmg);
		return;
	}

	float healthLose = dmg.damage / (0.5 + this->defense / 100);
	this->currentHealth -= healthLose;
	this->UpdateHealthBar();

	//Hiệu ứng nổ các kiểu
	if (dmg.animateName != "") {
		Sprite* sp_Animation = Sprite::create("Sprites/Blank Image.png");
		//Chỉnh màu animation
		if (this->isOwned)
			sp_Animation->setColor(IngameObject::elementColor[Tool::opponentPlayer->elementName]);
		else
			sp_Animation->setColor(IngameObject::elementColor[Tool::currentPlayer->elementName]);

		sp_Animation->setPosition(this->sprite->getBoundingBox().size / 2);
		this->sprite->addChild(sp_Animation);
		auto animate = IngameObject::animate[dmg.animateName]->clone();
		sp_Animation->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));
	}

	//Làm cái label trừ máu cho đẹp
	Label* lbl_HealthLose = Tool::CreateLabel("-" + to_string((int)healthLose), Tool::defaultTextSize*0.8, Color4B::RED);
	this->sprite->addChild(lbl_HealthLose);
	if (this->isOwned) lbl_HealthLose->setRotation3D(Vec3(0, 180, 0));
	lbl_HealthLose->setPosition(Vec2(this->sprite->getBoundingBox().size.width / 2, this->sprite->getBoundingBox().size.height));
	lbl_HealthLose->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0, 30)), RemoveSelf::create(), nullptr));

}

void BaseUnitClass::ClearStatusStat(string statusInfluence)
{
	if (statusInfluence == "Attack") this->attack = baseAttack;
	if (statusInfluence == "Defense") this->defense = baseDefense;
	if (statusInfluence == "MoveSpeed") this->moveSpeed = baseMoveSpeed;
	if (statusInfluence == "AttackSpeed") this->attackSpeed = baseAttackSpeed;
	if (statusInfluence == "Regeneration") this->regeneration = baseRegeneration;
}

StatusReceive::StatusReceive(string statusName, string statusInfluence, float value, float releaseStatusTime, int statusOrder)
{
	this->statusName = statusName;
	this->statusInfluence = statusInfluence;
	this->value = value;
	this->releaseStatusTime = releaseStatusTime;
	this->statusOrder = statusOrder;
}
void BaseUnitClass::ApplyStatus(StatusReceive stt) {
	this->statusReceive.push_back(stt);
	this->ReprocessAllStatus(stt.statusInfluence);
}

void BaseUnitClass::ReprocessAllStatus(string influence) {
	std::sort(this->statusReceive.begin(), this->statusReceive.end(), BaseUnitClass::SortStatus);
	//Clear stat affect
	this->ClearStatusStat(influence);
	//Apply lại từ đầu
	for (auto stt : this->statusReceive) {
		if (stt.statusInfluence == influence) {
			this->onStatusTrigger(this->unitId, stt);
		}
	}
}
void BaseUnitClass::onStatusTrigger(int id, StatusReceive &stt) {
	auto thisUnit = BaseUnitClass::GetUnitById(id);
	if (thisUnit == nullptr) return;

	//The Presence of Ice: Slow all enemies on the line, decrease Move Speed by 1 / 1 / 2
	//and Attack Speed by 10 / 17 / 25%
	if (stt.statusName == "The Presence of Ice - Move Speed")
		thisUnit->moveSpeed += stt.value;
	
	else if (stt.statusName == "The Presence of Ice - Attack Speed")
		thisUnit->attackSpeed *= stt.value;

	//Icy Body: Whoever attacked this bear will tremble, decrease 12% / 20% Attack for 5 seconds.
	else if (stt.statusName == "Icy Body") {
		thisUnit->attack *= stt.value;
	}
	//The Presence of Fire: burn all non-Fire-Special unit on the line, dealing 2 dps and decrease Regeneration by 20%
	else if (stt.statusName == "The Presence of Fire") {
		thisUnit->regeneration *= stt.value;
	}
	//Rotten Aura: Decrease enemies Attack and Defense by 5 / 7.5 / 10 % in 5 seconds in 500 range around.
	else if (stt.statusName == "Rotten Aura - Defense") {
		thisUnit->defense *= stt.value;
	}
	else if (stt.statusName == "Rotten Aura - Attack") {
		thisUnit->attack *= stt.value;
	}
}

void BaseUnitClass::ProcessSpecial(int id, DamageReceive &dmg) {
	auto thisUnit = BaseUnitClass::GetUnitById(id);
	if (thisUnit == nullptr) return;

	//Frost Nova: Launch a snowball toward enemy, dealing 75 / 100 / 150 splash damage in 100 range,
	//pierce 25 Defense (Cooldown 7 / 6 / 4 seconds)
	if (dmg.special == "Frost Nova") {
		auto currentDefense = thisUnit->defense;
		thisUnit->defense -= 25;
		dmg.special = "";
		thisUnit->onDamageReceive(dmg);
		thisUnit->defense = currentDefense;
		return;
	}
	
}

BaseUnitClass::BaseUnitClass()
{
}

BaseUnitClass::~BaseUnitClass()
{
}

HardEffect::HardEffect(string effectName, float triggerTime, float releaseTime)
{
	this->effectName = effectName;
	this->triggerTime = triggerTime;
	this->releaseTime = releaseTime;
}
