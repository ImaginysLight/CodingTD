#include "IngameObject.h"

unordered_map<string, Color3B> IngameObject::elementColor;
unordered_map<string, Vec2> IngameObject::spawnPoint;
unordered_map<string, Animate*> IngameObject::animate;


void IngameObject::loadIngameObjectStaticVariables() {
	IngameObject::elementColor.insert({ "Ice",Color3B(0,255,255) });
	IngameObject::elementColor.insert({ "Fire",Color3B(255,0,0) });
	IngameObject::elementColor.insert({ "Poison",Color3B(100,240,70) });
	IngameObject::elementColor.insert({ "Dark",Color3B(60,0,60) });

	IngameObject::spawnPoint.insert({ "1_1",Vec2(1000,50) }); // team1 _ line1
	IngameObject::spawnPoint.insert({ "1_2",Vec2(200,100) });
	IngameObject::spawnPoint.insert({ "1_3",Vec2(200,150) });

	IngameObject::spawnPoint.insert({ "2_1",Vec2(2000,50) });
	IngameObject::spawnPoint.insert({ "2_2",Vec2(2000,100) });
	IngameObject::spawnPoint.insert({ "2_3",Vec2(2000,150) });

}

void IngameObject::loadAnimate() {
	IngameObject::animate.insert(CreateAnimateWithKey("", "explosion", 1, 20));

	IngameObject::animate.insert(CreateAnimateWithKey("MainTower1", "die", 1, 9));
	IngameObject::animate.insert(CreateAnimateWithKey("MainTower1", "attack", 1, 11));

	IngameObject::animate.insert(CreateAnimateWithKey("MainTower2", "die", 1, 9));
	IngameObject::animate.insert(CreateAnimateWithKey("MainTower2", "attack", 1, 11));

	IngameObject::animate.insert(CreateAnimateWithKey("Robot2", "run", 1, 8));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot2", "die", 1, 9));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot2", "attack", 1, 11));


	IngameObject::animate.insert(CreateAnimateWithKey("Robot5", "run", 1, 16));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot5", "die", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot5", "attack", 1, 10));

	IngameObject::animate.insert(CreateAnimateWithKey("Robot7", "run", 1, 8));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot7", "die", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot7", "attack", 1, 11));

	IngameObject::animate.insert(CreateAnimateWithKey("Robot10", "run", 1, 8));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot10", "die", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot10", "attack", 1, 11));

	IngameObject::animate.insert(CreateAnimateWithKey("Robot12", "run", 1, 8));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot12", "die", 1, 10));
	IngameObject::animate.insert(CreateAnimateWithKey("Robot12", "attack", 1, 11));


}

Animate* IngameObject::CreateAnimate(string prefix, string suffix, int numBegin, int numEnd, float delay) {
	auto animation = Animation::create();
	for (int i = numBegin; i <= numEnd; i++)
	{
		string name = prefix + to_string(i) + suffix;
		animation->addSpriteFrameWithFileName(name);
	}
	animation->setDelayPerUnit(delay);
	auto animate = Animate::create(animation);
	animate->retain();
	return animate;
}

pair<string, Animate*> IngameObject::CreateAnimateWithKey(string characterName, string action, int numBegin, int numEnd) {
	pair<string, Animate*> result;
	result.first = characterName + "_" + action;
	result.second = IngameObject::CreateAnimate("Sprites/" + characterName + "/" + action + "/" + action + " (", ").png", numBegin, numEnd, 0.1f);
	return result;
}


