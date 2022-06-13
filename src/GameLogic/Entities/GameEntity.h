#ifndef __GAMEENTITY_H
#define __GAMEENTITY_H

class GameEntity
{
public:
	virtual void interact(GameEntity *other) = 0;
	virtual void interactInternal(GameEntity *other);

public:
	~GameEntity() = default;
};

#endif

