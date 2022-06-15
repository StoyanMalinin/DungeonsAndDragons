#include "OnlyDownMoveController.h"

MoveController* OnlyDownMoveController::clone() const
{
    return new OnlyDownMoveController(*this);
}

Directions OnlyDownMoveController::getDirection(const MovableTileEntity& entity)
{
    return Directions::DOWN;
}

Directions OnlyDownMoveController::peekDirection(const MovableTileEntity& entity)
{
    return Directions::DOWN;
}
