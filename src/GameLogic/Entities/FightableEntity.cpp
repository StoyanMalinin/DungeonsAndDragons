#include "FightableEntity.h"

#include <stdexcept>

#include "../FightMaster.h"
#include "../../Utils/GlobalRandomGenerator.h"

FightableEntity::FightableEntity(float strength, float mana, float health, const FightController& fc, FightMaster &fm) 
	                            : strength(strength), mana(mana), health(health), fc(fc.clone()), fm(fm)
{}

void FightableEntity::postBattleAction()
{}

bool FightableEntity::isAlive() const
{
	return health>0.0001f;
}

void FightableEntity::setHealth(float health)
{
	if (health < 0) health = 0;
	this->health = health;
}

void FightableEntity::setStregth(float strength)
{
	if (strength < 0) strength = 0;
	this->strength = strength;
}

void FightableEntity::setMana(float mana)
{
	if (mana < 0) mana = 0;
	this->mana = mana;
}

float FightableEntity::getStrength() const
{
	return strength;
}

float FightableEntity::getMana() const
{
	return mana;
}

float FightableEntity::getHealth() const
{
	return health;
}

void FightableEntity::interact(GameEntity* other)
{
	if (other == nullptr) throw std::logic_error("cannot interact with nullptr");

	fm.setFighter(this);
	other->interactInternal(this);
	fm.flush();
}

void FightableEntity::interactInternal(FightableEntity* other)
{
	fm.setFighter(this);
	fm.flush();
}

void FightableEntity::write(std::ostream& os) const
{
	os << "|strength: " << strength << "|mana: " << mana << "|health: " << health;
}

void FightableEntity::writeln(std::ostream& os) const
{
	write(os);
	os << '\n';
}

FightableEntity::~FightableEntity()
{}
