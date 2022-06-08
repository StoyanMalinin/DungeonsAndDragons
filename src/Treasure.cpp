#include "Treasure.h"

Treasure::Treasure(int r, int c) : TileEntity(r, c), isTaken(false)
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
