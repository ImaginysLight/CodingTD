#include"BaseObjectCLass.h"


#include"MainTower/CursedKingdom.h"
#include"MainTower/FlamedKingdom.h"
#include"MainTower/FrozenKingdom.h"
#include"MainTower/RottedKingdom.h"

#include"Robot/Robot2.h"
#include"Robot/Robot5.h"
#include"Robot/Robot7.h"
#include"Robot/Robot10.h"
#include"Robot/Robot12.h"

#include"Robot/Robot2_2.h"
#include"Robot/Robot5_2.h"
#include"Robot/Robot7_2.h"
#include"Robot/Robot10_2.h"

#include"Robot/Robot2_3.h"
#include"Robot/Robot5_3.h"

class ObjectConstructor {
public:
	static BaseObjectClass* InitializeObject(string objectName, int line, bool isLeft, int id);
	
};

