#pragma once

#include <simple.h>
#include <simpleMath.h>
#include "simplePoint.h"
#include "simpleVector.h"

namespace simple::math
{
	class simpleVectorMath
	{
	public:
		template <isNumber TMath>
		static simpleVector<TMath> subtract(const simplePoint<TMath>& point2, const simplePoint<TMath>& point1)
		{
			return simpleVector<TMath>(point2.x - point1.x, point2.y - point1.y);
		}

		/// <summary>
		/// Returns the determinant of the orientation cross product (the sign of the cross product resulting in 
		/// crossing two difference vectors that order points 1,2, and 3 in that order). The sign of the determinant
		/// returned shows the orientation of the ordering (clockwise, counter-clockwise, or collinear)
		/// </summary>
		template <isNumber TMath>
		static int orientation(const simplePoint<TMath>& point1, const simplePoint<TMath>& point2,
		                       const simplePoint<TMath>& point3)
		{
			// 1 -> 2 -> 3 (Results from crossing the vectors 12 X 23 - where subtracting the points gives you the vector)
			simpleVector<TMath> vector12 = simpleVectorMath::subtract(point2, point1);
			simpleVector<TMath> vector23 = simpleVectorMath::subtract(point3, point2);

			TMath value = vector12.cross(vector23);

			if (value == 0)
				return 0;

			return simpleMath::sign(value);
		}

		// To find orientation of ordered triplet (p, q, r). 
		// The function returns following values 
		// 0 --> p, q and r are collinear 
		// 1 --> Clockwise 
		// 2 --> Counterclockwise
		template <isNumber TMath>
		static int orientationPoint(const simplePoint<TMath>& point1, const simplePoint<TMath>& point2,
		                            const simplePoint<TMath>& point3)
		{
			// See https://www.geeksforgeeks.org/orientation-3-ordered-points/ 
			// for details of below formula. 
			int val = ((point2.y - point1.y) * (point3.x - point2.x)) - ((point3.x - point1.x) * (point3.y - point2.y));

			if (val == 0)
				return 0; // collinear 

			return simpleMath::sign(val);
		}

		template <isNumber TMath>
		static bool onSegmentCollinear(const simplePoint<TMath>& point1, const simplePoint<TMath>& point2,
		                               const simplePoint<TMath>& point3)
		{
			// Given three collinear points p, q, r, the function checks if 
			// point2 lies on line segment 'point1 -> point3' 
			if (point2.x <= simpleMath::maxOf(point1.x, point3.x) && point2.x >= simpleMath::minOf(point1.x, point3.x)
				&&
				point2.y <= simpleMath::maxOf(point1.y, point3.y) && point2.y >= simpleMath::minOf(point1.y, point3.y))
				return true;

			return false;
		}
	};
}
