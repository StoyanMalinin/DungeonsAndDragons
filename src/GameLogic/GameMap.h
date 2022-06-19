#ifndef __GAMEMAP_H
#define __GAMEMAP_H

#include "../Utils/Vector.hpp"
#include "../Utils/SharedPtr.hpp"

class TileEntity;

struct Rectangle;
class RandomGenerator;
#include "../Utils/Pair.hpp"
#include "MapProperties.h"

#include <iostream>

struct MapProperties;
enum class Interactions;

class GameMap
{
private:
	MapProperties mp;
	Vector<Vector<SharedPtr<TileEntity>>> grid;

private:
	void deepCopyFromOther(const GameMap& other);

public:
	GameMap(MapProperties &mp, size_t seed);
	GameMap(std::iostream& stream);
	GameMap(const GameMap& other);
	GameMap& operator =(const GameMap& other) = delete;

private:
	void fillBySpacePartitioning(RandomGenerator &rnd);
	void connectCellToDungeon(size_t i, size_t j, RandomGenerator& rnd);
	Pair<int,int> partitionSpaceRec(Rectangle scope, RandomGenerator& rnd, bool sideSplit, bool dimensionSplit, size_t depth);
	void genRadomPathBetweenTwoPoints(Pair<int, int> p1, Pair<int, int> p2, const Rectangle& boundingBox, Vector<Pair<int, int>>& path, RandomGenerator &rnd);
	bool randomDfsTo(Pair<int, int> x, Pair<int, int> destination, const Rectangle& boundingBox, Vector<Vector<bool>>& used, RandomGenerator& rnd, Vector <Pair<int, int>> &currPath, Vector<Pair<int, int>> &ansPath);
	void addMapComponents(RandomGenerator& rnd);

private:
	void deserialize(std::iostream& stream);
	void checkStream(std::iostream& stream);

public:
	size_t getN() const;
	size_t getM() const;
	char getCharAt(size_t i, size_t j) const;
	const MapProperties& getMapProperties() const;

public:
	void serialize(std::ostream& stream) const;
	void serializeLn(std::ostream& stream) const;

public:
	int isInside(int r, int c) const;
	bool canEnter(int r, int c) const;

public:
	Interactions doInteraction(TileEntity &te);

public:
	void debug(std::ostream& os);
};

#endif