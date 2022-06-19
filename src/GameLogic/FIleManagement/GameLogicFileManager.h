#ifndef __GAMELOGICFILEMANAGER_H
#define __GAMELOGICFILEMANAGER_H

#include "../Entities/Player/Player.h"
#include "../Entities/Player/MagePlayer.h"
#include "../Entities/Player/HumanPlayer.h"
#include "../Entities/Player/WarriorPlayer.h"

//#include "../Level.h"
#include "../Entities/Dragon.h"
#include "../Entities/WallTile.h"
#include "../Entities/ExitTile.h"
#include "../Entities/EmptyTile.h"
#include "../Entities/Items/SpellTreasure.h"
#include "../Entities/Items/ArmorTreasure.h"
#include "../Entities/Items/WeaponTreasure.h"

#include <iostream>

class Level;

class GameLogicFileManager
{
public:
	GameLogicFileManager() = delete;
	GameLogicFileManager(const GameLogicFileManager& other) = delete;
	GameLogicFileManager& operator=(const GameLogicFileManager& other) = delete;

public:
	static Player* deserializePlayer(std::iostream& stream, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm);
	static WallTile* deserializeWallTile(std::iostream& stream);
	static ExitTile* deserializeExitTile(std::iostream& stream);
	static EmptyTile* deserializeEmptyTile(std::iostream& stream);
	static SpellTreasure* deserializeSpellTreasure(std::iostream& stream, ItemExchangeMaster& iem);
	static ArmorTreasure* deserializeArmorTreasure(std::iostream& stream, ItemExchangeMaster& iem);
	static WeaponTreasure* deserializeWeaponTreasure(std::iostream& stream, ItemExchangeMaster& iem);
	static Treasure* deserializeTreasure(std::iostream& stream, ItemExchangeMaster& iem);
	static Dragon* deserializeDragon(std::iostream& stream, const FightController& fc, FightMaster& fm);
	static Level* deserializeLevel(std::iostream& stream);

private:
	static void checkForBadStream(std::iostream& stream);
};

#endif // !__GAMELOGICFILEMANAGER_H
