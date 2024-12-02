#pragma once

#include "simple.h"
#include "simpleLogger.h"
#include "simpleExt.h"
#include <iostream>

namespace simple
{
	enum class simpleConsoleColor : int
	{
		White = 97,
		Green = 92,
		Yellow = 93,
		Red = 91,
		Blue = 94
	};

	class simpleLogger
	{
	public:
		/*

			TODO: Wrap terminal stream in a class

			30	Black	90	Bright Black
			31	Red		91	Bright Red
			32	Green	92	Bright Green
			33	Yellow	93	Bright Yellow
			34	Blue	94	Bright Blue
			35	Magenta	95	Bright Magenta
			36	Cyan	96	Bright Cyan
			37	White	97	Bright White

		*/

		static void log(const char* message);

		static void logColor(const simpleConsoleColor& color, const char* message);

		template <isStringConvertible T, isStringConvertible...Args>
		static void log(const char* formatStr, const T& param, const Args&... args);

		template <isStringConvertible T, isStringConvertible...Args>
		static void logColor(const simpleConsoleColor& color, const char* formatStr, const T& param,
		                     const Args&... args);

	private:
		static void setColor(simpleConsoleColor textColor);
	};

	void simpleLogger::log(const char* message)
	{
		std::cout << message << std::endl;
	}

	void simpleLogger::logColor(const simpleConsoleColor& color, const char* message)
	{
		setColor(color);
		std::cout << message << std::endl;
		setColor(simpleConsoleColor::White);
	}

	template <isStringConvertible T, isStringConvertible... Args>
	void simpleLogger::log(const char* formatStr, const T& param, const Args&... args)
	{
		std::string message = simpleExt::format(formatStr, param, args...);

		std::cout << message << std::endl;
	}

	template <isStringConvertible T, isStringConvertible... Args>
	void simpleLogger::logColor(const simpleConsoleColor& color, const char* formatStr, const T& param,
	                            const Args&... args)
	{
		std::string message = simpleExt::format(formatStr, param, args...);

		setColor(color);
		std::cout << message << std::endl;
		setColor(simpleConsoleColor::White);
	}

	void simpleLogger::setColor(simpleConsoleColor textColor)
	{
		std::cout << "\033[" << (int)textColor << "m";
	}
}
