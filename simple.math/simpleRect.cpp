#pragma once
#include <simpleMath.h>
#include "simpleRect.h"

namespace simple::math
{
	simpleRect::simpleRect()
	{
		column = 0;
		row = 0;
		width = 0;
		height = 0;
	}

	simpleRect::simpleRect(const simpleRect& copy)
	{
		column = copy.column;
		row = copy.row;
		width = copy.width;
		height = copy.height;
	}

	simpleRect::simpleRect(int acolumn, int arow, int awidth, int aheight)
	{
		column = acolumn;
		row = arow;
		width = awidth;
		height = aheight;
	}

	void simpleRect::operator=(const simpleRect& copy)
	{
		column = copy.column;
		row = copy.row;
		width = copy.width;
		height = copy.height;
	}

	void simpleRect::set(const simpleRect& copy)
	{
		column = copy.column;
		row = copy.row;
		width = copy.width;
		height = copy.height;
	}


	bool simpleRect::operator==(const simpleRect& rect) const
	{
		return column == rect.column &&
			row == rect.row &&
			width == rect.width &&
			height == rect.height;
	}

	bool simpleRect::operator!=(const simpleRect& rect) const
	{
		return column != rect.column ||
			row != rect.row ||
			width != rect.width ||
			height != rect.height;
	}

	/// <summary>
	/// Returns true if the grid rect represents a valid rectangle in UI coordinates
	/// </summary>
	/// <returns></returns>
	bool simpleRect::validateUI() const
	{
		if (column < 0)
			return false;

		if (row < 0)
			return false;

		if (width <= 0)
			return false;

		if (height <= 0)
			return false;

		return true;
	}

	int simpleRect::left() const

	{
		return column;
	}

	int simpleRect::right() const
	{
		return column + width - 1;
	}

	int simpleRect::top() const
	{
		return row;
	}

	int simpleRect::bottom() const
	{
		return row + height - 1;
	}

	int simpleRect::centerX() const
	{
		return column + simpleMath::floor(width / 2.0f);
	}

	int simpleRect::centerY() const
	{
		return row + simpleMath::floor(height / 2.0f);
	}

	long simpleRect::area() const
	{
		return width * height;
	}

	bool simpleRect::contains(int acolumn, int arow) const
	{
		if (acolumn < left())
			return false;

		if (acolumn > right())
			return false;

		if (arow < top())
			return false;

		if (arow > bottom())
			return false;

		return true;
	}

	bool simpleRect::contains(const simpleRect& rect) const
	{
		if (!contains(rect.left(), rect.top()))
			return false;

		if (!contains(rect.left(), rect.bottom()))
			return false;

		if (!contains(rect.right(), rect.top()))
			return false;

		if (!contains(rect.right(), rect.bottom()))
			return false;

		return true;
	}

	size_t simpleRect::getHash() const
	{
		return hashGenerator::generateHash(column, row, width, height);
	}
}
