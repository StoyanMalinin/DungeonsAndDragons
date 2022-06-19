#ifndef __MAGEPLAYER_H
#define __MAGEPLAYER_H

#include "Player.h"

class MagePlayer : public Player
{
public:
	MagePlayer(const String& name, int r, int c,
		       const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
		       ItemExchangeMaster& iem, FightMaster& fm);
	MagePlayer(const String& name, int r, int c, float strength, float mana, float health, float initialHealth,
		       const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc,
		       ItemExchangeMaster& iem, FightMaster& fm);

public:
	void serialize(std::ostream& stream) const override;
	TileEntity* clone() const override;
};

#endif // !__MAGEPLAYER_H

