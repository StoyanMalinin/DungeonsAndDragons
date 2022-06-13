#include "MovableTileEntity.h"

MovableTileEntity::MovableTileEntity(int r, int c, const MoveController& mc) : TileEntity(r, c), mc(mc.clone())
{

}

Pair<int, int> MovableTileEntity::peekNxtPosition()
{
	return calcNewPos(Pair<int, int>(r, c), mc->peekDirection());
}

void MovableTileEntity::move()
{
	Pair<int, int> newPos = calcNewPos(Pair<int, int>(r, c), mc->getDirection());

	r = newPos.first;
	c = newPos.second;
}

Pair<int, int> MovableTileEntity::calcNewPos(Pair<int, int> pos, Directions dir)
{
	if (dir == Directions::UP) pos.first--;
	else if (dir == Directions::DOWN) pos.first++;
	else if (dir == Directions::LEFT) pos.second--;
	else if (dir == Directions::RIGHT) pos.second++;

	return pos;
}
