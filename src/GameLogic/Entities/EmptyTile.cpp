#include "EmptyTile.h"

EmptyTile::EmptyTile(int r, int c) : TileEntity(r, c)
{}

bool EmptyTile::canEnter() const
{
    return true;
}

Interactions EmptyTile::getInteractionType() const
{
    return Interactions::BASIC;
}

char EmptyTile::getSymbol() const
{
    return '.';
}

void EmptyTile::serialize(std::ostream& stream) const
{
    stream << "EmptyTile" << " ";
    TileEntity::serialize(stream);
}
