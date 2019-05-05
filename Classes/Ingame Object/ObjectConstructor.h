#include"Unit/BaseUnitClass.h"
#include"Unit/FrostWyvern.h"
#include"Unit/PolarBear.h"
#include"Unit/Volcarona.h"
#include"Unit/EnragedUrsa.h"
//Nature
//Nature
#include"Unit/HotheadedGunner.h"
#include"Unit/CrazyWolf.h"
#include"Unit/Helicopter.h"
#include"Unit/DeadWalker.h"
#include"Unit/UFODriver.h"


class ObjectConstructor {
public:
	static BaseUnitClass* InitializeObject(string objectName, int line, bool isOwned, int playerId);
	
};

