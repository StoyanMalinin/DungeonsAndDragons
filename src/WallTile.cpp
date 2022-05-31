#include "WallTile.h"

WallTile::WallTile(int r, int c) : TileEntity(r, c)
{}

bool WallTile::canEnter() const
{
    return false;
}

Interactions WallTile::getInteractionType() const
{
    return Interactions::INVALID;
}
