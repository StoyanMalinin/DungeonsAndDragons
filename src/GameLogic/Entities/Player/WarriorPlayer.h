#ifndef __WARIORPLAYER_H
#define __WARIORPLAYER_H

#include "Player.h"

class WarriorPlayer : public Player
{
public:
	WarriorPlayer(const String& name, int r, int c,
	              const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
	              ItemExchangeMaster& iem, FightMaster& fm);
	WarriorPlayer(const String& name, int r, int c, float strength, float mana, float health, float initialHealth,
		          const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
		          ItemExchangeMaster& iem, FightMaster& fm);

public:
	void serialize(std::ostream &stream) const override;
	TileEntity* clone() const override;
};

#endif // !__WARIORPLAYER_H

