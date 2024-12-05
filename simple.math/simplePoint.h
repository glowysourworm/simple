#pragma once

#include "simpleGraphNode.h"
#include <simple.h>

namespace simple::math
{
	using namespace simple;

	template <isHashable T>
	struct simplePoint : simpleGraphNode
	{
		T x;
		T y;

		simplePoint()
		{
			x = default_value::value<T>();
			y = default_value::value<T>();
		}

		simplePoint(const simplePoint<T>& copy)
		{
			x = copy.x;
			y = copy.y;
		}

		simplePoint(const T& ax, const T& ay)
		{
			x = ax;
			y = ay;
		}

		void operator=(const simplePoint<T>& copy)
		{
			x = copy.x;
			y = copy.y;
		}

		bool operator !=(const simplePoint<T>& point) const
		{
			return x != point.x || y != point.y;
		}

		bool operator ==(const simplePoint<T>& point) const
		{
			return x == point.x && y == point.y;
		}

		double distance(const simplePoint<T>& point) const
		{
			T dx = point.x - x;
			T dy = point.y - y;

			return sqrtf((dx * dx) + (dy * dy));
		}

		void translate(T offsetX, T offsetY)
		{
			x = x + offsetX;
			y = y + offsetY;
		}

		size_t getHash() const override
		{
			return hashGenerator::generateHash(x, y);
		}
	};
}
