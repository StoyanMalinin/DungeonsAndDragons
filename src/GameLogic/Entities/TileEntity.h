#ifndef __HILEENTITY_H
#define __HILEENTITY_H

#include "GameEntity.h"

enum class Interactions
{
	INVALID,
	BASIC,
	FIGHT,
	TREASURE_OPENING,
	MAP_EXITING,
};

class TileEntity : public virtual GameEntity
{
protected:
	int r, c;

public:
	TileEntity();
	TileEntity(int r, int c);

protected:
	TileEntity(const TileEntity& other) = default;

public:
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
