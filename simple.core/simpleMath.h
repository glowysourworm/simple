#pragma once

#include "simple.h"
#include "simpleException.h"

#include <cmath>
#include <numbers>

namespace simple
{
	class simpleMath
	{
	public:
		static constexpr double Pi = std::numbers::pi;

	public:
		template <isNumber TMath>
		static TMath abs(TMath x)
		{
			if (x < 0)
				return x * -1;

			return x;
		}

		template <isNumber TMath>
		static TMath sign(TMath x)
		{
			if (x < 0)
				return -1;

			return 1;
		}

		template <isNumber TMath, isNumber...Args>
		static TMath minOf(const TMath x, const Args... args)
		{
			if (sizeof...(args) > 0)
			{
				TMath result = minOf(args...);

				return x < result ? x : result;
			}

			return x;
		}

		template <isNumber TMath, isNumber...Args>
		static TMath maxOf(const TMath x, const Args... args)
		{
			if (sizeof...(args) > 0)
			{
				TMath result = maxOf(args...);

				return x > result ? x : result;
			}

			return x;
		}

		template <isNumber TMath>
		static int nearestEvenFloor(const TMath x)
		{
			int result = simpleMath::floor(x);

			if (result % 2 == 0)
				return result;

			return result - 1;
		}

		// Cheat sheet:  https://easings.net/

		template <isNumber TMath>
		static TMath easeInCubic(const TMath x)
		{
			return powerImpl(x, 3);
		}

		template <isNumber TMath>
		static TMath easeOutCubic(const TMath x)
		{
			return 1 - powerImpl(1 - x, 3);
		}

		template <isNumber TMath>
		static double interpolate(TMath value1, TMath value2, double weight)
		{
			if (weight < 0 || weight > 1)
				throw simpleException("Improper interpolation weight simpleMath::interpolate");

			return (value1 * (1 - weight)) + (weight * value2);
		}

		template <isNumber TMath>
		static float easeATan(const TMath x)
		{
			// Calculated based on asymptotic functions using the ratio of the defender to the attacker's attribute values.
			// 
			// The piecewise function has an output of [0, 1) (asymptotically); but scaled to dramatically yield the final 
			// value close to 1.

			float result;

			// Scaled for pseudo-logarithmic dynamics from [0.001, 1]
			if (x <= 1)
				result = (0.637f * simpleMath::arctan(x - 1)) + 0.5f;

			else
				result = 0.318f * simpleMath::arctan(x - 1) + 0.5f;

			// Clip result and return
			return simpleMath::clamp(result, 0.0f, 1.0f);
		}

		template <isNumber TMath>
		static TMath power(const TMath x, const TMath raisedTo)
		{
			return powerImpl(x, raisedTo);
		}

		template <isNumber TMath>
		static TMath power(const TMath x, const int raisedTo)
		{
			return powerImpl(x, raisedTo);
		}

		template <isNumber TMath>
		static TMath squareRoot(TMath x)
		{
			if (isFloatLike<TMath>)
				return sqrtf(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return sqrt(x);

			else
				throw simpleException("Unknown sqrt type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath naturalLog(TMath x)
		{
			if (isFloatLike<TMath>)
				return log(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return log(x);

			else
				throw simpleException("Unknown sqrt type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath sine(TMath x)
		{
			if (isFloatLike<TMath>)
				return sinf(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return sin(x);

			else
				throw simpleException("Unknown sqrt type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath arctan(TMath x)
		{
			if (isFloatLike<TMath>)
				return atanf(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return atan(x);

			else
				throw simpleException("Unknown sqrt type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath exponential(TMath x)
		{
			if (isFloatLike<TMath>)
				return expf(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return exp(x);

			else
				throw simpleException("Unknown sqrt type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath floor(TMath x)
		{
			if (isFloatLike<TMath>)
				return floorf(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return std::floor(x);

			else
				throw simpleException("Unknown floor type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath ceiling(TMath x)
		{
			if (isFloatLike<TMath>)
				return ceilf(static_cast<float>(x));

			else if (isIntLike<TMath>)
				return ceil(x);

			else
				throw simpleException("Unknown ceiling type simpleMath.h");
		}

		template <isNumber TMath>
		static TMath clamp(TMath x, TMath low, TMath high)
		{
			if (x < low)
				return low;

			else if (x > high)
				return high;

			return x;
		}

		template <isNumber TMath>
		static TMath lowLimit(TMath x, TMath low)
		{
			if (x < low)
				return low;

			return x;
		}

		template <isNumber TMath>
		static TMath highLimit(TMath x, TMath high)
		{
			if (x > high)
				return high;

			return x;
		}

	private:
		template <isNumber TMath>
		static TMath minOf(const TMath x)
		{
			return x;
		}

		template <isNumber TMath>
		static TMath maxOf(const TMath x)
		{
			return x;
		}

		template <isNumber TMath>
		static float powerImpl(const TMath x, const int raisedTo)
		{
			return pow(x, raisedTo);
		}

		template <isNumber TMath>
		static float powerImpl(const TMath x, const float raisedTo)
		{
			return pow(x, raisedTo);
		}
	};
}
