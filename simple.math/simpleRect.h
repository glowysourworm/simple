#pragma once

#include <simple.h>
#include <simpleException.h>
#include <functional>

namespace simple::math
{
	struct simpleRect : simpleStruct
	{
	public:
		int column;
		int row;
		int width;
		int height;

		simpleRect();
		simpleRect(const simpleRect& copy);
		simpleRect(int acolumn, int arow, int awidth, int aheight);

		void operator=(const simpleRect& copy);
		void set(const simpleRect& copy);

		bool operator==(const simpleRect& rect) const;
		bool operator!=(const simpleRect& rect) const;

		/// <summary>
		/// Returns true if the grid rect represents a valid rectangle in UI coordinates
		/// </summary>
		bool validateUI() const;

		int left() const;
		int right() const;
		int top() const;
		int bottom() const;
		int centerX() const;
		int centerY() const;
		long area() const;
		bool contains(int acolumn, int arow) const;
		bool contains(const simpleRect& rect) const;

		virtual size_t getHash() const override;
	};
}
