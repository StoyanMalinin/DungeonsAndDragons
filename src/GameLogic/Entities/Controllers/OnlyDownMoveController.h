#ifndef __ONLYDOWNMOVECONTROLLER_H
#define __ONLYDOWNMOVECONTROLLER_H

#include "MoveController.h"

class OnlyDownMoveController : public MoveController
{
public:
	OnlyDownMoveController() = default;
protected:
	OnlyDownMoveController(const OnlyDownMoveController& other) = default;

public:
	MoveController* clone() const override;
	Directions getDirection() override;
	Directions peekDirection() override;
};

#endif // !__ONLYDOWNMOVECONTROLLER_H

