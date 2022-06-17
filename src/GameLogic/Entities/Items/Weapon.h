#ifndef __WEAPON_H
#define __WEAPON_H

#include "GameItem.h"

#include <iostream>

class Weapon : public GameItem
{
private:
	float c;

public:
	Weapon(const String& name, size_t level, float c);
	Weapon(std::iostream& stream);

public:
	float getC() const;

public:
	void write(std::ostream& os) const override;
	void serialize(std::ostream& stream) const override;
};

#endif

