#ifndef __INTERACTIONMASTER_H
#define __INTERACTIONMASTER_H

class InteractionMaster
{
public:
	virtual void flush() = 0;
	virtual void doInteraction() = 0;
};

#endif // !__INTERACTIONMASTER_H

