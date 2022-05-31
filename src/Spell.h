#ifndef __SPELL_H
#define __SPELL_H

#include "GameItem.h"

class Spell : public GameItem
{
private:
	float c;

public:
	Spell(const String& name, size_t level, float c);

public:
	float getC() const;
};

#endif // !__SPELL_H

