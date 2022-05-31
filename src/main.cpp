#include <iostream>
#include "../tests/doctest.h"

#include <vector>
#include "SharedPtr.hpp"
#include "FightController.h"
#include "RandomFightController.h"
#include "Dragon.h"

#include "Player.h"
#include "Dragon.h"

#include "Vector.hpp"
#include "OptimalItemManagerController.h"

/*
0 -> run unit tests
1 -> normal mode
*/
#define PROGRAM_MODE 0

void sandbox()
{
	
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