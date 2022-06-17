#include "UIHandler.h"

#include <cmath>

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

void UIHandler::requestPointsDistribution(float allPoints, float& strength, float& mana, float& health)
{
	os << "Please enter a way to distribute " << allPoints << " points between strength/mana/health" << '\n';
	while (true)
	{
		os << "(enter three nonnegative numbers)>";
		float inStregth, inMana, inHealth;

		is >> inStregth >> inMana >> inHealth;
		if (inStregth < 0 || inMana < 0 || inHealth < 0)
		{
			os << "The numbers must be nonnegative!" << '\n';
		}
		else if (fabs(allPoints - (inStregth + inMana + inHealth)) > 0.000001f)
		{
			os << "The numbers must sum up to " << allPoints << "!" << '\n';
		}
		else
		{
			strength = inStregth;
			mana = inMana;
			health = inHealth;

			break;
		}
	}

}

void UIHandler::writeMessage(const String& s)
{
	os << s << '\n';
}

void UIHandler::readAndParseCommand(Vector<String>& tokens)
{
	String cmd;
	os << ">";
	
	while (is.peek() == '\n')
	{
		is.ignore();
		os << ">";
	}
	
	getline(is, cmd);
	is.ignore();

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
		is.ignore();

		for (size_t i = 0; i < validChoices.getLen(); i++)
			if (validChoices[i] == c) return c;
	}
}

void UIHandler::requestTextLine(const String& msg, const String& shortMsg, String& txt)
{
	os << msg << '\n';
	os << shortMsg << ">";
	while (is.peek() == '\n')
	{
		is.ignore();
		os << shortMsg << ">";
	}
	
	getline(is, txt);
	is.ignore();
}

int UIHandler::requestInt(const String& msg, const String& shortMsg)
{
	os << msg << '\n';
	os << shortMsg << ">";
	
	int x;
	is >> x;

	return x;
}
