#include "UIFightController.h"
#include "../../../UI/UIHandler.h"

UIFightController::UIFightController(UIHandler& uih) : uih(uih)
{}

AttackType UIFightController::getAttackType(const FightableEntity& you, const FightableEntity& opponent)
{
    return char2AttackType(uih.requestAttackType(you, opponent));
}

FightController* UIFightController::clone() const
{
    return new UIFightController(*this);
}

AttackType UIFightController::char2AttackType(char c)
{
    if (c == 's') return AttackType::STRENGTH_ATTACK;
    if (c == 'm') return AttackType::SPELL_ATTACK;

    return AttackType();
}
