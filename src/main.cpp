#include <iostream>
#include "../tests/doctest.h"

#include <vector>
#include "SharedPtr.hpp"
#include "FightController.h"
#include "RandomFightController.h"
#include "Dragon.h"

#include "Player.h"
#include "Dragon.h"

#include "OptimalItemManagerController.h"

/*
0 -> run unit tests
1 -> normal mode
*/
#define PROGRAM_MODE 1

void sandbox()
{
	Player p("ivan", 1, 1, 10, 20, 100, RandomFightController(), OptimalItemManagerController());
	Dragon d(1, 1, 50, 5, 200, RandomFightController());

	p.acquireSpell(SharedPtr<Spell>(new Spell("abra kadabra", 1, 0.2)));

	while (d.isAlive() == true)
	{
		std::cout << d.getHealth() << '\n';
		p.attack(d);
	}
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