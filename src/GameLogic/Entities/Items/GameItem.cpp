#include "GameItem.h"

GameItem::GameItem(const String& name, size_t level) : name(name), level(level)
{}

GameItem::GameItem(std::iostream & stream)
{
	checkForError(stream);

	size_t nameLen;
	stream >> nameLen;
	checkForError(stream);

	stream.ignore();
	for (size_t i = 0; i < nameLen; i++)
	{
		char c;
		stream.get(c);

		this->name += c;
	}
	checkForError(stream);
	
	stream >> level;
	checkForError(stream);
}

const String& GameItem::getName() const
{
	return name;
}

size_t GameItem::getLevel() const
{
	return level;
}

void GameItem::serialize(std::ostream& stream) const
{
	stream << name.getLen() << " " << name << " " << level;
}

void GameItem::serializeLn(std::ostream& stream) const
{
	serialize(stream);
	stream << '\n';
}

void GameItem::write(std::ostream& os) const
{
	os << "|name: " << name << "|level: " << level;
}

void GameItem::writeln(std::ostream& os) const
{
	write(os);
	os << '\n';
}

void GameItem::checkForError(std::iostream& stream)
{
	if (stream.bad() == true)
		throw std::logic_error("Error while deserializing GameItem! The file is corrupted or in wrong format!");
}
