#include "Player.h"

#include "../../FightMaster.h"
#include "../../ItemExchangeMaster.h"
#include "../Controllers/FightController.h"

Player::Player(const String& name, int r, int c, float strength, float mana, float health,
			   const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
			   ItemExchangeMaster& iem, FightMaster& fm)
	          
	: MovableTileEntity(r, c, mc), FightableEntity(strength, mana, health, fc, fm), 
	            name(name), armor(nullptr), spell(nullptr), weapon(nullptr), 
	            imc(imc.clone()), iem(iem), initialHealth(health), pdc(pdc.clone())
{}

Player::Player(const String & name, int r, int c, float strength, float mana, float health, float initialHealth, const FightController & fc, const ItemManagerController & imc, const MoveController & mc, const PointsDistributionController & pdc, ItemExchangeMaster & iem, FightMaster & fm)
	: MovableTileEntity(r, c, mc), FightableEntity(strength, mana, health, fc, fm),
	name(name), armor(nullptr), spell(nullptr), weapon(nullptr),
	imc(imc.clone()), iem(iem), initialHealth(initialHealth), pdc(pdc.clone())
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
	AttackType at = fc->getAttackType(*this, other);

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

void Player::postBattleAction()
{
	if (getHealth() < initialHealth * 0.5f)
		setHealth(initialHealth * 0.5f);
}

void Player::postLevelAction()
{
	float allPoints = 30;
	float strengthBoost, manaBoost, healthBoost;

	pdc->distributePoints(allPoints, strengthBoost, manaBoost, healthBoost);

	setStregth(getStrength() + strengthBoost);
	setMana(getMana() + manaBoost);
	setHealth(getHealth() + healthBoost);
}

void Player::serialize(std::ostream& stream) const
{
	stream << 'p';
	serializeRawData(stream);

	if (stream.bad() == true)
		throw std::exception("Error while serializing player, the stream got corrupted!");
}

void Player::serializeRawData(std::ostream& stream) const
{
	stream << " " << name.getLen();
	stream << " "; stream << name;
	stream << " "; stream << getR();
	stream << " "; stream << getC();
	stream << " "; stream << getStrength();
	stream << " "; stream << getMana();
	stream << " "; stream << getHealth();
	stream << " "; stream << initialHealth;

	stream << " ";
	if (spell.isNull() == true) stream << "!";
	else spell->serialize(stream);

	stream << " ";
	if (armor.isNull() == true) stream << "!";
	else armor->serialize(stream);

	stream << " ";
	if (weapon.isNull() == true) stream << "!";
	else weapon->serialize(stream);
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

void Player::setSpell(SharedPtr<Spell> s)
{
	spell = s;
}

void Player::setArmor(SharedPtr<Armor> a)
{
	armor = a;
}

void Player::setWeapon(SharedPtr<Weapon> w)
{
	weapon = w;
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

const String& Player::getName() const
{
	return name;
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

TileEntity* Player::clone() const
{
	return new Player(*this);
}
