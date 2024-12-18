#pragma once

#include "simpleGraphEdge.h"
#include <simple.h>
#include <simpleMath.h>
#include "simpleVectorMath.h"
#include "simplePoint.h"
#include "simpleVector.h"

namespace simple::math
{
	using namespace simple;

	enum class simpleLineIntersectionResult
	{
		None = 0,
		SinglePoint = 1,
		Collinear = 2
	};

	template <isHashable T>
	struct simpleLine : public simpleGraphEdge<simplePoint<T>>
	{
	public:
		simpleLine()
		{
		}

		simpleLine(const simplePoint<T>& point1, const simplePoint<T>& point2)
		{
			this->node1 = point1;
			this->node2 = point2;
		}

		simpleLine(const simpleLine<T>& copy)
		{
			this->node1 = copy.node1;
			this->node2 = copy.node2;
		}

		void operator=(const simpleLine<T>& other)
		{
			this->node1 = other.node1;
			this->node2 = other.node2;
		}

		bool operator==(const simpleLine<T>& other)
		{
			return this->node1 == other.node1 &&
				this->node2 == other.node2;
		}

		bool operator!=(const simpleLine<T>& other)
		{
			return this->node1 != other.node1 ||
				this->node2 != other.node2;
		}

		void translate(const simplePoint<T>& offset)
		{
			this->node1.translate(offset.x, offset.y);
			this->node2.translate(offset.x, offset.y);
		}

		float weight() const override
		{
			return this->node1.distance (this->node2);
		}

		simpleLineIntersectionResult calculateIntersection (const simpleLine<T>& other)
		{
			// Line Segment Intersection:
			//
			// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
			/*
				Two segments (p1,q1) and (p2,q2) intersect iff one of the following two
				conditions is true:

				1. General Case:
				� (p1, q1, p2) and (p1, q1, q2) have different orientations and
				� (p2, q2, p1) and (p2, q2, q1) have different orientations.

				2. Special Case:
				� (p1, q1, p2), (p1, q1, q2), (p2, q2, p1), and (p2, q2, q1) are all collinear and
				� the x-projections of (p1, q1) and (p2, q2) intersect
				� the y-projections of (p1, q1) and (p2, q2) intersect
			 *
			 */

			simplePoint<T> p1 = this->node1; // Their notation was off... p/q are not vectors (>_<)
			simplePoint<T> q1 = this->node2;
			simplePoint<T> p2 = other.node1;
			simplePoint<T> q2 = other.node2;

			// Find the four orientations needed for general and 
			// special cases 
			T o1 = simpleVectorMath::orientationPoint(p1, q1, p2);

			// TODO TODO!!! We have bigger issues with Real V.S. UI Coordinates.
			//
			// Update:  This algorithm works in Real coordinates. There's still a
			//			todo on the backlog for the general "coordinate system"
			//			problem being added to "simple"
			T o2 = simpleVectorMath::orientationPoint(p1, q1, q2);

			// These need to be explicit! And, all our math has to be done in
			T o3 = simpleVectorMath::orientationPoint(p2, q2, p1);

			// REAL coordinates unless the algorithm / function stipulates it explicitly!
			T o4 = simpleVectorMath::orientationPoint(p2, q2, q1);

			// General case 
			if ((o1 != o2) && (o3 != o4))
				return simpleLineIntersectionResult::SinglePoint;

			// Special Cases (collinear)
			// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
			if (o1 == 0 && simpleVectorMath::onSegmentCollinear(p1, p2, q1))
				return simpleLineIntersectionResult::Collinear;

			// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
			if (o2 == 0 && simpleVectorMath::onSegmentCollinear(p1, q2, q1))
				return simpleLineIntersectionResult::Collinear;

			// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
			if (o3 == 0 && simpleVectorMath::onSegmentCollinear(p2, p1, q2))
				return simpleLineIntersectionResult::Collinear;

			// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
			if (o4 == 0 && simpleVectorMath::onSegmentCollinear(p2, q1, q2))
				return simpleLineIntersectionResult::Collinear;

			return simpleLineIntersectionResult::None;
		}

		bool isEquivalent(const simplePoint<T>& point1, const simplePoint<T>& point2) const
		{
			return (this->node1.x == point1.x &&
					this->node1.y == point1.y &&
					this->node2.x == point2.x &&
					this->node2.y == point2.y) ||
				(this->node1.x == point2.x &&
					this->node1.y == point2.y &&
					this->node2.x == point1.x &&
					this->node2.y == point1.y);
		}
	};
}
