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

char WallTile::getSymbol() const
{
    return '#';
}

void WallTile::serialize(std::ostream& stream) const
{
    stream << "WallTile" << " ";
    TileEntity::serialize(stream);
}

TileEntity* WallTile::clone() const
{
    return new WallTile(*this);
}
