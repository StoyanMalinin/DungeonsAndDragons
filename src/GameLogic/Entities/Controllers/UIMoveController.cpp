#include "UIMoveController.h"

#include "../../GameMap.h"
#include "../../../UI/UIHandler.h"

#include "MoveController.h"
#include "../MovableTileEntity.h"

UIMoveController::UIMoveController(UIHandler& uih, const GameMap& mp) : uih(uih), mp(mp), isCached(false)
{}

Directions UIMoveController::getDirection(const MovableTileEntity& entity)
{
    Directions dir;
    while (true)
    {
        dir = char2Direction(uih.requestMoveType(mp, entity));

        int r = entity.getR();
        int c = entity.getC();

        if (dir == Directions::UP) r--;
        else if (dir == Directions::DOWN) r++;
        else if (dir == Directions::LEFT) c--;
        else if (dir == Directions::RIGHT) c++;

        if (mp.isInside(r, c) == false) uih.writeMessage("You are getting outside the map!");
        else if (mp.canEnter(r, c) == false) uih.writeMessage("Cannot enter this cell!");
        else break;
    }

    return dir;
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
