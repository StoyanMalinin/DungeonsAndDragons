#include "EvenPointsDistributionController.h"

void EvenPointsDistributionController::distributePoints(float allPoints, float& strength, float& mana, float& health)
{
    strength = allPoints / 3;
    mana = allPoints / 3;
    health = allPoints / 3;
}

PointsDistributionController* EvenPointsDistributionController::clone() const
{
    return new EvenPointsDistributionController(*this);
}
