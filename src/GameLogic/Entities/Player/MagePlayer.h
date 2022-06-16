#ifndef __MAGEPLAYER_H
#define __MAGEPLAYER_H

#include "Player.h"

class MagePlayer : public Player
{
public:
	MagePlayer(const String& name, int r, int c,
		const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
		ItemExchangeMaster& iem, FightMaster& fm);
};

#endif // !__MAGEPLAYER_H

