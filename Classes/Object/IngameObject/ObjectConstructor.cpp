#include "ObjectConstructor.h"

BaseObjectClass * ObjectConstructor::InitializeObject(string objectName, int line, bool isLeft)
{
	if (objectName == "MainTower1") return new MainTower1(isLeft);
	if (objectName == "MainTower2") return new MainTower2(isLeft);
	if (objectName == "Robot2") return new Robot2(line, isLeft);
	if (objectName == "Robot5") return new Robot5(line, isLeft);
	if (objectName == "Robot7") return new Robot7(line, isLeft);
	if (objectName == "Robot10") return new Robot10(line, isLeft);
	if (objectName == "Robot12") return new Robot12(line, isLeft);

	//if (objectName == "MainTower1") return new MainTower1(isLeft);
	//if (objectName == "MainTower2") return new MainTower2(isLeft);
	if (objectName == "Robot2_2") return new Robot2_2(line, isLeft);
	if (objectName == "Robot5_2") return new Robot5_2(line, isLeft);
	if (objectName == "Robot7_2") return new Robot7_2(line, isLeft);
	if (objectName == "Robot10_2") return new Robot10_2(line, isLeft);

	if (objectName == "Robot2_3") return new Robot2_3(line, isLeft);
	if (objectName == "Robot5_3") return new Robot5_3(line, isLeft);
}
