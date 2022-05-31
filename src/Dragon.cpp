#include "Dragon.h"

Dragon::Dragon(int r, int c, float strength, float mana, float health, const FightController &fc) : TileEntity(r, c), FightableEntity(strength, mana, health, fc), armor("scales", 1, 0.15f)
{}

bool Dragon::canEnter() const
{
	return true;
}

Interactions Dragon::getInteractionType() const
{
	return Interactions::FIGHT;
}

void Dragon::attack(FightableEntity& other) const
{
	AttackType at = fc->getAttackType();

	if (at == AttackType::STRENGTH_ATTACK) other.receiveDamage(getStrength());
	else other.receiveDamage(getMana());
}

void Dragon::receiveDamage(float damage)
{
	damage -= damage * armor.getC();
	setHealth(getHealth() - damage);
}
