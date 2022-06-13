#include <iostream>

#include "Sandbox.h"
#include "../tests/doctest.h"

/*
0 -> run unit tests
1 -> normal mode
*/
#define PROGRAM_MODE 1

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
