#pragma once

#include "simpleTestFunction.h"
#include <exception>
#include <functional>
#include <simple.h>
#include <simpleHash.h>
#include <simpleLogger.h>
#include <simpleString.h>

namespace simple
{
	using simpleTestAssertion = std::function<bool (void)>;

	class simpleTestPackage
	{
	public:
		simpleTestPackage(const char* name)
		{
			_tests = new simpleHash<simpleString, simpleTestFunction>();
			_batteryName = name;
		}

		simpleTestPackage(const simpleString& name)
		{
			_tests = new simpleHash<simpleString, simpleTestFunction>();
			_batteryName = name;
		}

		~simpleTestPackage()
		{
			delete _tests;
		}

		bool run()
		{
			simpleTestPackage* that = this;
			bool anyErrors = false;

			_tests->iterate([&that, &anyErrors](const simpleString& key, simpleTestFunction value)
			{
				that->setCurrentTest(key);

				//logger->log("Running Test:  {}", key.c_str());

				bool result = false;

				try
				{
					result = value.testRun();
				}
				catch (const std::exception& ex)
				{
					simpleLogger::logColor(simpleConsoleColor::Red, "Exception: {}", ex.what());

					result = false;
				}

				if (result)
					simpleLogger::logColor(simpleConsoleColor::Green, "Test {} Success!", key.c_str());
				else
					simpleLogger::logColor(simpleConsoleColor::Red, "Test {} Fail!", key.c_str());

				anyErrors &= result;

				return iterationCallback::iterate;
			});

			return anyErrors;
		}

		void testAssert(const simpleString& assertName, simpleTestAssertion assertion)
		{
			bool result = false;

			try
			{
				result = assertion();
			}
			catch (const std::exception& ex)
			{
				simpleLogger::logColor(simpleConsoleColor::Red,
				                       "Unit Test {} Assertion Exception {}:  {}",
				                       _currentTestName.c_str(), assertName.c_str(), ex.what());
				result = false;
			}

			if (!result)
				simpleLogger::logColor(simpleConsoleColor::Red, "Unit Test {} Assertion {} Failed!",
				                       _currentTestName.c_str(), assertName.c_str());
		}

		void output(const char* message, simpleConsoleColor color = simpleConsoleColor::White)
		{
			simpleLogger::logColor(color, message);
		}

		simpleString getName()
		{
			return _batteryName;
		}

	protected:
		void addTest(simpleTestFunction testDelegate)
		{
			_tests->add(testDelegate.name, testDelegate);
		}

		void setCurrentTest(const simpleString& testName)
		{
			_currentTestName = testName;
		}

	private:
		simpleHash<simpleString, simpleTestFunction>* _tests;

		simpleString _currentTestName;
		simpleString _batteryName;
	};
}
