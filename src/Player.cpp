#include "Player.h"

Player::Player(const String& name, int r, int c, float strength, float mana, float health, const FightController& fc) 
	: TileEntity(r, c), FightableEntity(strength, mana, health, fc), name(name), armor(nullptr), spell(nullptr), weapon(nullptr)
{}

bool Player::canEnter() const
{
	return false;
}

Interactions Player::getInteractionType() const
{
	return Interactions::INVALID;
}

void Player::attack(FightableEntity& other) const
{
	AttackType at = fc->getAttackType();

	float attackPower = 0;
	if (at == AttackType::STRENGTH_ATTACK)
	{
		attackPower = getStrength();
		if (weapon.isNull() == false) attackPower += attackPower * weapon->getC();
	}
	else if(at == AttackType::SPELL_ATTACK)
	{
		attackPower = getMana();
		if (spell.isNull() == false) attackPower += attackPower * spell->getC();
	}

	other.receiveDamage(attackPower);
}

void Player::receiveDamage(float damage)
{
	if(armor.isNull()==false)
		damage -= damage * armor->getC();

	setHealth(getHealth() - damage);
}