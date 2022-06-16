#ifndef __POINTSDISTRIBUTIONCONTROLLER_H
#define __POINTSDISTRIBUTIONCONTROLLER_H

class PointsDistributionController
{
public:
	PointsDistributionController() = default;
protected:
	PointsDistributionController(const PointsDistributionController& other) = default;

public:
	virtual void distributePoints(float allPoints, float& strength, float& mana, float &health) = 0;
	virtual PointsDistributionController* clone() const = 0;
};

#endif // !__POINTSDISTRIBUTIONCONTROLLER_H

