#ifndef __GAMEMAP_H
#define __GAMEMAP_H

#include "Entities/Dragon.h"
#include "Entities/Player.h"
#include "../Utils/Vector.hpp"

#include "../Utils/Pair.hpp"
#include "../Utils/Rectangle.h"
#include "../Utils/RandomGenerator.h"

#include "MapProperties.h"

#include <iostream>

class GameMap
{
private:
	MapProperties mp;
	size_t n, m;
	size_t dragonsCount, treasuresCount;
	Vector<Vector<SharedPtr<TileEntity>>> grid;
	Vector<SharedPtr<Dragon>> dragons;

public:
	GameMap(MapProperties &mp, size_t seed);
	GameMap(const GameMap& other) = delete;
	GameMap& operator =(const GameMap& other) = delete;

private:
	void fillBySpacePartitioning(RandomGenerator &rnd);
	void connectCellToDungeon(size_t i, size_t j, RandomGenerator& rnd);
	Pair<int,int> partitionSpaceRec(Rectangle scope, RandomGenerator& rnd, bool sideSplit, bool dimensionSplit, size_t depth);
	void genRadomPathBetweenTwoPoints(Pair<int, int> p1, Pair<int, int> p2, const Rectangle& boundingBox, Vector<Pair<int, int>>& path, RandomGenerator &rnd);
	bool randomDfsTo(Pair<int, int> x, Pair<int, int> destination, const Rectangle& boundingBox, Vector<Vector<bool>>& used, RandomGenerator& rnd, Vector <Pair<int, int>> &currPath, Vector<Pair<int, int>> &ansPath);
	void addDragonsAndTreasures(RandomGenerator& rnd);

public:
	void debug(std::ostream& os);
};

#endif