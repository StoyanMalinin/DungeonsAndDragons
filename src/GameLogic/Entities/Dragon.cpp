#include "Dragon.h"

#include "../FightMaster.h"

Dragon::Dragon(int r, int c, float strength, float mana, float health, const FightController &fc, FightMaster &fm) 
	           : TileEntity(r, c), FightableEntity(strength, mana, health, fc, fm), armor("scales", 1, 0.15f)
{}

bool Dragon::canEnter() const
{
	return true;
}

Interactions Dragon::getInteractionType() const
{
	return Interactions::FIGHT;
}

char Dragon::getSymbol() const
{
	return 'D';
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

void Dragon::interact(GameEntity* other)
{
	if (other == nullptr) throw std::logic_error("cannot interact with nullptr");

	fm.setFighter(this);
	other->interactInternal(this);
	fm.flush();
}

void Dragon::interactInternal(GameEntity* other)
{
	fm.setFighter(this);
	fm.flush();
}