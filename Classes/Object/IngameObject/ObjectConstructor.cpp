#include "ObjectConstructor.h"

BaseObjectClass * ObjectConstructor::InitializeObject(string objectName, int line, bool isLeft, int id)
{
	//Main tower
	if (objectName == "CursedKingdom") return new CursedKingdom(isLeft, id);
	if (objectName == "FlamedKingdom") return new FlamedKingdom(isLeft, id);
	if (objectName == "FrozenKingdom") return new FrozenKingdom(isLeft, id);
	if (objectName == "RottedKingdom") return new RottedKingdom(isLeft, id);

	//Robot
	if (objectName == "Robot2") return new Robot2(line, isLeft, id);
	if (objectName == "Robot5") return new Robot5(line, isLeft, id);
	if (objectName == "Robot7") return new Robot7(line, isLeft, id);
	if (objectName == "Robot10") return new Robot10(line, isLeft, id);
	if (objectName == "Robot12") return new Robot12(line, isLeft, id);

	if (objectName == "Robot2_2") return new Robot2_2(line, isLeft, id);
	if (objectName == "Robot5_2") return new Robot5_2(line, isLeft, id);
	if (objectName == "Robot7_2") return new Robot7_2(line, isLeft, id);
	if (objectName == "Robot10_2") return new Robot10_2(line, isLeft, id);

	if (objectName == "Robot2_3") return new Robot2_3(line, isLeft, id);
	if (objectName == "Robot5_3") return new Robot5_3(line, isLeft, id);

}


