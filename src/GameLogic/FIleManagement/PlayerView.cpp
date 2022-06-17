#include "PlayerView.h"

#include "../Entities/Player/Player.h"
#include "../Entities/Player/MagePlayer.h"
#include "../Entities/Player/HumanPlayer.h"
#include "../Entities/Player/WarriorPlayer.h"

PlayerView::PlayerView(std::iostream& stream)
{
	deserialize(stream);
}

void PlayerView::deserialize(std::iostream& stream)
{
	checkForError(stream);
	stream >> type;
	if (!(type == 'p' || type == 'w' || type == 'm' || type == 'h')) throw std::logic_error("Error while deserializing player, wrong file format!");

	size_t nameLen;
	stream >> nameLen;
	checkForError(stream);

	stream.ignore();
	for (size_t i = 0; i < nameLen; i++)
	{
		char c;
		stream.get(c);
		name += c;
	}

	stream >> r;
	checkForError(stream);
	stream >> c;
	checkForError(stream);

	stream >> strength;
	checkForError(stream);
	stream >> mana;
	checkForError(stream);
	stream >> health;
	checkForError(stream);

	stream >> initialHealth;
	checkForError(stream);
	stream.ignore();
	
	char c = stream.peek();
	if (c != '!') spell = SharedPtr<Spell>(new Spell(stream));
	else { stream.ignore(); stream.ignore(); }

	c = stream.peek();
	if (c != '!') armor = SharedPtr<Armor>(new Armor(stream));
	else { stream.ignore(); stream.ignore(); }

	c = stream.peek();
	if (c != '!') weapon = SharedPtr<Weapon>(new Weapon(stream));
	else { stream.ignore(); stream.ignore(); }
}

Player* PlayerView::getPlayer(const FightController& fc, const ItemManagerController& imc, const MoveController& mc, const PointsDistributionController& pdc, ItemExchangeMaster& iem, FightMaster& fm) const
{
	Player* res = nullptr;
	if (type == 'p') res = new Player(name, r, c, strength, mana, health, initialHealth, fc, imc, mc, pdc, iem, fm);
	if (type == 'w') res = new WarriorPlayer(name, r, c, strength, mana, health, initialHealth, fc, imc, mc, pdc, iem, fm);
	if (type == 'm') res = new MagePlayer(name, r, c, strength, mana, health, initialHealth, fc, imc, mc, pdc, iem, fm);
	if (type == 'h') res = new HumanPlayer(name, r, c, strength, mana, health, initialHealth, fc, imc, mc, pdc, iem, fm);

	if (res != nullptr)
	{
		if (spell.isNull() == false) res->setSpell(spell);
		if (armor.isNull() == false) res->setArmor(armor);
		if (weapon.isNull() == false) res->setWeapon(weapon);
	}

	return res;
}

void PlayerView::checkForError(std::iostream& stream)
{
	if (stream.bad() == true)
		throw std::exception("Error while deserializing player! Invalid file format or corrupt file!");
}
