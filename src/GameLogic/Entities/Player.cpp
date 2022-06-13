#include "Player.h"

#include "../FightMaster.h"
#include "../ItemExchangeMaster.h"

Player::Player(const String& name, int r, int c, float strength, float mana, float health, 
	           const FightController& fc, const ItemManagerController& imc, const MoveController& mc, 
	           ItemExchangeMaster& iem, FightMaster &fm)
	: MovableTileEntity(r, c, mc), FightableEntity(strength, mana, health, fc, fm), name(name), armor(nullptr), spell(nullptr), weapon(nullptr), imc(imc.clone()), iem(iem)
{}

bool Player::canEnter() const
{
	return false;
}

Interactions Player::getInteractionType() const
{
	return Interactions::INVALID;
}

char Player::getSymbol() const
{
	return 'P';
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

bool Player::acquireSpell(SharedPtr<Spell> s)
{
	if (imc->acquireSpell(spell, s) == true)
	{
		spell = s;
		return true;
	}

	return false;
}

bool Player::acquireArmor(SharedPtr<Armor> a)
{
	if (imc->acquireArmor(armor, a) == true)
	{
		armor = a;
		return true;
	}

	return false;
}

bool Player::acquireWeapon(SharedPtr<Weapon> w)
{
	if (imc->acquireWeapon(weapon, w) == true)
	{ 
		weapon = w;
		return true;
	}

	return false;
}

const Spell* Player::getSpell() const
{
	return spell.getRaw();
}

const Armor* Player::getArmor() const
{
	return armor.getRaw();
}

const Weapon* Player::getWeapon() const
{
	return weapon.getRaw();
}

void Player::interact(GameEntity* other)
{
	if (other == nullptr) throw std::logic_error("cannot interact with nullptr");
	
	iem.setReceiver(this);
	fm.setFighter(this);
	other->interactInternal(this);
	iem.flush();
	fm.flush();
}

void Player::interactInternal(GameEntity* other)
{
	//acquire items
	iem.setReceiver(this);
	iem.flush();

	//fight
	fm.setFighter(this);
	fm.flush();
}
