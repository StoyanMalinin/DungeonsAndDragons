#include "TileEntity.h"

TileEntity::TileEntity() : r(0), c(0)
{}

TileEntity::TileEntity(int r, int c) : r(r), c(c)
{}

void TileEntity::move(Directions dir) noexcept
{
	if (dir == Directions::UP) r--;
	else if (dir == Directions::DOWN) r++;
	else if (dir == Directions::LEFT) c--;
	else if (dir == Directions::RIGHT) c++;


}

int TileEntity::getR() const noexcept
{
	return r;
}

int TileEntity::getC() const noexcept
{
	return c;
}

TileEntity::~TileEntity()
{}
