#ifndef __UIHANDLER_H
#define __UIHANDLER_H

#include <iostream>
#include "../Utils/String.h"
#include "../Utils/Vector.hpp"
#include "../Utils/SharedPtr.hpp"

#include "../GameLogic/Entities/Items/GameItem.h"
#include "../GameLogic/Entities/FightableEntity.h"

#include "../GameLogic/GameMap.h"
#include "../GameLogic/Entities/Player.h"

enum class UIStates
{
	IN_GAME,
	CONTROL_PANEL,
};

class UIHandler
{
private:
	std::istream& is;
	std::ostream& os;

public:
	UIHandler(std::istream& is, std::ostream& os);
	UIHandler(const UIHandler& other) = delete;
	UIHandler& operator =(const UIHandler& other) = delete;

public:
	char requestMoveType(const GameMap& mp, const MovableTileEntity& p);
	char requestAttackType(const FightableEntity &you, const FightableEntity &opponent);
	char requestItemManagementDecision(const GameItem* oldItem, const GameItem* newItem);

public:
	void writeMessage(const String& s);

private:
	char requestCharChoice(const Vector<char>& validChoices);
};

#endif // !__UIHANDLER_H

