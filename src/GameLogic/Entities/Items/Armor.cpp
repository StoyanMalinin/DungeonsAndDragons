#include "Armor.h"

Armor::Armor(const String& name, size_t level, float c) : GameItem(name, level), c(c)
{}

Armor::Armor(std::iostream & stream) : GameItem(stream)
{
	stream >> c;
	checkForError(stream);
}

float Armor::getC() const
{
	return c;
}

void Armor::write(std::ostream& os) const
{
	GameItem::write(os);
	os << "|protection: " << c;
}

void Armor::serialize(std::ostream& stream) const
{
	GameItem::serialize(stream);
	stream << " " << c;
}
