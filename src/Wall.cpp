#include "Wall.h"

bool Wall::canEnter() const
{
    return false;
}

Interactions Wall::getInteractionType() const
{
    return Interactions::INVALID;
}
