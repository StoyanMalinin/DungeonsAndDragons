#include <iostream>
//#include "../tests/doctest.h"

#include "GameMap.h"

/*
0 -> run unit tests
1 -> normal mode
*/
#define PROGRAM_MODE 1

void sandbox()
{
	GameMap mp(50, 50, 19);
	mp.debug(std::cout);
}

int main()
{
#if (PROGRAM_MODE==0)
	//doctest::Context().run();
#elif (PROGRAM_MODE==1)
	sandbox();
#else
	std::cout << "Invalid mode" << '\n';
#endif // (PROGRAM_MODE==1)
}
