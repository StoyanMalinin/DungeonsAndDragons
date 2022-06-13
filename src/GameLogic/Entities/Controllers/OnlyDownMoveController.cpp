#include "OnlyDownMoveController.h"

MoveController* OnlyDownMoveController::clone() const
{
    return new OnlyDownMoveController(*this);
}

Directions OnlyDownMoveController::getDirection()
{
    return Directions::DOWN;
}

Directions OnlyDownMoveController::peekDirection()
{
    return Directions::DOWN;
}
