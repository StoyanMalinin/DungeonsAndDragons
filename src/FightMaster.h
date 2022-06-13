#ifndef __FIGHTMASTER_H
#define __FIGHTMASTER_H

#include "InteractionMaster.h"

class FightableEntity;

class FightMaster : public InteractionMaster
{
private:
	FightableEntity *f1, *f2;

public:
	FightMaster();

public:
	void setFighter(FightableEntity *f);

private:
	bool checkDone() const;
	void doInteraction() override;

public:
	void flush() override;

public:
	static FightMaster& getGlobalInstance();
};

#endif // !__FIGHTMASTER_H
