#include "RandomFightController.h"
#include "../../../Utils/GlobalRandomGenerator.h"

AttackType RandomFightController::getAttackType()
{
    int res = GlobalRandomGenerator::randIntInRange(0, 1);

    if (res == 0) return AttackType::STRENGTH_ATTACK;
    else return AttackType::SPELL_ATTACK;
}

FightController* RandomFightController::clone() const
{
    return new RandomFightController(*this);
}
