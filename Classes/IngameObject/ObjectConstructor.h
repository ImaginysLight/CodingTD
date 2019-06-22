#pragma once
#include"Unit/BaseUnitClass.h"

#include"Unit/FrozenKingdom.h"
#include"Unit/FlamedKingdom.h"
#include"Unit/BlessedKingdom.h"

#include"Unit/FrostWyvern_1.h"
#include"Unit/FrostWyvern_2.h"
#include"Unit/FrostWyvern_3.h"

#include"Unit/PolarBear_1.h"
#include"Unit/PolarBear_2.h"
#include"Unit/PolarBear_3.h"

#include"Unit/Volcarona_1.h"
#include"Unit/Volcarona_2.h"

#include"Unit/EnragedUrsa_1.h"
#include"Unit/EnragedUrsa_2.h"

#include"Unit/PoisonousButterfly_1.h"
#include"Unit/PoisonousButterfly_2.h"

#include"Unit/VampireDragon_1.h"
#include"Unit/VampireDragon_2.h"

#include"Unit/HotheadedGunner_1.h"
#include"Unit/HotheadedGunner_2.h"
#include"Unit/HotheadedGunner_3.h"

#include"Unit/CrazyWolf_1.h"
#include"Unit/CrazyWolf_2.h"
#include"Unit/CrazyWolf_3.h"

#include"Unit/Helicopter_1.h"
#include"Unit/Helicopter_2.h"

#include"Unit/DeadWalker_1.h"
#include"Unit/DeadWalker_2.h"
#include"Unit/DeadWalker_3.h"


#include"Unit/UFODriver_1.h"
#include"Unit/UFODriver_2.h"
#include"Unit/UFODriver_3.h"
#include"Unit/UFODriver_4.h"

#include"Unit/WingedOrc_1.h"
#include"Unit/WingedOrc_2.h"
#include"Unit/WingedOrc_3.h"

#include"Unit/LiquidAssassin_1.h"
#include"Unit/LiquidAssassin_2.h"
#include"Unit/LiquidAssassin_3.h"

#include"Unit/ElementalAlien_1.h"
#include"Unit/ElementalAlien_2.h"
#include"Unit/ElementalAlien_3.h"
#include"Unit/ElementalAlien_4.h" 

class ObjectConstructor {
public:
	static BaseUnitClass* InitializeObject(string objectName, int line, bool isOwned, int playerId, int unitId);
	static ui::ScrollView* GetSpecificUnitDetails(string unitName, Size visibleSize);
};

