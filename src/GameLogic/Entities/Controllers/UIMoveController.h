#ifndef __UIMOVECONTROLLER_H
#define __UIMOVECONTROLLER_H

#include "../../../UI/UIHandler.h"
#include "MoveController.h"

#include "../../GameMap.h"

class UIMoveController : public MoveController
{
private:
	GameMap& mp;
	UIHandler& uih;
private:
	bool isCached;
	Directions cachedDirection;

public:
	UIMoveController(UIHandler& uih, GameMap& mp);

public:
	Directions getDirection(const MovableTileEntity& entity) override;
	Directions peekDirection(const MovableTileEntity& entity) override;

public:
	MoveController* clone() const override;

private:
	static Directions char2Direction(char c);
};

#endif // !__UIMOVECONTROLLER_H
