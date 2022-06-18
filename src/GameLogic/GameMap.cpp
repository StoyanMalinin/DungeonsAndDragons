#include "GameMap.h"

#include "Entities/WallTile.h"
#include "Entities/ExitTile.h"
#include "Entities/EmptyTile.h"
#include "../Utils/RandomGenerator.h"

#include "Entities/Controllers/RandomFightController.h"

#include "Entities/Items/Treasure.h"
#include "Entities/Items/ArmorTreasure.h"
#include "Entities/Items/WeaponTreasure.h"
#include "Entities/Items/SpellTreasure.h"

#include "ItemExchangeMaster.h"
#include "FightMaster.h"

GameMap::GameMap(MapProperties& mp, size_t seed) : mp(mp)
{
	this->grid = Vector<Vector<SharedPtr<TileEntity>>>(mp.n);
	for (size_t i = 0; i < mp.n; i++)
	{
		this->grid[i] = Vector<SharedPtr<TileEntity>>(mp.m);
		for (size_t j = 0; j < mp.m; j++) grid[i][j] = SharedPtr<TileEntity>(new WallTile(i, j));
	}

	RandomGenerator rnd(seed);
	this->fillBySpacePartitioning(rnd);
	this->addMapComponents(rnd);
}

void GameMap::fillBySpacePartitioning(RandomGenerator& rnd)
{
	partitionSpaceRec(Rectangle(0, mp.n - 1, 0, mp.m - 1), rnd, false, false, 0);
	connectCellToDungeon(0, 0, rnd);
}

void GameMap::connectCellToDungeon(size_t i, size_t j, RandomGenerator &rnd)
{
	if (grid[i][j]->canEnter() == true) return;

	grid[i][j] = SharedPtr<TileEntity>(new EmptyTile(i, j));
	Pair<int, int> p1 = Pair<int, int>(i, j), p2 = p1;

	for (size_t r = 0; r < mp.n; r++)
	{
		for (size_t c = 0; c < mp.m; c++)
		{
			if (grid[i][j]->canEnter() == true)
			{
				p2 = Pair<int, int>(r, c);
				break;
			}
		}
	}

	Vector<Pair<int, int>> path;
	genRadomPathBetweenTwoPoints(p1, p2, Rectangle(0, mp.n - 1, 0, mp.m - 1), path, rnd);

	for(size_t ind = 0;ind<path.getLen();ind++)
		grid[path[ind].first][path[ind].second] = SharedPtr<TileEntity>(new EmptyTile(path[ind].first, path[ind].second));
}

