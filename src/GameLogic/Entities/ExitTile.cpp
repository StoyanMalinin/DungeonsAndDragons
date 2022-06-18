#include "ExitTile.h"

ExitTile::ExitTile() : TileEntity()
{}

ExitTile::ExitTile(int r, int c) : TileEntity(r, c)
{}

bool ExitTile::canEnter() const
{
	return true;
}

Interactions ExitTile::getInteractionType() const
{
	return Interactions::MAP_EXITING;
}

char ExitTile::getSymbol() const
{
	return 'E';
}

void ExitTile::serialize(std::ostream& stream) const
{
	stream << "ExitTile" << " ";
	TileEntity::serialize(stream);
}

