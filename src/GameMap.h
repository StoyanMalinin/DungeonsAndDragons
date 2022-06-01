#ifndef __GAMEMAP_H
#define __GAMEMAP_H

#include "Dragon.h"
#include "Player.h"
#include "Vector.hpp"

#include "Pair.hpp"
#include "Rectangle.h"
#include "RandomGenerator.h"

#include <iostream>

class GameMap
{
private:
	size_t n, m;
	Vector<Vector<SharedPtr<TileEntity>>> grid;
	Vector<SharedPtr<Dragon>> dragons;

public:
	GameMap(size_t n, size_t m);
	GameMap(size_t n, size_t m, size_t seed);
	GameMap(const GameMap& other) = delete;
	GameMap& operator =(const GameMap& other) = delete;

private:
	void fillBySpacePartitioning(size_t seed);
	void connectCellToDungeon(size_t i, size_t j, RandomGenerator& rnd);
	Pair<int,int> partitionSpaceRec(Rectangle scope, RandomGenerator& rnd, bool sideSplit, bool dimensionSplit, size_t depth);
	void genRadomPathBetweenTwoPoints(Pair<int, int> p1, Pair<int, int> p2, const Rectangle& boundingBox, Vector<Pair<int, int>>& path, RandomGenerator &rnd);
	bool randomDfsTo(Pair<int, int> x, Pair<int, int> destination, const Rectangle& boundingBox, Vector<Vector<bool>>& used, RandomGenerator& rnd, Vector <Pair<int, int>> &currPath, Vector<Pair<int, int>> &ansPath);

public:
	void debug(std::ostream& os);
};

#endif