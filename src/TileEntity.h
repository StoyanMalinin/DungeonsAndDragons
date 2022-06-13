#ifndef __HILEENTITY_H
#define __HILEENTITY_H

#include "GameEntity.h"

enum class Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

enum class Interactions
{
	INVALID,
	BASIC,
	FIGHT
};

class TileEntity : public virtual GameEntity
{
private:
	int r, c;

public:
	TileEntity();
	TileEntity(int r, int c);

protected:
	TileEntity(const TileEntity& other) = default;

public:
	void move(Directions dir) noexcept;
	virtual bool canEnter() const = 0;
	virtual Interactions getInteractionType() const = 0;
	virtual char getSymbol() const = 0;

public:
	int getR() const noexcept;
	int getC() const noexcept;

public:
	void interact(GameEntity* other) override;

public:
	virtual ~TileEntity();
};

#endif
