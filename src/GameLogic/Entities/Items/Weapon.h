#ifndef __WEAPON_H
#define __WEAPON_H

#include "GameItem.h"

class Weapon : public GameItem
{
private:
	float c;

public:
	Weapon(const String& name, size_t level, float c);

public:
	float getC() const;

public:
	void write(std::ostream& os) const override;
};

#endif

