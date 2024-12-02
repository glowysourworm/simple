#pragma once

#include "simpleTestFunction.h"
#include "simpleTestPackage.h"
#include <simpleHash.h>
#include <functional>

namespace simple::test
{
	class simpleComponentTests : public simpleTestPackage
	{
	public:
		simpleComponentTests() : simpleTestPackage("Simple Component Tests")
		{
			this->addTest(simpleTestFunction("create_simpleHash_brogueObject",
			                                 std::bind(&simpleComponentTests::create_simpleHash_brogueObject, this)));
		}

		~simpleComponentTests()
		{
		}

		bool create_simpleHash_brogueObject()
		{
			simpleHash<int, int> hash;

			hash.add(9, 9);

			return true;
		}
	};
}
