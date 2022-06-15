#ifndef __MOVABLETILEENTITY_H
#define __MOVABLETILEENTITY_H

#include "../../Utils/SharedPtr.hpp"
#include "../../Utils/Pair.hpp"

#include "TileEntity.h"
#include "Controllers/MoveController.h"

class MovableTileEntity : public TileEntity
{
private:
	SharedPtr<MoveController> mc;

public:
	MovableTileEntity(int r, int c, const MoveController& mc);
protected:
	MovableTileEntity(const MovableTileEntity& other) = default;
public:
	MovableTileEntity& operator=(const MovableTileEntity& other) = delete;
	
public:
	Pair<int, int> peekNxtPosition();
	virtual void move();

private:
	Pair<int, int> calcNewPos(Pair<int, int> pos, Directions dir);
};

#endif // !__MOVABLETILEENTITY_H
