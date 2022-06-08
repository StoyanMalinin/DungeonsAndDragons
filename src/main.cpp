#include <iostream>
#include "../tests/doctest.h"

#include "GameMap.h"
#include "Level.h"

/*
0 -> run unit tests
1 -> normal mode
*/
#define PROGRAM_MODE 0

void sandbox()
{
	GameMap mp(Level::getMapPropertiesByNumber(2), 22);
	mp.debug(std::cout);
}

int main()
{
#if (PROGRAM_MODE==0)
	doctest::Context().run();
#elif (PROGRAM_MODE==1)
	sandbox();
#else
	std::cout << "Invalid mode" << '\n';
#endif // (PROGRAM_MODE==1)
}
