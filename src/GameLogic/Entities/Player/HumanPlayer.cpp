#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(const String& name, int r, int c, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm)
    : Player(name, r, c, 30, 20, 50, fc, imc, mc, pdc, iem, fm)
{}

HumanPlayer::HumanPlayer(const String & name, int r, int c, float strength, float mana, float health, float initialHealth, const FightController & fc, const ItemManagerController & imc, const MoveController & mc, const PointsDistributionController & pdc, ItemExchangeMaster & iem, FightMaster & fm)
    : Player(name, r, c, strength, mana, health, fc, imc, mc, pdc, iem, fm)
{}

void HumanPlayer::serialize(std::ostream& stream) const
{
    stream << 'h';
    serializeRawData(stream);

    if (stream.bad() == true)
        throw std::exception("Error while serializing human player, the stream got corrupted!");
}

TileEntity* HumanPlayer::clone() const
{
    return new HumanPlayer(*this);
}
