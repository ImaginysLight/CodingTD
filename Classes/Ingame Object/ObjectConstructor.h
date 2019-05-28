#include"Unit/BaseUnitClass.h"

#include"Unit/FrozenKingdom.h"
//#include"Unit/FrozenKingdom_2.h"
//#include"Unit/FrozenKingdom_3.h"

#include"Unit/FlamedKingdom.h"
//#include"Unit/FlamedKingdom_2.h"
//#include"Unit/FlamedKingdom_3.h"

#include"Unit/BlessedKingdom.h"
//#include"Unit/BlessedKingdom_2.h"
//#include"Unit/BlessedKingdom_3.h"

#include"Unit/FrostWyvern.h"
#include"Unit/FrostWyvern_2.h"
#include"Unit/FrostWyvern_3.h"

#include"Unit/PolarBear.h"
#include"Unit/PolarBear_2.h"
#include"Unit/PolarBear_3.h"

#include"Unit/Volcarona.h"
#include"Unit/Volcarona_2.h"

#include"Unit/EnragedUrsa.h"
#include"Unit/EnragedUrsa_2.h"

#include"Unit/PoisonousButterfly.h"
#include"Unit/PoisonousButterfly_2.h"

#include"Unit/VampireDragon.h"
#include"Unit/VampireDragon_2.h"

#include"Unit/HotheadedGunner.h"
#include"Unit/HotheadedGunner_2.h"
#include"Unit/HotheadedGunner_3.h"

#include"Unit/CrazyWolf.h"
#include"Unit/CrazyWolf_2.h"
#include"Unit/CrazyWolf_3.h"

#include"Unit/Helicopter.h"
#include"Unit/Helicopter_2.h"

#include"Unit/DeadWalker.h"
#include"Unit/DeadWalker_2.h"
#include"Unit/DeadWalker_3.h"


#include"Unit/UFODriver.h"
#include"Unit/UFODriver_2.h"
#include"Unit/UFODriver_3.h"
#include"Unit/UFODriver_4.h"

#include"Unit/WingedOrc.h"
#include"Unit/WingedOrc_2.h"
#include"Unit/WingedOrc_3.h"

#include"Unit/LiquidAssassin.h"
#include"Unit/LiquidAssassin_2.h"
#include"Unit/LiquidAssassin_3.h"

#include"Unit/ElementalAlien.h"
#include"Unit/ElementalAlien_2.h"
#include"Unit/ElementalAlien_3.h"
#include"Unit/ElementalAlien_4.h" 

class ObjectConstructor {
public:
	static BaseUnitClass* InitializeObject(string objectName, int line, bool isOwned, int playerId, int unitId);
	static ui::ScrollView* GetSpecificUnitDetails(string unitName, Size visibleSize);
};

