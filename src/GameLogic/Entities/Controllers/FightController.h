#ifndef __FIGHTCONTROLLER_H
#define __FIGHTCONTROLLER_H

class FightableEntity;

enum class AttackType
{
	STRENGTH_ATTACK,
	SPELL_ATTACK
};

class FightController
{
public:
	virtual AttackType getAttackType(const FightableEntity& you, const FightableEntity& opponent) = 0;
	virtual FightController* clone() const = 0;

public:
	virtual ~FightController() = default;
};

#endif // !__FIGHTCONTROLLER_H
