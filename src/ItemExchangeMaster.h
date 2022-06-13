#ifndef __ITEMEXCHANGEMASTER_H
#define __ITEMEXCHANGEMASTER_H

//#include "Player.h"
//#include "Treasure.h"
#include "InteractionMaster.h"

class Player;
class Treasure;

class ItemExchangeMaster : public InteractionMaster
{
private:
	Player* receiver;
	Treasure* giver;

public:
	ItemExchangeMaster();
	//ItemExchangeMaster(const ItemExchangeMaster& other) = delete;
	//ItemExchangeMaster& operator=(const ItemExchangeMaster& other) = delete;
	
public:
	void setReceiver(Player *receiver);
	void setGiver(Treasure *giver);

private:
	bool checkDone() const;
	void doInteraction() override;

public:
	void flush() override;

public:
	static ItemExchangeMaster& getGlobalInstance();
};

#endif // !__ITEMEXCHANGEMASTER_H
