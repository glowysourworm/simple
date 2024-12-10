#pragma once

#include <simple.h>

namespace simple::math
{
	using namespace simple;

	struct simpleSize : public simpleStruct
	{
	public:
		int width;
		int height;

		simpleSize()
		{
			width = 0;
			height = 0;
		}
		simpleSize(const simpleSize& copy)
		{
			width = copy.width;
			height = copy.height;
		}
		simpleSize(int awidth, int aheight)
		{
			width = awidth;
			height = aheight;
		}

		void operator=(const simpleSize& copy)
		{
			width = copy.width;
			height = copy.height;
		}

		bool operator==(const simpleSize& other) const
		{
			return width == other.width && height == other.height;
		}
		bool operator!=(const simpleSize& other) const
		{
			return width != other.width || height != other.height;
		}

		long area() const
		{
			return width * height;
		}

		simpleSize createExpanded(int amount)
		{
			return simpleSize(width + amount, height + amount);
		}

		virtual size_t getHash() const override
		{
			return hashGenerator::generateHash(width, height);
		}
	};
}
