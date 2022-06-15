#ifndef __MOVECONTROLLER_H
#define __MOVECONTROLLER_H

class MovableTileEntity;

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
	virtual Directions getDirection(const MovableTileEntity& entity) = 0;
	virtual Directions peekDirection(const MovableTileEntity& entity) = 0;

public:
	MoveController() = default;
protected:
	MoveController(const MoveController& other) = default;

public:
	virtual MoveController* clone() const = 0;

public:
	virtual ~MoveController() = default;
};

#endif // !__MOVECONTROLLER_H
