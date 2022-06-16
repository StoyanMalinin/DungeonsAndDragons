#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const String& name, int r, int c, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm)
    : Player(name, r, c, 30, 20, 50, fc, imc, mc, pdc, iem, fm)
{}
