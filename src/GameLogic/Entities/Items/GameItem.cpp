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
