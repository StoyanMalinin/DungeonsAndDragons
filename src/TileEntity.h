#ifndef __HILEENTITY_H
#define __HILEENTITY_H

enum class Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class TileEntity
{
private:
	int r, c;

public:
	TileEntity();
	TileEntity(int r, int c);

public:
	void move(Directions dir) noexcept;
	virtual bool canEnter() const = 0;

public:
	int getR() const noexcept;
	int getC() const noexcept;

public:
	virtual ~TileEntity();
};

#endif
