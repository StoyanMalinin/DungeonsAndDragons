#include "UIHandler.h"

UIHandler::UIHandler(std::istream& is, std::ostream& os) : is(is), os(os)
{}

char UIHandler::requestAttackType(const FightableEntity& you, const FightableEntity& opponent)
{
	os << "you: "; you.writeln(os);
	os << "opponent: "; opponent.writeln(os);

	os << "What kind of attack do you want to perform? (Strength attack(s)/Magic attack(m))" << '\n';
	
	Vector<char> choices;
	choices.pushBack('s');
	choices.pushBack('m');
	return requestCharChoice(choices);
}

char UIHandler::requestItemManagementDecision(const GameItem* oldItem, const GameItem* newItem)
{
	os << "Old item: ";
	if (oldItem == nullptr) os << "none" << '\n';
	else oldItem->writeln(os);

	os << "New item: ";
	if (newItem == nullptr) os << "none" << '\n';
	else newItem->writeln(os);

	os << "Would you like to replace the old item for the new one? (y/n)" << '\n';
	
	Vector<char> choices;
	choices.pushBack('y');
	choices.pushBack('n');
	return requestCharChoice(choices);
}

void UIHandler::writeMessage(const String& s)
{
	os << s << '\n';
}

void UIHandler::readAndParseCommand(Vector<String>& tokens)
{
	String cmd;
	os << ">";
	getline(is, cmd);
	is.get();

	String curr;
	for (size_t i = 0; i < cmd.getLen(); i++)
	{
		if (cmd[i] == ' ')
		{
			if (curr.getLen() != 0) tokens.pushBack(curr);
			curr = "";
		}
		else
		{
			curr += cmd[i];
		}
	}
	if (curr.getLen() != 0) tokens.pushBack(curr);
}

char UIHandler::requestMoveType(const GameMap& mp, const MovableTileEntity& curr)
{
	for (size_t i = 0; i < mp.getN(); i++)
	{
		for (size_t j = 0; j < mp.getM(); j++)
		{
			if (i == curr.getR() && j == curr.getC()) os << curr.getSymbol();
			else os << mp.getCharAt(i, j);
		}
		os << '\n';
	}

	os << "Where do you want to move? (Up(u)/Down(d)/Left(l)/Right(r))" << '\n';

	Vector<char> choices;
	choices.pushBack('u');
	choices.pushBack('d');
	choices.pushBack('l');
	choices.pushBack('r');
	return requestCharChoice(choices);
}

char UIHandler::requestCharChoice(const Vector<char>&validChoices)
{
	while (true)
	{
		os << ">";
		char c;
		is >> c;

		for (size_t i = 0; i < validChoices.getLen(); i++)
			if (validChoices[i] == c) return c;
	}
}
