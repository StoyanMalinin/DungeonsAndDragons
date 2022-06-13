#ifndef __ITEMEXCHANGEMASTER_H
#define __ITEMEXCHANGEMASTER_H

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
