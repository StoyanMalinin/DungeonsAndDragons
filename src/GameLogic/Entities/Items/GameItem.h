#ifndef __GAMEITEM_H
#define __GAMEITEM_H

#include "../../../Utils/String.h"

class GameItem
{
private:
	String name;
	size_t level;

protected:
	GameItem(const String& name, size_t level);

public:
	const String& getName() const;
	size_t getLevel() const;
};

#endif

