#ifndef __EMPTYTILE_H
#define __EMPTYTILE_H

#include "TileEntity.h"

class EmptyTile : public TileEntity
{
public:
	EmptyTile(int r, int c);

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
};

#endif // !__EMPTYTILE_H
