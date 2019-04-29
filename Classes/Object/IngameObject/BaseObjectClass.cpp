#include "BaseObjectClass.h"
using namespace std;


vector<BaseObjectClass*> BaseObjectClass::player1_Object;
vector<BaseObjectClass*> BaseObjectClass::player2_Object;

void BaseObjectClass::UpdateIngameInfo(string spriteName, bool isStand)
{
	root = Node::create();
	sprite = Sprite::create(spriteName);
	this->CreateHealthBar();
	root->addChild(sprite, 1);
	root->addChild(healthBar, 1);
	isAlive = true;
	this->isStand = isStand; // Object ko có quyền di chuyển
	this->line = line;
	action = "Idle";
	string spawnPosition = this->isLeft ? "1_" : "2_";
	spawnPosition += to_string(line);
	root->setPosition(IngameObject::spawnPoint[spawnPosition]);
	if (this->isLeft) {
		root->setRotation3D(Vec3(0, 180, 0));
		this->healthBar->setMidpoint(Vec2(1, 0));
	}
}
//Action flags: move = 1, attack = 2, die = 3
void BaseObjectClass::UpdateAction(vector<BaseObjectClass*>& vec)
{
	//Nếu nó chết rồi thì hủy
	if (!this->isAlive) {
		delete this;
		goto End;
	}

	//Kiểm tra trạng thái
	if (this->statusReceive.size() > 0) this->CheckStatusEnd();

	//Hồi máu
	if (nextRegeneration < Tool::currentIngameTime) {
		Regeneration();
		nextRegeneration++;
	}

	//Update damage nhận vào
	if (this->damageReceive.size() > 0) {
		for (int i = 0; i < damageReceive.size(); i++) {
			if (damageReceive[i].triggerTime < Tool::currentIngameTime) {
				this->ExcuteDamageReceive(damageReceive[i]);
				damageReceive.erase(damageReceive.begin() + i);
				this->UpdateHealthBar();
			}
		}
	}
	
	//Action die
	if (this->currentHealth <= 0 && (this->action == "Idle" || this->action == "Move")) {
		this->StopMove();
		this->Die();
		goto End;
	}

	//Action attack
	if (this->action == "Move" || this->action == "Idle") {
		vector<BaseObjectClass*> targetList = this->FindTargets(vec);
		if (targetList.size() > 0) {
			this->StopMove();
			for (auto target : targetList) {
				this->Attack(target);
			}
			goto End;
		}
	}

	//Action Move
	if(this->action == "Idle" && !this->isStand) this->Move();
End:;
}

void BaseObjectClass::Die() {
	this->root->stopAllActions();
	this->sprite->stopAllActions();
	this->action = "Die";
	auto animate = IngameObject::animate[this->animateName + "_die"]->clone();
	animate->setDuration(1);
	
	this->sprite->runAction(Sequence::create(
		animate,
		RemoveSelf::create(),
		CallFunc::create([&]() {	this->root->runAction(RemoveSelf::create());
			this->healthBar->runAction(RemoveSelf::create());
			this->isAlive = false;
			this->action = "Idle"; }),
		nullptr
	))->setFlags(3);
}


void BaseObjectClass::Move()
{
	this->action = "Move";
	auto animate = IngameObject::animate[this->animateName + "_run"]->clone();
	int direction = this->isLeft ? 1 : -1;
	this->StopMove();
	this->root->runAction(RepeatForever::create(MoveBy::create(1, Vec2(this->speed * 10 * direction, 0))))->setFlags(1);
	this->sprite->runAction(RepeatForever::create(animate))->setFlags(1);
}

void BaseObjectClass::StopMove() {
	this->root->stopActionsByFlags(1);
	this->sprite->stopActionsByFlags(1);
}

void BaseObjectClass::Attack(BaseObjectClass *& target)
{
	this->action = "Attack";
	auto animate = IngameObject::animate[this->animateName + "_attack"]->clone();
	animate->setDuration(this->attackRate);
	this->sprite->runAction(Sequence::create(
		animate,
		CallFunc::create([&]() {	this->action = "Idle"; }),
		nullptr
	))->setFlags(2);
	float healthLose = ((float)this->attack / (0.5 + target->defense / 100.0)); // defense >= 0
	//string animateName = this->animateName + "_explosion";
	string animateName = "_explosion"; // Không có sprite nên ai bắn cũng nổ như nhau
	float triggerTime = Tool::currentIngameTime + this->attackRate / 2;
	target->damageReceive.push_back(DamageReceive(healthLose, triggerTime, animateName, this->id));
}

void BaseObjectClass::Regeneration()
{
	if (this->regeneration != 0 && this->currentHealth < this->maxHealth && this->currentHealth > 0) {
		this->currentHealth += this->regeneration;
		this->currentHealth = currentHealth > maxHealth ? maxHealth : currentHealth;
		auto lbl_HealthRecover = Tool::CreateLabel("+" + to_string(this->regeneration), Tool::defaultTextSize, Color4B::GREEN);
		lbl_HealthRecover->setPosition(Vec2(this->sprite->getBoundingBox().size.width / 2, this->sprite->getBoundingBox().size.height));
		lbl_HealthRecover->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0, 40)), RemoveSelf::create(), nullptr));
		if (this->isLeft) lbl_HealthRecover->setRotation3D(Vec3(0, 180, 0));
		this->sprite->addChild(lbl_HealthRecover);
	}
}

