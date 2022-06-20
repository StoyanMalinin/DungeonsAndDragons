#include "Level.h"

#include "GameMap.h"
#include "MapProperties.h"
#include "Entities/Player/Player.h"

#include <fstream>

Level::Level(size_t number, size_t seed) : number(number), mp(Level::getMapPropertiesByNumber(number), seed)
{}

Level::Level(size_t number, const GameMap& mp) : number(number), mp(mp)
{

}

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
						 dragonStrength, dragonMana, dragonHealth,
		                 coef*0.9f, coef, coef*0.9f,
						 number);
}

const GameMap& Level::getMap() const
{
	return mp;
}

LevelOutcome Level::play(Player &p, String *s)
{
	if (p.isAlive() == false)
		return LevelOutcome::PLAYER_DIED;

	while (true)
	{
		std::fstream f;

		p.move();
		Interactions res = mp.doInteraction(p);

		if (s != nullptr)
		{
			f.open(s->getData(), std::ios::out | std::ios::trunc);
			if (f.is_open() == false) throw std::logic_error("Cannot open backup file!");
		}

		if (p.isAlive() == false)
			return LevelOutcome::PLAYER_DIED;

		if (res == Interactions::MAP_EXITING)
			break;

		if (f.is_open() == true)
		{
			serializeLn(f);
			p.serializeLn(f);

			f.close();
			if (f.bad() == true)
				throw std::exception("Error while closing file after backup!");
		}
	}

	if (p.isAlive() == true)
		p.postLevelAction();

	return LevelOutcome::COMPLETED;
}

void Level::serialize(std::ostream& stream) const
{
	stream << number << " ";
	mp.serialize(stream);
}

void Level::serializeLn(std::ostream& stream) const
{
	serialize(stream);
	stream << '\n';
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
