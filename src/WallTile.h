#ifndef __WALLTILE_H
#define __WALLTILE_H

#include "TileEntity.h"

class WallTile : public TileEntity
{
public:
	WallTile(int r, int c);

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
};

#endif

