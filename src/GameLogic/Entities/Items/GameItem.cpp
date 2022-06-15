#include "GameItem.h"

GameItem::GameItem(const String& name, size_t level) : name(name), level(level)
{}

const String& GameItem::getName() const
{
	return name;
}

size_t GameItem::getLevel() const
{
	return level;
}

void GameItem::write(std::ostream& os) const
{
	os << "|name: " << name << "|level: " << level;
}

void GameItem::writeln(std::ostream& os) const
{
	write(os);
	os << '\n';
}
