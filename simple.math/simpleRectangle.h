#pragma once

#include <simple.h>
#include "simplePoint.h"
#include "simpleLine.h"

namespace simple::math
{
	template <isNumber T>
	struct simpleRectangle : simpleStruct
	{
		simpleRectangle()
		{
			_topLeft = default_value::value<simplePoint<T>>();
			_bottomRight = default_value::value<simplePoint<T>>();
		}

		simpleRectangle(const simplePoint<T>& topLeft, const simplePoint<T>& bottomRight)
		{
			_topLeft = topLeft;
			_bottomRight = bottomRight;
		}

		simpleRectangle(const simpleRectangle<T>& copy)
		{
			_topLeft = copy.getTopLeft();
			_bottomRight = copy.getBottomRight();
		}

		void operator=(const simpleRectangle<T>& copy)
		{
			_topLeft = copy.getTopLeft();
			_bottomRight = copy.getBottomRight();
		}

		bool operator==(const simpleRectangle<T>& other)
		{
			return _topLeft == other.getTopLeft() &&
				_bottomRight == other.getBottomRight();
		}

		bool operator!=(const simpleRectangle<T>& other)
		{
			return _topLeft != other.getTopLeft() ||
				_bottomRight != other.getBottomRight();
		}

		bool intersects(const simpleLine<T>& line)
		{
			simpleLine<T> lineLeft(simplePoint<T>(_topLeft.x, _topLeft.y), simplePoint<T>(_topLeft.x, _bottomRight.y));
			simpleLine<T> lineBottom(simplePoint<T>(_topLeft.x, _bottomRight.y),
			                         simplePoint<T>(_bottomRight.x, _bottomRight.y));
			simpleLine<T> lineRight(simplePoint<T>(_bottomRight.x, _bottomRight.y),
			                        simplePoint<T>(_bottomRight.x, _topLeft.y));
			simpleLine<T> lineTop(simplePoint<T>(_bottomRight.x, _topLeft.y), simplePoint<T>(_topLeft.x, _topLeft.y));

			bool intersectsLeft = lineLeft.calculateIntersection(line) != simpleLineIntersectionResult::None;
			bool intersectsBottom = lineBottom.calculateIntersection(line) != simpleLineIntersectionResult::None;
			bool intersectsRight = lineRight.calculateIntersection(line) != simpleLineIntersectionResult::None;
			bool intersectsTop = lineTop.calculateIntersection(line) != simpleLineIntersectionResult::None;

			return intersectsLeft || intersectsBottom || intersectsRight || intersectsTop;
		}

		simpleRect getSimpleRect() const
		{
			return simpleRect(_topLeft.x, _topLeft.y, _bottomRight.x - _topLeft.x + 1, _bottomRight.y - _topLeft.y + 1);
		}

		simplePoint<T> getTopLeft() const
		{
			return _topLeft;
		}

		simplePoint<T> getTopRight () const
		{
			return simplePoint<T>(_bottomRight.x, _topLeft.y);
		}

		simplePoint<T> getBottomLeft () const
		{
			return simplePoint<T> (_topLeft.x, _bottomRight.y);
		}

		simplePoint<T> getBottomRight() const
		{
			return _bottomRight;
		}



	private:
		simplePoint<T> _topLeft;
		simplePoint<T> _bottomRight;
	};
}
