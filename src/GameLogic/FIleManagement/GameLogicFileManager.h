#ifndef __GAMELOGICFILEMANAGER_H
#define __GAMELOGICFILEMANAGER_H

#include "../Entities/Player/Player.h"
#include "../Entities/Player/MagePlayer.h"
#include "../Entities/Player/HumanPlayer.h"
#include "../Entities/Player/WarriorPlayer.h"

#include <iostream>

class GameLogicFileManager
{
public:
	GameLogicFileManager() = delete;
	GameLogicFileManager(const GameLogicFileManager& other) = delete;
	GameLogicFileManager& operator=(const GameLogicFileManager& other) = delete;
};

#endif // !__GAMELOGICFILEMANAGER_H