void BaseObjectClass::ExcuteDamageReceive(DamageReceive dmg) {
	
	this->currentHealth -= dmg.healthLose;
	if (this->currentHealth > this->maxHealth) this->currentHealth = this->maxHealth;
	Label* lbl_HealthLose;
	if (dmg.healthLose > 0)
		lbl_HealthLose = Tool::CreateLabel("-" + to_string(dmg.healthLose), Tool::defaultTextSize, Color4B::RED);
	else
		lbl_HealthLose = Tool::CreateLabel("+" + to_string(dmg.healthLose*-1), Tool::defaultTextSize, Color4B::GREEN);
	this->sprite->addChild(lbl_HealthLose);
	if (this->isLeft) lbl_HealthLose->setRotation3D(Vec3(0, 180, 0));
	lbl_HealthLose->setPosition(Vec2(this->sprite->getBoundingBox().size.width / 2, this->sprite->getBoundingBox().size.height));
	lbl_HealthLose->runAction(Sequence::create(MoveBy::create(0.7, Vec2(0, 40)), RemoveSelf::create(), nullptr));

	if (dmg.animateName != "") {
		Sprite* sp_Animation = Sprite::create("Sprites/BlankImage.png");
		
		//Chỉnh màu animation theo hệ của đối phương
		if (this->isLeft) {
			if (Tool::opponentPlayer->elementName != "")
				sp_Animation->setColor(IngameObject::elementColor[Tool::opponentPlayer->elementName]);
		}
		else if (Tool::currentPlayer->elementName != "")
			sp_Animation->setColor(IngameObject::elementColor[Tool::currentPlayer->elementName]);

		//Tool::setNodeSize(sp_Animation, this->sprite->getBoundingBox().size.width, this->sprite->getBoundingBox().size.height);
		sp_Animation->setPosition(this->sprite->getBoundingBox().size / 2);
		this->sprite->addChild(sp_Animation);
		auto animate = IngameObject::animate[dmg.animateName]->clone();
		animate->setDuration(1);
		sp_Animation->runAction(Sequence::create(animate, RemoveSelf::create(), nullptr));
	}
}


void BaseObjectClass::UpdateHealthBar()
{
	this->healthBar->runAction(ProgressTo::create(0.5, this->currentHealth * 100 / this->maxHealth));
}

void BaseObjectClass::CreateHealthBar()
{
	this->healthBar = ProgressTimer::create(Sprite::create("healthBar.png"));
	this->healthBar->setType(ProgressTimer::Type::BAR);
	this->healthBar->setBarChangeRate(Vec2(1, 0));
	this->healthBar->setMidpoint(Vec2(0, 0));
	this->healthBar->setPercentage(100);
	this->healthBar->setPosition(this->sprite->getPosition() + Vec2(0, this->sprite->getBoundingBox().size.height*0.5 + 10));
	if (this->isLeft) this->healthBar->setColor(Color3B::GREEN);
	else  this->healthBar->setColor(Color3B::RED);
	Tool::setNodeSize(this->healthBar, this->sprite->getBoundingBox().size.width*0.35, 8);
}


bool BaseObjectClass::SortByHealth(BaseObjectClass* object1, BaseObjectClass* object2) {
	return (object1->currentHealth < object2->currentHealth);
}


vector<BaseObjectClass*> BaseObjectClass::FindTargets(vector<BaseObjectClass*>& targets) {
	vector<BaseObjectClass*> result;
	vector<BaseObjectClass*> shotableTargets;

	//Tìm danh sách địch có thể bắn tới
	for (auto target : targets) {
		//Xem target còn sống không
		if (target->currentHealth > 0 && target->action != "Die") {
			//Tìm xem có cùng hàng không || là maintower
			if (this->line == target->line || target->description == "Main tower") {
				//Nếu cùng hàng thì tim xem có trong range không
				if (abs(target->root->getPositionX() - this->root->getPositionX()) < this->range) {
					shotableTargets.push_back(target);
				}
			}
		}
	}
	//Sắp xếp theo máu tăng dần
	sort(shotableTargets.begin(), shotableTargets.end(), BaseObjectClass::SortByHealth);

	//Lấy 1 thằng máu thấp nhất
	if(shotableTargets.size() > 0) result.push_back(shotableTargets[0]);
	return result;

}

void BaseObjectClass::CheckStatusEnd()
{
	for (int i = 0; i < statusReceive.size(); i++) {
		if (statusReceive[i].endTime < Tool::currentIngameTime) {
			this->RemoveStatus(statusReceive[i].statusName);
			statusReceive.erase(statusReceive.begin() + i);
		}
	}
	
}
void BaseObjectClass::RemoveStatus(string statusName) {
	if (statusName == "CursedAura") {
		//Cursed Kingdom: Whoever entered this tower range will be rotted, decrease 25% Attack.
		this->attack /= 0.75; return;
	}
	if (statusName == "FrozenAura") {
		//Frozen Aura: Whoever entered this tower range will be cold, decrease Attack Rate by 25%
		this->attackRate *= 0.75; return;
	}
}



BaseObjectClass::BaseObjectClass()
{
}

BaseObjectClass::~BaseObjectClass()
{
}

BaseObjectClass::DamageReceive::DamageReceive(int healthLose, float triggerTime, string animateName, int sourceId)
{
	this->healthLose = healthLose;
	this->triggerTime = triggerTime;
	this->animateName = animateName;
	this->sourceId = sourceId;
}

BaseObjectClass::StatusReceive::StatusReceive(int sourceId, string statusName, float endTime)
{
	this->sourceId = sourceId;
	this->statusName = statusName;
	this->endTime = endTime;
}

BaseObjectClass* BaseObjectClass::GetObjectById(int id)
{
	for (auto object : BaseObjectClass::player1_Object) {
		if (object->id == id) return object;
	}
	for (auto object : BaseObjectClass::player2_Object) {
		if (object->id == id) return object;
	}
	return nullptr;
}