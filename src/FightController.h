#ifndef __FIGHTCONTROLLER_H
#define __FIGHTCONTROLLER_H

enum class AttackType
{
	STRENGTH_ATTACK,
	SPELL_ATTACK
};

class FightController
{
public:
	virtual AttackType getAttackType() = 0;
	virtual FightController* clone() const = 0;
};

#endif // !__FIGHTCONTROLLER_H
