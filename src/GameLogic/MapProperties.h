#ifndef __MAPPROPERTIES_H
#define __MAPPROPERTIES_H

#include <iostream>

struct MapProperties
{
	size_t n, m;
	size_t dragonsCount, treasuresCount;
	float dragonStrength, dragonMana, dragonHealth;
	float treasureArmor, treasureWeapon, treasureSpell;
	size_t itemLevel;

	MapProperties(size_t n, size_t m,
		          size_t dragonsCount, size_t treasuresCount,
		          float dragonStrength, float dragonMana, float dragonHealth,
		          float treasureArmor, float treasureWeapon, float treasureSpell,
		          size_t itemLevel);
	MapProperties(std::iostream& stream);
	MapProperties() = default;

	void serialize(std::ostream &stream) const;
	void serializeLn(std::ostream& stream) const;

	bool checkValid() const;
};

bool operator ==(const MapProperties& lhs, const MapProperties& rhs);

#endif // !__MAPPROPERTIES_H
