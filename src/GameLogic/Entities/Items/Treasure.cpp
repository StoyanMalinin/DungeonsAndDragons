#include "Treasure.h"

#include "../../ItemExchangeMaster.h"

Treasure::Treasure(int r, int c, ItemExchangeMaster& iem) : TileEntity(r, c), isTaken(false), iem(iem)
{}

bool Treasure::canEnter() const
{
	return true;
}

Interactions Treasure::getInteractionType() const
{
	return Interactions::BASIC;
}

char Treasure::getSymbol() const
{
	return 'T';
}

bool Treasure::getIsTaken() const
{
	return isTaken;
}

void Treasure::interact(GameEntity* other)
{
	if (other == nullptr) throw std::logic_error("cannot interact with nullptr");
	
	iem.setGiver(this);
	other->interactInternal(this);
	iem.flush();
}

void Treasure::interactInternal(GameEntity* other)
{
	iem.setGiver(this);
	iem.flush();
}