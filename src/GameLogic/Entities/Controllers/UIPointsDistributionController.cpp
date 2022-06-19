#include "UIPointsDistributionController.h"
#include "../../../UI/UIHandler.h"

UIPointsDistributionController::UIPointsDistributionController(UIHandler& uih) : uih(uih)
{}

void UIPointsDistributionController::distributePoints(float allPoints, float& strength, float& mana, float& health)
{
	uih.requestPointsDistribution(allPoints, strength, mana, health);
}

PointsDistributionController* UIPointsDistributionController::clone() const
{
	return new UIPointsDistributionController(*this);
}
