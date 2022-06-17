#include "Weapon.h"

Weapon::Weapon(const String& name, size_t level, float c) : GameItem(name, level), c(c)
{}

Weapon::Weapon(std::iostream & stream) : GameItem(stream)
{
	stream >> c;
	checkForError(stream);
}

float Weapon::getC() const
{
	return c;
}

void Weapon::write(std::ostream& os) const
{
	GameItem::write(os);
	os << "|strength: " << c << '\n';
}

void Weapon::serialize(std::ostream& stream) const
{
	GameItem::serialize(stream);
	stream << " " << c;
}
