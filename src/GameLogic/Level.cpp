#include "Level.h"

//Level::Level(size_t number, size_t seed) : number(number), mp(getMapPropertiesByNumber(number), seed)
//{}

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
	return MapProperties(getMapRowCountByNumber(number), getMapColCountByNumber(number),
		                 getDragonCountByNumber(number), getTreasureCountByNumber(number),
						 25, 25, 50,
		                 5, 5, 10);
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
