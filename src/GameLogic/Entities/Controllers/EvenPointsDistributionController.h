#ifndef __EVENPOINTSDISTRIBUTIONCONTROLLER_H
#define __EVENPOINTSDISTRIBUTIONCONTROLLER_H

#include "PointsDistributionController.h"

class EvenPointsDistributionController : public PointsDistributionController
{
public:
	EvenPointsDistributionController() = default;
protected:
	EvenPointsDistributionController(const EvenPointsDistributionController& other) = default;

public:
	void distributePoints(float allPoints, float& strength, float& mana, float& health) override;
	PointsDistributionController* clone() const override;
};

#endif // !__EVENPOINTSDISTRIBUTIONCONTROLLER_H
