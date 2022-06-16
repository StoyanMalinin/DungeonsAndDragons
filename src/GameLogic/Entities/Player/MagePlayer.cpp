#include "MagePlayer.h"

MagePlayer::MagePlayer(const String& name, int r, int c, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm)
    : Player(name, r, c, 10, 40, 50, fc, imc, mc, pdc, iem, fm)
{}