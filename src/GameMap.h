#ifndef __GAMEMAP_H
#define __GAMEMAP_H

#include "Dragon.h"
#include "Player.h"
#include "Vector.hpp"

class GameMap
{
private:
	size_t n, m;
	Vector<Vector<SharedPtr<TileEntity>>> grid;
	Vector<SharedPtr<Dragon>> dragons;

public:
	GameMap(size_t n, size_t m);
	GameMap(const GameMap& other) = delete;
	GameMap& operator =(const GameMap& other) = delete;


};

#endif