#ifndef __SANDBOX_H

#include "GameLogic/Level.h"
#include "GameLogic/GameMap.h"
#include "GameLogic/ItemExchangeMaster.h"

void sandbox()
{
	RandomGenerator rnd1(22);
	std::cout << rnd1.randIntInRange(1, 3) << '\n';

	RandomGenerator rnd2(22);
	std::cout << rnd2.peekRandIntInRange(1, 3) << '\n';
	std::cout << rnd2.randIntInRange(1, 3) << '\n';
}

#endif // !__SANDBOX_H
