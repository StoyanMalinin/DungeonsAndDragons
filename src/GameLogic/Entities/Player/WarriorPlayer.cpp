#include "WarriorPlayer.h"

WarriorPlayer::WarriorPlayer(const String& name, int r, int c, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm)
    : Player(name, r, c, 40, 10, 50, fc, imc, mc, pdc, iem, fm)
{}

WarriorPlayer::WarriorPlayer(const String & name, int r, int c, float strength, float mana, float health, float initialHealth, const FightController & fc, const ItemManagerController & imc, const MoveController & mc, const PointsDistributionController & pdc, ItemExchangeMaster & iem, FightMaster & fm)
    : Player(name, r, c, strength, mana, health, initialHealth, fc, imc, mc, pdc, iem, fm)
{}

void WarriorPlayer::serialize(std::ostream & stream) const
{
    stream << 'w';
    serializeRawData(stream);

    if (stream.bad() == true)
        throw std::exception("Error while serializing warrior player, the stream got corrupted!");
}
