#include "GameMap.h"

#include "EmptyTile.h"

GameMap::GameMap(size_t n, size_t m)
{
	this->n = n;
	this->m = m;

	this->grid = Vector<Vector<SharedPtr<TileEntity>>>(n);
	for (size_t i = 0; i < n; i++)
	{
		this->grid[i] = Vector<SharedPtr<TileEntity>>(m);
		for (size_t j = 0; j < m; j++) grid[i][j] = SharedPtr<TileEntity>(new EmptyTile(i, j));
	}
}