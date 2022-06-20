#ifndef __UIHANDLER_H
#define __UIHANDLER_H

#include <iostream>
#include "../Utils/String.h"
#include "../Utils/Vector.hpp"
#include "../Utils/SharedPtr.hpp"

class GameItem;
class FightableEntity;

class MovableTileEntity;
class GameMap;
class Player;

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
	void requestPointsDistribution(float allPoints, float& strength, float& mana, float& health);

public:
	void writeMessage(const String& s);
	void readAndParseCommand(Vector<String>& tokens);

public:
	char requestCharChoice(const Vector<char>& validChoices);
	void requestTextLine(const String& msg, const String& shortMsg, String& txt);
	int requestInt(const String& msg, const String& shortMsg);
};

#endif // !__UIHANDLER_H

