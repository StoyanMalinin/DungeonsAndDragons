#ifndef __RANDOMFIGHTCONTROLLER_H
#define __RANDOMFIGHTCONTROLLER_H

#include "FightController.h"

class RandomFightController : public FightController
{
public:
	AttackType getAttackType(const FightableEntity& you, const FightableEntity& opponent) override;
	FightController* clone() const override;
};

#endif // __RANDOMFIGHTCONTROLLER_H