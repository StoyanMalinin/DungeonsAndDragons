#include "FightMaster.h"

#include "Entities/FightableEntity.h"
#include "../Utils/GlobalRandomGenerator.h"

FightMaster::FightMaster() : f1(nullptr), f2(nullptr)
{}

void FightMaster::setFighter(FightableEntity* f)
{
	if (f1 == nullptr) f1 = f;
	else f2 = f;

	if (checkDone() == true) doInteraction();
}

bool FightMaster::checkDone() const
{
    return f1!=nullptr && f2!=nullptr;
}

void FightMaster::doInteraction()
{
	if (GlobalRandomGenerator::randBool() == true)
		std::swap(f1, f2);

	for (bool iter = false; f1->isAlive() == true && f2->isAlive() == true; iter ^= true)
	{
		if (iter == false) f1->attack(*f2);
		else f2->attack(*f1);
	}

	if (f1->isAlive() == true) f1->postBattleAction();
	else f2->postBattleAction();

	flush();
}

void FightMaster::flush()
{
	f1 = nullptr;
	f2 = nullptr;
}

FightMaster& FightMaster::getGlobalInstance()
{
	static FightMaster instance;
	return instance;
}
