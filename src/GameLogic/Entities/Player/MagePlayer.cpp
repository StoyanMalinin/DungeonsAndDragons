#include "MagePlayer.h"

MagePlayer::MagePlayer(const String& name, int r, int c, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm)
    : Player(name, r, c, 10, 40, 50, fc, imc, mc, pdc, iem, fm)
{}

MagePlayer::MagePlayer(const String & name, int r, int c, float strength, float mana, float health, float initialHealth, const FightController & fc, const ItemManagerController & imc, const MoveController & mc, const PointsDistributionController & pdc, ItemExchangeMaster & iem, FightMaster & fm)
    : Player(name, r, c, strength, mana, health, initialHealth, fc, imc, mc, pdc, iem, fm)
{}

void MagePlayer::serialize(std::ostream& stream) const
{
    stream << 'm';
    serializeRawData(stream);

    if (stream.bad() == true)
        throw std::exception("Error while serializing mage player, the stream got corrupted!");
}