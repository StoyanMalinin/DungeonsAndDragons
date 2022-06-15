#include "Armor.h"

Armor::Armor(const String& name, size_t level, float c) : GameItem(name, level), c(c)
{}

float Armor::getC() const
{
	return c;
}

void Armor::write(std::ostream& os) const
{
	GameItem::write(os);
	os << "|protection: " << c;
}
