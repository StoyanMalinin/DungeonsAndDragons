#ifndef __EMPTYCELL_H
#define __EMPTYCELL_H

#include "TileEntity.h"

class EmptyCell : public TileEntity
{
public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
};

#endif // !__EMPTYCELL_H
