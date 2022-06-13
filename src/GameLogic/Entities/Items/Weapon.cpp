#include "Weapon.h"

Weapon::Weapon(const String& name, size_t level, float c) : GameItem(name, level), c(c)
{}

float Weapon::getC() const
{
	return c;
}
