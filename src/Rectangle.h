#ifndef __ALABALA_H
#define __ALABALA_H

#include <iostream>
#include "RandomGenerator.h"

struct Rectangle
{
	int minRow, maxRow;
	int minCol, maxCol;

	Rectangle() = default;
	Rectangle(int minRow, int maxRow, int minCol, int maxCol);

	bool isInside(int r, int c) const;
	friend std::ostream& operator <<(std::ostream& os, const Rectangle& r);

	Rectangle randomSubrectangle(RandomGenerator& rnd);
};

#endif // !__RECTANGLE_H