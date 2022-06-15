#ifndef __ARMOR_H
#define __ARMOR_H

#include <ostream>

#include "GameItem.h"
#include "../../../Utils/String.h"

class Armor : public GameItem
{
private:
	float c;

public:
	Armor(const String& name, size_t level, float c);

public:
	float getC() const;

public:
	void write(std::ostream& os) const override;
};

#endif
