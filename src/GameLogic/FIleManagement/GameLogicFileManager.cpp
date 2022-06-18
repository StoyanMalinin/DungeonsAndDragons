#include "GameLogicFileManager.h"
#include "PlayerView.h"

Player* GameLogicFileManager::deserializePlayer(std::iostream& stream, const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm)
{
	checkForBadStream(stream);

	PlayerView pv(stream);
	return pv.getPlayer(fc, imc, mc, pdc, iem, fm);
}

WallTile* GameLogicFileManager::deserializeWallTile(std::iostream& stream)
{
	checkForBadStream(stream);

	String s;
	stream >> s;
	if (s != "WallTile") throw std::logic_error("Error while deserializing WallTile! Invalid stream format!");

	int r, c;
	stream >> r >> c;

	return new WallTile(r, c);
}

ExitTile* GameLogicFileManager::deserializeExitTile(std::iostream& stream)
{
	checkForBadStream(stream);

	String s;
	stream >> s;
	if (s != "ExitTile") throw std::logic_error("Error while deserializing ExitTile! Invalid stream format!");

	int r, c;
	stream >> r >> c;

	return new ExitTile(r, c);
}

EmptyTile* GameLogicFileManager::deserializeEmptyTile(std::iostream& stream)
{
	checkForBadStream(stream);

	String s;
	stream >> s;
	if (s != "EmptyTile") throw std::logic_error("Error while deserializing EmptyTile! Invalid stream format!");

	int r, c;
	stream >> r >> c;

	return new EmptyTile(r, c);
}

SpellTreasure* GameLogicFileManager::deserializeSpellTreasure(std::iostream& stream, ItemExchangeMaster &iem)
{
	checkForBadStream(stream);

	String type;
	stream >> type;
	if (type != "SpellTreasure") throw std::logic_error("Error while deserializing SpellTreasure! Invalid stream format!");

	int r, c;
	stream >> r >> c;

	bool isTaken;
	stream >> isTaken;
	Spell spell(stream);

	return new SpellTreasure(r, c, isTaken, iem, spell);
}

ArmorTreasure* GameLogicFileManager::deserializeArmorTreasure(std::iostream& stream, ItemExchangeMaster& iem)
{
	checkForBadStream(stream);

	String type;
	stream >> type;
	if (type != "ArmorTreasure") throw std::logic_error("Error while deserializing ArmorTreasure! Invalid stream format!");

	int r, c;
	stream >> r >> c;

	bool isTaken;
	stream >> isTaken;
	Armor armor(stream);

	return new ArmorTreasure(r, c, isTaken, iem, armor);
}

WeaponTreasure* GameLogicFileManager::deserializeWeaponTreasure(std::iostream& stream, ItemExchangeMaster& iem)
{
	checkForBadStream(stream);

	String type;
	stream >> type;
	if (type != "WeaponTreasure") throw std::logic_error("Error while deserializing WeaponTreasure! Invalid stream format!");

	int r, c;
	stream >> r >> c;

	bool isTaken;
	stream >> isTaken;
	Weapon weapon(stream);

	return new WeaponTreasure(r, c, isTaken, iem, weapon);
}

Treasure* GameLogicFileManager::deserializeTreasure(std::iostream& stream, ItemExchangeMaster& iem)
{
	checkForBadStream(stream);

	size_t pos = stream.tellg();
	String type;
	stream >> type;
	stream.seekg(pos);

	if (type == "WeaponTreasure") return deserializeWeaponTreasure(stream, iem);
	if (type == "SpellTreasure") return deserializeSpellTreasure(stream, iem);
	if (type == "ArmorTreasure") return deserializeArmorTreasure(stream, iem);

	throw std::logic_error("Error while deserializing treasure! Invalid stream format!");
}

void GameLogicFileManager::checkForBadStream(std::iostream& stream)
{
	if (stream.bad() == true)
		throw std::logic_error("Stream is corrupted!");
}
