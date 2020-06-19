
#include "pge.hpp"

int main(int argc, char **argv)
{
	const char *file = argv[1];

	Demo demo;
	demo.Construct(780, 480, 2, 2, file);
	demo.Start();

	return 0;
}


/*
--Controls--
C - nes tick - whole cpu instruction
F - one whole frame
R - reset
SPACE - run
*/