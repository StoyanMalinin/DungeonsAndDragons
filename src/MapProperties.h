#ifndef __MAPPROPERTIES_H
#define __MAPPROPERTIES_H

struct MapProperties
{
	size_t n, m;
	size_t dragonsCount, treasuresCount;
	float dragonStrength, dragonMana, dragonHealth;
	float treasureArmor, treasureWeapon, treasureSpell;

	MapProperties::MapProperties(size_t n, size_t m,
		size_t dragonsCount, size_t treasuresCount,
		float dragonStrength, float dragonMana, float dragonHealth,
		float treasureArmor, float treasureWeapon, float treasureSpell);
};

#endif // !__MAPPROPERTIES_H
