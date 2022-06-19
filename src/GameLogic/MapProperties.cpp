#include "MapProperties.h"

#include <cmath>

MapProperties::MapProperties(size_t n, size_t m,
	                         size_t dragonsCount, size_t treasuresCount,
	                         float dragonStrength, float dragonMana, float dragonHealth,
	                         float treasureArmor, float treasureWeapon, float treasureSpell,
							 size_t itemLevel)
	                         :
							 n(n), m(m),
							 dragonsCount(dragonsCount), treasuresCount(treasuresCount),
	                         dragonStrength(dragonStrength), dragonMana(dragonMana), dragonHealth(dragonHealth),
	                         treasureArmor(treasureArmor), treasureWeapon(treasureWeapon), treasureSpell(treasureSpell),
							 itemLevel(itemLevel)
{}

MapProperties::MapProperties(std::iostream & stream)
{
	if (stream.bad() == true)
		throw std::logic_error("Error while deserializing MapProoerties object, the stream is corrupt or in invalid format!");

	stream >> n >> m;
	stream >> dragonsCount >> treasuresCount;
	stream >> dragonStrength >> dragonMana >> dragonHealth;
	stream >> treasureArmor >> treasureWeapon >> treasureSpell;
	stream >> itemLevel;

	if (stream.bad() == true)
		throw std::logic_error("Error while deserializing MapProoerties object, the stream is corrupt or in invalid format!");

}

void MapProperties::serialize(std::ostream & stream) const
{
	stream << n << " " << m << " " << dragonsCount << " " << treasuresCount << " "
		   << dragonStrength << " " << dragonMana << " " << dragonHealth << " "
		   << treasureArmor << " " << treasureWeapon << " " << treasureSpell << " "
		   << itemLevel;
}

void MapProperties::serializeLn(std::ostream& stream) const
{
	serialize(stream);
	stream << '\n';
}

bool MapProperties::checkValid() const
{
	const float eps = 0.001f;

	if (dragonStrength < -eps || dragonMana < -eps || dragonHealth < -eps) return false;
	if (treasureArmor < -eps || treasureSpell < -eps || treasureWeapon < -eps) return false;
	if (n > 1e6) return false;
	if (m > 1e6) return false;
	if (n * m > 1e7) return false;
	if (itemLevel > 1e4) return false;

	return true;
}

bool operator==(const MapProperties& lhs, const MapProperties& rhs)
{
	const float eps = 0.001f;

	if (lhs.n != rhs.n) return false;
	if (lhs.m != rhs.m) return false;
	if (lhs.dragonsCount != rhs.dragonsCount) return false;
	if (lhs.treasuresCount != rhs.treasuresCount) return false;
	if (fabs(lhs.dragonStrength - rhs.dragonStrength) > eps) return false;
	if (fabs(lhs.dragonMana - rhs.dragonMana) > eps) return false;
	if (fabs(lhs.dragonHealth - rhs.dragonHealth) > eps) return false;
	if (fabs(lhs.treasureArmor - rhs.treasureArmor) > eps) return false;
	if (fabs(lhs.treasureWeapon - rhs.treasureWeapon) > eps) return false;
	if (fabs(lhs.treasureSpell - rhs.treasureSpell) > eps) return false;
	if (lhs.itemLevel != rhs.itemLevel) return false;

	return true;
}
