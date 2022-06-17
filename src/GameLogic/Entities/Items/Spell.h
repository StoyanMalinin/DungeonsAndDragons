#ifndef __SPELL_H
#define __SPELL_H

#include "GameItem.h"

#include <iostream>

class Spell : public GameItem
{
private:
	float c;

public:
	Spell(const String& name, size_t level, float c);
	Spell(std::iostream& stream);

public:
	float getC() const;

public:
	void write(std::ostream& os) const override;
	void serialize(std::ostream& stream) const override;
};

#endif // !__SPELL_H

