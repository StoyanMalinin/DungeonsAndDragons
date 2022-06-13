#include "Rectangle.h"

Rectangle::Rectangle(int minRow, int maxRow, int minCol, int maxCol) : minRow(minRow), maxRow(maxRow), minCol(minCol), maxCol(maxCol)
{}

bool Rectangle::isInside(int r, int c) const
{
	return ((minRow<=r && r<=maxRow) && (minCol<=c && c<=maxCol));
}

Rectangle Rectangle::randomSubrectangle(RandomGenerator& rnd)
{
	int resMinRow = rnd.randIntInRange(minRow, maxRow), resMaxRow = rnd.randIntInRange(minRow, maxRow);
	int resMinCol = rnd.randIntInRange(minCol, maxCol), resMaxCol = rnd.randIntInRange(minCol, maxCol);
	if (resMinRow > resMaxRow) std::swap(resMinRow, resMaxRow);
	if (resMinCol > resMaxCol) std::swap(resMinCol, resMaxCol);

	return Rectangle(resMinRow, resMaxRow, resMinCol, resMaxCol);
}

std::ostream& operator <<(std::ostream& os, const Rectangle& r)
{
	os << "[" << "[" << r.minRow << ", " << r.maxRow << "], " << "[" << r.minCol << ", " << r.maxCol << "]" << "]";
	return os;
}
