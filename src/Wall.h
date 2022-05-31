#ifndef __WALL_H
#define __WALL_H

#include "TileEntity.h"

class Wall : public TileEntity
{
public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
};

#endif

