#ifndef __LEVEL_H
#define __LEVEL_H

#include "GameMap.h"

enum class LevelOutcome
{
	COMPLETED,
	PLAYER_DIED,
};

class Level
{
private:
	size_t number;
	GameMap &mp;
	Player &p;

public:
	Level(size_t number, GameMap &mp, Player &p);

public:
	static size_t getMapRowCountByNumber(size_t number);
	static size_t getMapColCountByNumber(size_t number);
	static size_t getDragonCountByNumber(size_t number);
	static size_t getTreasureCountByNumber(size_t number);
	static MapProperties getMapPropertiesByNumber(size_t number);

public:
	LevelOutcome play();

private:
	static size_t getNthMemberOfFibonacciLikeSequence(size_t n, size_t f1, size_t f2);
	static float sigmoid(float x);
};

#endif // !__LEVEL_H
