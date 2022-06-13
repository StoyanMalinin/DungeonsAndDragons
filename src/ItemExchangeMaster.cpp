#include "ItemExchangeMaster.h"

#include "Player.h"
#include "Treasure.h"

ItemExchangeMaster::ItemExchangeMaster() : receiver(nullptr), giver(nullptr)
{

}

void ItemExchangeMaster::setReceiver(Player * receiver)
{
	this->receiver = receiver;
	if (checkDone() == true) doInteraction();
}

void ItemExchangeMaster::setGiver(Treasure* giver)
{
	this->giver = giver;
	if (checkDone() == true) doInteraction();
}

bool ItemExchangeMaster::checkDone() const
{
	return receiver!=nullptr && giver!=nullptr;
}

void ItemExchangeMaster::doInteraction()
{
	giver->giveToPlayer(*receiver);
	flush();
}

void ItemExchangeMaster::flush()
{
	receiver = nullptr;
	giver = nullptr;
}

ItemExchangeMaster& ItemExchangeMaster::getGlobalInstance()
{
	static ItemExchangeMaster instace;
	return instace;
}
