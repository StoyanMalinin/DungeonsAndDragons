#include "Spell.h"

Spell::Spell(const String& name, size_t level, float c) : GameItem(name, level), c(c)
{}

Spell::Spell(std::iostream & stream) : GameItem(stream)
{
	stream >> c;
	checkForError(stream);
}

float Spell::getC() const
{
	return c;
}

void Spell::write(std::ostream& os) const
{
	GameItem::write(os);
	os << "|magic: " << c;
}

void Spell::serialize(std::ostream& stream) const
{
	GameItem::serialize(stream);
	stream << " " << c;
}
