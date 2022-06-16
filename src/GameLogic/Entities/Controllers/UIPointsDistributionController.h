#ifndef __UIPOINTSDISTRIBUTIONCONTROLLER_H
#define __UIPOINTSDISTRIBUTIONCONTROLLER_H

#include "../../../UI/UIHandler.h"
#include "PointsDistributionController.h"

class UIPointsDistributionController : public PointsDistributionController
{
private:
	UIHandler& uih;

public:
	UIPointsDistributionController(UIHandler &uih);
protected:
	UIPointsDistributionController(const UIPointsDistributionController& other) = default;

public:
	void distributePoints(float allPoints, float& strength, float& mana, float& health);
	PointsDistributionController* clone() const;
};

#endif // !__UIPOINTSDISTRIBUTIONCONTROLLER_H
