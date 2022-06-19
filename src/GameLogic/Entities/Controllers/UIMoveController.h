#ifndef __UIMOVECONTROLLER_H
#define __UIMOVECONTROLLER_H

class GameMap;
class UIHandler;
#include "MoveController.h"

class UIMoveController : public MoveController
{
private:
	const GameMap& mp;
	UIHandler& uih;
private:
	bool isCached;
	Directions cachedDirection;

public:
	UIMoveController(UIHandler& uih, const GameMap& mp);

public:
	Directions getDirection(const MovableTileEntity& entity) override;
	Directions peekDirection(const MovableTileEntity& entity) override;

public:
	MoveController* clone() const override;

private:
	static Directions char2Direction(char c);
};

#endif // !__UIMOVECONTROLLER_H
