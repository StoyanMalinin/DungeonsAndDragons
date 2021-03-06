#ifndef __EXITTILE_H
#define __EXITTILE_H

#include "TileEntity.h"

class ExitTile : public TileEntity
{
public:
	ExitTile();
	ExitTile(int r, int c);

public:
	bool canEnter() const override;
	Interactions getInteractionType() const override;
	char getSymbol() const override;

public:
	void serialize(std::ostream& stream) const override;
	TileEntity* clone() const override;
};

#endif // !__EXITTILE_H
