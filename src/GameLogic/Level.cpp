#include "Level.h"

Level::Level(size_t number, size_t seed) : number(number), mp(GameMap(Level::getMapPropertiesByNumber(number), seed))
{}

Level::Level(size_t number, GameMap& mp) : number(number), mp(mp)
{}

size_t Level::getMapRowCountByNumber(size_t number)
{
	return getNthMemberOfFibonacciLikeSequence(number, 10, 15);
}

size_t Level::getMapColCountByNumber(size_t number)
{
	return getNthMemberOfFibonacciLikeSequence(number, 10, 10);
}

size_t Level::getDragonCountByNumber(size_t number)
{
	return getNthMemberOfFibonacciLikeSequence(number, 2, 3);
}

size_t Level::getTreasureCountByNumber(size_t number)
{
	return getNthMemberOfFibonacciLikeSequence(number, 2, 2);
}

MapProperties Level::getMapPropertiesByNumber(size_t number)
{
	float adjustedLevelNumber = (float)number - 7.6f;
	float coef = sigmoid(adjustedLevelNumber/5.0f);

	float dragonStrength = ((number == 1) ? 25.0f : coef * 125.0f);
	float dragonMana = ((number == 1) ? 25.0f : coef * 125.0f);
	float dragonHealth = ((number == 1) ? 50.0f : coef * 250.0f);

	return MapProperties(getMapRowCountByNumber(number), getMapColCountByNumber(number),
		                 getDragonCountByNumber(number), getTreasureCountByNumber(number),
						 dragonStrength, dragonHealth, dragonMana,
		                 coef*0.9f, coef, coef*0.9f,
						 number);
}

LevelOutcome Level::play(Player &p)
{
	if (p.isAlive() == false)
		return LevelOutcome::PLAYER_DIED;

	while (true)
	{
		p.move();
		Interactions res = mp.doInteraction(p);
		
		if (p.isAlive() == false)
			return LevelOutcome::PLAYER_DIED;

		if (res == Interactions::MAP_EXITING)
			break;
	}

	if (p.isAlive() == true)
		p.postLevelAction();

	return LevelOutcome::COMPLETED;
}

size_t Level::getNthMemberOfFibonacciLikeSequence(size_t n, size_t f1, size_t f2)
{
	if (n == 0) return f2 - f1;
	if (n == 1) return f1;
	if (n == 2) return f2;

	for (size_t i = 3; i <= n; i++)
	{
		f1 = f1 + f2;
		std::swap(f1, f2);
	}

	return f2;
}

float Level::sigmoid(float x)
{
	return 1.0f/(1.0f+exp(-x));
}
