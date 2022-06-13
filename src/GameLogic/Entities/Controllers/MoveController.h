#ifndef __MOVECONTROLLER_H
#define __MOVECONTROLLER_H

enum class Directions
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class MoveController
{
public:
	virtual Directions getDirection() = 0;
	virtual Directions peekDirection() = 0;

public:
	MoveController() = default;
protected:
	MoveController(const MoveController& other) = default;

public:
	virtual MoveController* clone() const = 0;
};

#endif // !__MOVECONTROLLER_H
