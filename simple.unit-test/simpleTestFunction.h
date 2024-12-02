#pragma once

#include <simple.h>
#include <simpleString.h>
#include <functional>

namespace simple::test
{
	struct simpleTestFunction : simpleStruct
	{
		simple::simpleString name;
		std::function<bool (void)> testRun;

		simpleTestFunction()
		{
		}

		simpleTestFunction(const char* aname, std::function<bool (void)> runFunc)
		{
			name = aname;
			testRun = runFunc;
		}

		bool operator==(const simpleTestFunction& other)
		{
			return name == other.name;
		}

		bool operator!=(const simpleTestFunction& other)
		{
			return name != other.name;
		}

		size_t getHash() const override
		{
			return hashGenerator::generateHash(name);
		}
	};
}
