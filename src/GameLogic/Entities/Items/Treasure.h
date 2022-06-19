#ifndef __TREASURE_H
#define __TREASURE_H

#include "../TileEntity.h"

class Player;
class InteractionMaster;
class ItemExchangeMaster;

class Treasure : public TileEntity
{
protected:
	bool isTaken;
	ItemExchangeMaster &iem;

public:
	Treasure(int r, int c, ItemExchangeMaster& iem);
	Treasure(int r, int c, bool isTaken, ItemExchangeMaster& iem);
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
	bool getIsTaken() const;

public:
	void interact(GameEntity* other) override;
	void interactInternal(GameEntity* other) override;

public:
	virtual void serialize(std::ostream& stream) const = 0;
	void serializeLn(std::ostream& stream) const;

public:
	virtual ~Treasure() = default;
};

#endif // !__TREASURE_H