Pair<int, int>  GameMap::partitionSpaceRec(Rectangle scope, RandomGenerator& rnd, bool sideSplit, bool dimensionSplit, size_t depth)
{
	const size_t minPartition = 5;

	size_t nxtStep;
	Vector<size_t> nxtStepOptions;
	
	for (size_t i = 0; i < 1; i++)  nxtStepOptions.pushBack(1);
	if (depth>=2)
	{
		for(size_t i = 0;i<10;i++) nxtStepOptions.pushBack(0);
	}
	if (scope.maxRow - scope.minRow >= minPartition && scope.maxCol - scope.minCol >= minPartition)
	{
		for (size_t i = 0; i < 30; i++) nxtStepOptions.pushBack(2);
	}
	nxtStep = nxtStepOptions[rnd.randIntInRange(0, nxtStepOptions.getLen() - 1)];

	//std::cout << scope << " -> " << nxtStep << " " << nxtStepOptions.getLen() << '\n';

	if (nxtStep == 0) //fill
	{
		Rectangle r = scope.randomSubrectangle(rnd);
		//std::cout << "fill: " << r << '\n';

		for (int i = r.minRow; i <= r.maxRow; i++)
			for (int j = r.minCol; j <= r.maxCol; j++)
				grid[i][j] = SharedPtr<TileEntity>(new EmptyTile(i, j));

		if (dimensionSplit == false)
		{
			if (sideSplit == false) return Pair<int, int>(rnd.randIntInRange(r.minRow, r.maxRow), r.maxCol);
			else return Pair<int, int>(rnd.randIntInRange(r.minRow, r.maxRow), r.minCol);
		}
		else
		{
			if (sideSplit == false) return Pair<int, int>(r.maxRow, rnd.randIntInRange(r.minCol, r.maxCol));
			else return Pair<int, int>(r.minRow, rnd.randIntInRange(r.minCol, r.maxCol));
		}
	}
	else if (nxtStep == 1) //leave
	{
		return Pair<int, int>(scope.maxRow, scope.maxCol);
	}
	else if (nxtStep == 2) //partition
	{
		bool dimension = dimensionSplit ^ 1;//rnd.randBool();

		Pair <int, int> p1, p2;
		Rectangle corridorBoundingBox;

		if (dimension == false)
		{
			int mid = rnd.randIntInRange(scope.minCol+1, scope.maxCol-1);

			p1 = partitionSpaceRec(Rectangle(scope.minRow, scope.maxRow, scope.minCol, mid - 1), rnd, false, dimension, depth+1);
			p2 = partitionSpaceRec(Rectangle(scope.minRow, scope.maxRow, mid + 1, scope.maxCol), rnd, true, dimension, depth+1);
			corridorBoundingBox = Rectangle(scope.minRow, scope.maxRow, p1.second, p2.second);
		}
		else if (dimension == true)
		{
			int mid = rnd.randIntInRange(scope.minRow + 1, scope.maxRow - 1);

			p1 = partitionSpaceRec(Rectangle(scope.minRow, mid - 1, scope.minCol, scope.maxCol), rnd, false, dimension, depth+1);
			p2 = partitionSpaceRec(Rectangle(mid + 1, scope.maxRow, scope.minCol, scope.maxCol), rnd, true, dimension, depth+1);	
			corridorBoundingBox = Rectangle(p1.first, p2.first, scope.minCol, scope.maxCol);
		}

		if (grid[p1.first][p1.second]->canEnter() == false && grid[p2.first][p2.second]->canEnter() == false) 
			return { scope.maxRow, scope.maxCol };
		if (grid[p1.first][p1.second]->canEnter() == true && grid[p2.first][p2.second]->canEnter() == true)
		{
			//std::cout << "scope: " << scope << '\n';
			//std::cout << "generating path || " << "dimension: " << dimension << " || " << p1.first << " " << p1.second << " <> " << p2.first << " " << p2.second << '\n';

			Vector <Pair<int, int>> path;
			genRadomPathBetweenTwoPoints(p1, p2, corridorBoundingBox, path, rnd);
	
			//std::cout << "path is generated" << '\n';

			for (size_t i = 0; i < path.getLen(); i++)
				grid[path[i].first][path[i].second] = SharedPtr<TileEntity>(new EmptyTile(path[i].first, path[i].second));
		}

		bool minOrMax, rowOrCol;
		if (dimensionSplit == false)
		{
			rowOrCol = true;
			if (sideSplit == false) minOrMax = true;
			else minOrMax = false;
		}
		else
		{
			rowOrCol = false;
			if (sideSplit == false) minOrMax = true;
			else minOrMax = false;
		}
		
		for (int iIter = scope.minRow; iIter <= scope.maxRow; iIter++)
		{
			int i = iIter;
			if (rowOrCol == false && minOrMax == true) i = scope.minRow + (scope.maxRow - i);

			for (int jIter = scope.minCol; jIter <= scope.maxCol; jIter++)
			{
				int j = jIter;
				if (rowOrCol == true && minOrMax == true) j = scope.minCol + (scope.maxCol - j);
			
				if (grid[i][j]->canEnter() == true) return { i, j };
			}
		}

		return { scope.maxRow, scope.maxRow };
	}

	return { scope.maxRow, scope.maxRow };
}

void GameMap::genRadomPathBetweenTwoPoints(Pair<int, int> p1, Pair<int, int> p2, const Rectangle& boundingBox, Vector<Pair<int, int>>& path, RandomGenerator& rnd)
{
	//std::cout << "bounding box: " << boundingBox << '\n';

	Vector<Vector<bool>> used(boundingBox.maxRow - boundingBox.minRow + 1);
	for (size_t i = 0; i < used.getLen(); i++)
	{
		used[i] = Vector<bool>(boundingBox.maxCol - boundingBox.minCol + 1);
		for (size_t j = 0; j < used[i].getLen(); j++) used[i][j] = false;
	}

	Vector <Pair<int, int>> currPath;
	randomDfsTo(p1, p2, boundingBox, used, rnd, currPath, path);
}

bool GameMap::randomDfsTo(Pair<int, int> x, Pair<int, int> destination, const Rectangle& boundingBox, Vector<Vector<bool>>& used, RandomGenerator& rnd, Vector<Pair<int, int>>& currPath, Vector<Pair<int, int>>& ansPath)
{
	if (boundingBox.isInside(x.first, x.second) == false) return false;
	used[x.first - boundingBox.minRow][x.second - boundingBox.minCol] = true;

	currPath.pushBack(x);
	if (x == destination)
	{
		ansPath = currPath;
		return true;
	}

	Vector<Pair<int, int>> directions;
	directions.pushBack({ -1, 0 });
	directions.pushBack({ +1, 0 });
	directions.pushBack({ 0, -1 });
	directions.pushBack({ 0, +1 });
	directions.randomShuffle(rnd);

	for (size_t i = 0; i < directions.getLen(); i++)
	{
		Pair<int, int> y = { x.first + directions[i].first, x.second + directions[i].second };

		if (boundingBox.isInside(y.first, y.second) == false) continue;
		if (used[y.first - boundingBox.minRow][y.second - boundingBox.minCol] == false)
		{
			bool res = randomDfsTo(y, destination, boundingBox, used, rnd, currPath, ansPath);
			if (res == true) break;
		}
	}

	currPath.popBack();
	return false;
}

