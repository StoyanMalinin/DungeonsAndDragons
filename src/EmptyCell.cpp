#include "EmptyCell.h"

bool EmptyCell::canEnter() const
{
    return true;
}

Interactions EmptyCell::getInteractionType() const
{
    return Interactions::BASIC;
}
