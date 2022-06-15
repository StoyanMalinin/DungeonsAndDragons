#ifndef __UIFIGHTCONTROLLER_H
#define __UIFIGHTCONTROLLER_H

#include "FightController.h"
#include "../../../UI/UIHandler.h"

class UIFightController : public FightController
{
private:
	UIHandler &uih;

public:
	UIFightController(UIHandler& uih);

public:
	AttackType getAttackType(const FightableEntity& you, const FightableEntity& opponent) override;
	FightController* clone() const override;

private:
	static AttackType char2AttackType(char c);
};

#endif // !__UIFIGHTCONTROLLER_H

