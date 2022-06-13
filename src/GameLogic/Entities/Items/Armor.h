#ifndef __ARMOR_H
#define __ARMOR_H

#include "../../../Utils/String.h"
#include "GameItem.h"

class Armor : public GameItem
{
private:
	float c;

public:
	Armor(const String& name, size_t level, float c);

public:
	float getC() const;
};

#endif
