#include <iostream>

#include "Application.h"
#include "../tests/doctest.h"

/*
0 -> run unit tests
1 -> normal mode
*/
#define PROGRAM_MODE 1

void runApp()
{
	Application* app = new Application(std::cin, std::cout);
	app->run();
	delete app;
}

int main()
{
#if (PROGRAM_MODE==0)
	doctest::Context().run();
#elif (PROGRAM_MODE==1)
	runApp();
#else
	std::cout << "Invalid mode" << '\n';
#endif // (PROGRAM_MODE==1)
}
