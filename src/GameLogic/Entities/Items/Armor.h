#ifndef __ARMOR_H
#define __ARMOR_H

#include <ostream>

#include "GameItem.h"
#include "../../../Utils/String.h"

#include <iostream>

class Armor : public GameItem
{
private:
	float c;

public:
	Armor(const String& name, size_t level, float c);
	Armor(std::iostream& stream);

public:
	float getC() const;

public:
	void write(std::ostream& os) const override;
	void serialize(std::ostream& stream) const override;
};

#endif
