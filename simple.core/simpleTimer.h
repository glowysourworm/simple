#pragma once
#include <chrono>

namespace simple
{
	class simpleTimer
	{
	private:
		using clock = std::chrono::time_point<std::chrono::system_clock>;

	public:
		void mark();

		int markMilliseconds();

	private:
		clock _last;
	};
}
