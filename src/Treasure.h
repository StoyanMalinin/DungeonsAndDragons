#ifndef __TREASURE_H
#define __TREASURE_H

#include "Player.h"
#include "TileEntity.h"

class Treasure : public TileEntity
{
protected:
	bool isTaken;
public:
	Treasure(int r, int c);
protected:
	Treasure(const Treasure& other) = default;
public:
	virtual Treasure* clone() const = 0;

public:
	virtual bool giveToPlayer(Player &p) = 0;
	bool canEnter() const;
	Interactions getInteractionType() const override;
	char getSymbol() const override;

public:
	virtual ~Treasure() = default;
};

#endif // !__TREASURE_H
