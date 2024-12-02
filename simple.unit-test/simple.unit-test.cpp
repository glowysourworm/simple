#include <iostream>

#include <simple.h>
#include "simpleArrayTests.h"
#include "simpleBSTTests.h"
#include "simpleComponentTests.h"
#include "simpleHashTests.h"
#include "simpleRect.h"
#include "simpleLogger.h"

using namespace simple::test;

int main()
{
	std::cout << "Simple (Native) Lib:  Unit Test Project";

	simpleComponentTests componentTests;
	simpleBSTTests bstTests;
	simpleArrayTests arrayTests;
	simpleHashTests hashTests;

	componentTests.run();
	bstTests.run();
	arrayTests.run();
	hashTests.run();

	return 0;
}
