#include "UIMoveController.h"

UIMoveController::UIMoveController(UIHandler& uih, GameMap& mp) : uih(uih), mp(mp), isCached(false)
{}

Directions UIMoveController::getDirection(const MovableTileEntity& entity)
{
    if (isCached == true)
    {
        isCached = false;
        return cachedDirection;
    }

    return char2Direction(uih.requestMoveType(mp, entity));
}

Directions UIMoveController::peekDirection(const MovableTileEntity& entity)
{
    if (isCached == true) return cachedDirection;
    
    isCached = true;
    cachedDirection = char2Direction(uih.requestMoveType(mp, entity));

    return cachedDirection;
}

MoveController* UIMoveController::clone() const
{
    return new UIMoveController(*this);
}

Directions UIMoveController::char2Direction(char c)
{
    if (c == 'u') return Directions::UP;
    if (c == 'd') return Directions::DOWN;
    if (c == 'l') return Directions::LEFT;
    if (c == 'r') return Directions::RIGHT;

    return Directions();
}
