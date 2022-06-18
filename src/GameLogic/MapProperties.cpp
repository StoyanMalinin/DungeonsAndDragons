#include "MapProperties.h"

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
