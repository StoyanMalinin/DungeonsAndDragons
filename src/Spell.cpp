#include "Spell.h"

Spell::Spell(const String& name, size_t level, float c) : GameItem(name, level), c(c)
{}

float Spell::getC() const
{
	return c;
}
