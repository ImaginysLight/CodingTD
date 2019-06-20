#include "IngameObject.h"

unordered_map<string, Color3B> IngameObject::elementColor;
unordered_map<string, Vec2> IngameObject::spawnPoint;
unordered_map<string, Animate*> IngameObject::animate;


void IngameObject::loadIngameObjectStaticVariables() {
	IngameObject::elementColor.insert({ "Ice",Color3B(100,200,250) });
	IngameObject::elementColor.insert({ "Fire",Color3B(200,0,0) });
	IngameObject::elementColor.insert({ "Nature",Color3B(0,200,100) });

	//Map dài 3000, mỗi 1 speed là 10pixel / s => trung bình = 10 speed cần 30s để đi tới nhà team kia
	IngameObject::spawnPoint.insert({ "1_1",Vec2(50,115) });
	IngameObject::spawnPoint.insert({ "1_2",Vec2(50,260) });
	IngameObject::spawnPoint.insert({ "1_3",Vec2(50,403) });

	IngameObject::spawnPoint.insert({ "2_1",Vec2(3050,115) });
	IngameObject::spawnPoint.insert({ "2_2",Vec2(3050,260) });
	IngameObject::spawnPoint.insert({ "2_3",Vec2(3050,403) });

}

void IngameObject::loadAnimate() {
	IngameObject::animate.insert(CreateAnimateWithKey("", "explosion", 1, 20));

	IngameObject::animate.insert(CreateAnimateWithKey("Crazy Wolf", "attack", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("Crazy Wolf", "die", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("Crazy Wolf", "move", 1, 16));
	
	IngameObject::animate.insert(CreateAnimateWithKey("Dead Walker", "attack", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("Dead Walker", "die", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Dead Walker", "move", 1, 24));

	IngameObject::animate.insert(CreateAnimateWithKey("Elemental Alien", "attack", 1, 20));
	IngameObject::animate.insert(CreateAnimateWithKey("Elemental Alien", "die", 1, 21));
	IngameObject::animate.insert(CreateAnimateWithKey("Elemental Alien", "move", 1, 49));

	IngameObject::animate.insert(CreateAnimateWithKey("Enraged Ursa", "attack", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Enraged Ursa", "die", 1, 18));
	IngameObject::animate.insert(CreateAnimateWithKey("Enraged Ursa", "move", 1, 32));

	IngameObject::animate.insert(CreateAnimateWithKey("Frost Wyvern", "attack", 1, 20));
	IngameObject::animate.insert(CreateAnimateWithKey("Frost Wyvern", "die", 1, 22));
	IngameObject::animate.insert(CreateAnimateWithKey("Frost Wyvern", "move", 1, 24));

	IngameObject::animate.insert(CreateAnimateWithKey("Helicopter", "attack", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Helicopter", "die", 1, 19));
	IngameObject::animate.insert(CreateAnimateWithKey("Helicopter", "move", 1, 17));

	IngameObject::animate.insert(CreateAnimateWithKey("Hotheaded Gunner", "attack", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("Hotheaded Gunner", "die", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Hotheaded Gunner", "move", 1, 16));

	IngameObject::animate.insert(CreateAnimateWithKey("Liquid Assassin", "attack", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Liquid Assassin", "die", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Liquid Assassin", "move", 1, 18));
	 
	IngameObject::animate.insert(CreateAnimateWithKey("Poisonous Butterfly", "attack", 1, 22));
	IngameObject::animate.insert(CreateAnimateWithKey("Poisonous Butterfly", "die", 1, 22));
	IngameObject::animate.insert(CreateAnimateWithKey("Poisonous Butterfly", "move", 1, 14));

	IngameObject::animate.insert(CreateAnimateWithKey("Polar Bear", "attack", 1, 18));
	IngameObject::animate.insert(CreateAnimateWithKey("Polar Bear", "die", 1, 24));
	IngameObject::animate.insert(CreateAnimateWithKey("Polar Bear", "move", 1, 16));

	IngameObject::animate.insert(CreateAnimateWithKey("UFO Driver", "attack", 1, 11));
	IngameObject::animate.insert(CreateAnimateWithKey("UFO Driver", "die", 1, 17));
	IngameObject::animate.insert(CreateAnimateWithKey("UFO Driver", "move", 1, 14));

	IngameObject::animate.insert(CreateAnimateWithKey("Vampire Dragon", "attack", 1, 18));
	IngameObject::animate.insert(CreateAnimateWithKey("Vampire Dragon", "die", 1, 22));
	IngameObject::animate.insert(CreateAnimateWithKey("Vampire Dragon", "move", 1, 24));

	IngameObject::animate.insert(CreateAnimateWithKey("Volcarona", "attack", 1, 9));
	IngameObject::animate.insert(CreateAnimateWithKey("Volcarona", "die", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Volcarona", "move", 1, 7));

	IngameObject::animate.insert(CreateAnimateWithKey("Winged Orc", "attack", 1, 13));
	IngameObject::animate.insert(CreateAnimateWithKey("Winged Orc", "die", 1, 15));
	IngameObject::animate.insert(CreateAnimateWithKey("Winged Orc", "move", 1, 9));

	IngameObject::animate.insert(CreateAnimateWithKey("Healing", "healing", 1, 20));
	IngameObject::animate.insert(CreateAnimateWithKey("Ice Age", "ice", 1, 10));
	IngameObject::animate.insert(CreateAnimateWithKey("Hell Fire", "fire", 1, 7));
	IngameObject::animate.insert(CreateAnimateWithKey("Heaven Bless", "heal", 1, 15));

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

string IngameObject::GetKingdomByElement(string element)
{
	if (element == "Fire") return "Flamed Kingdom";
	if (element == "Ice") return "Frozen Kingdom";
	if (element == "Nature") return "Blessed Kingdom";
}

int IngameObject::GetNumOfLevel(string name)
{
	if (name == "Frost Wyvern") return 3;
	if (name == "Polar Bear") return 3;
	if (name == "Volcarona") return 2;
	if (name == "Enraged Ursa") return 2;
	if (name == "Poisonous Butterfly") return 2;
	if (name == "Vampire Dragon") return 2;
	if (name == "Hotheaded Gunner") return 3;
	if (name == "UFO Driver") return 4;
	if (name == "Winged Orc") return 3;
	if (name == "Helicopter") return 2;
	if (name == "Crazy Wolf") return 3;
	if (name == "Dead Walker") return 3;
	if (name == "Liquid Assassin") return 3;
	if (name == "Elemental Alien") return 4;
}

