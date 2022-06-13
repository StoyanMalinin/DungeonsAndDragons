#include "TileEntity.h"

#include <stdexcept>

TileEntity::TileEntity() : r(0), c(0)
{}

TileEntity::TileEntity(int r, int c) : r(r), c(c)
{}

int TileEntity::getR() const noexcept
{
	return r;
}

int TileEntity::getC() const noexcept
{
	return c;
}

void TileEntity::interact(GameEntity* other)
{
	if (other == nullptr) throw std::logic_error("cannot interact with nullptr");
	other->interactInternal(this);
}

TileEntity::~TileEntity()
{}
