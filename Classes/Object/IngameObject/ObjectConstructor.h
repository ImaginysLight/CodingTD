#include"BaseObjectCLass.h"
#include"MainTower1.h"
#include"MainTower2.h"
#include"Robot2.h"
#include"Robot5.h"
#include"Robot7.h"
#include"Robot10.h"
#include"Robot12.h"

#include"Robot2_2.h"
#include"Robot5_2.h"
#include"Robot7_2.h"
#include"Robot10_2.h"

#include"Robot2_3.h"
#include"Robot5_3.h"

class ObjectConstructor {
public:
	static BaseObjectClass* InitializeObject(string objectName, int line, bool isLeft);
};

