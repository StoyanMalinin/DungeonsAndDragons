#ifndef __GAMEITEM_H
#define __GAMEITEM_H

#include <iostream>
#include "../../../Utils/String.h"

class GameItem
{
private:
	String name;
	size_t level;

protected:
	GameItem(const String& name, size_t level);
	GameItem(std::iostream& stream);

public:
	const String& getName() const;
	size_t getLevel() const;

public:
	virtual void serialize(std::ostream& stream) const;
	void serializeLn(std::ostream &stream) const;

public:
	virtual void write(std::ostream& os) const;
	void writeln(std::ostream& os) const;

protected:
	void checkForError(std::iostream &stream);
};

#endif

