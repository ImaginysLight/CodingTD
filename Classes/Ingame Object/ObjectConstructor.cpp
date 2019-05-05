#include "ObjectConstructor.h"

BaseUnitClass * ObjectConstructor::InitializeObject(string objectName, int line, bool isOwned, int playerId)
{
	if (objectName == "Frost Wyvern") return new FrostWyvern(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Polar Bear") return new PolarBear(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Volcarona") return new Volcarona(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Enraged Ursa") return new EnragedUrsa(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Hotheaded Gunner") return new HotheadedGunner(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Crazy Wolf") return new CrazyWolf(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Helicopter") return new Helicopter(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "Dead Walker") return new DeadWalker(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
	if (objectName == "UFO Driver") return new UFODriver(line, isOwned, ++BaseUnitClass::Unit_Id_Counter, playerId);
}
