#ifndef __HUMANPLAYER_H
#define __HUMANPLAYER_H

#include "Player.h"

class HumanPlayer : public Player
{
public:
	HumanPlayer(const String& name, int r, int c,
		        const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
		        ItemExchangeMaster& iem, FightMaster& fm);
};

#endif // !__HUMANPLAYER_H