void GameMap::addMapComponents(RandomGenerator& rnd)
{
	Vector<Pair<int, int>> freeSpots;
	for (size_t i = 0; i < mp.n; i++)
		for (size_t j = 0; j < mp.m; j++)
			if (!(i==0 && j==0) && grid[i][j]->canEnter() == true) freeSpots.pushBack({ (int)i, (int)j });
	
	if (freeSpots.getLen() < mp.dragonsCount + mp.treasuresCount + 1)
		throw std::logic_error("Map could not be build!");

	freeSpots.randomShuffle(rnd);
	for (size_t i = 0; i < mp.dragonsCount; i++)
		grid[freeSpots[i].first][freeSpots[i].second] = SharedPtr<TileEntity>(new Dragon(freeSpots[i].first, freeSpots[i].second, mp.dragonStrength, mp.dragonMana, mp.dragonMana, RandomFightController(), FightMaster::getGlobalInstance()));
	for (size_t i = mp.dragonsCount; i < mp.dragonsCount + mp.treasuresCount; i++)
	{
		size_t type = rnd.randIntInRange(0, 2);
		Treasure* t = nullptr;

		if (type == 0) t = new ArmorTreasure(freeSpots[i].first, freeSpots[i].second, ItemExchangeMaster::getGlobalInstance(), Armor("armor from treasure", mp.itemLevel, mp.treasureArmor));
		else if (type == 1) t = new SpellTreasure(freeSpots[i].first, freeSpots[i].second, ItemExchangeMaster::getGlobalInstance(), Spell("spell from treasure", mp.itemLevel, mp.treasureSpell));
		else t = new WeaponTreasure(freeSpots[i].first, freeSpots[i].second, ItemExchangeMaster::getGlobalInstance(), Weapon("weapon from treasure", mp.itemLevel, mp.treasureWeapon));

		grid[freeSpots[i].first][freeSpots[i].second] = SharedPtr<TileEntity>(t);
	}

	grid[freeSpots[mp.dragonsCount + mp.treasuresCount].first][freeSpots[mp.dragonsCount + mp.treasuresCount].second] =
	SharedPtr<TileEntity>(new ExitTile(freeSpots[mp.dragonsCount + mp.treasuresCount].first, freeSpots[mp.dragonsCount + mp.treasuresCount].second));
}

size_t GameMap::getN() const
{
	return mp.n;
}

size_t GameMap::getM() const
{
	return mp.m;
}

char GameMap::getCharAt(size_t i, size_t j) const
{
	if (!(0 <= i && i < mp.n && 0 <= j && j < mp.m)) throw std::logic_error("Invalid map cell requested!");
	
	if (grid[i][j].isNull() == true) return ' ';
	return grid[i][j]->getSymbol();
}

void GameMap::serialize(std::ostream& stream) const
{
	if (mp.n == 0 && mp.m == 0) mp.serialize(stream);
	else mp.serializeLn(stream);

	for (size_t i = 0; i < mp.n; i++)
	{
		for (size_t j = 0; j < mp.m; j++)
		{
			if (!(i == mp.n - 1 && j == mp.m - 1)) grid[i][j]->serializeLn(stream);
			else grid[i][j]->serialize(stream);
		}
	}
}

void GameMap::serializeLn(std::ostream& stream) const
{
	serialize(stream);
	stream << '\n';
}

int GameMap::isInside(int r, int c) const
{
	return (0<=r && r<mp.n && 0<=c && c<mp.m);
}

bool GameMap::canEnter(int r, int c) const
{
	if (isInside(r, c) == false) return false;
	return grid[r][c]->canEnter();
}

Interactions GameMap::doInteraction(TileEntity& te)
{
	if (isInside(te.getR(), te.getC()) == false || canEnter(te.getR(), te.getC()) == false)
		return Interactions::INVALID;

	Interactions res = grid[te.getR()][te.getC()]->getInteractionType();
	te.interact(grid[te.getR()][te.getC()].getRaw());

	return res;
}

void GameMap::debug(std::ostream& os)
{
	os << mp.n << " " << mp.m << '\n';
	for (size_t i = 0; i < mp.n; i++)
	{
		for (size_t j = 0; j < mp.m; j++) os << grid[i][j]->getSymbol();
		os << '\n';
	}
}