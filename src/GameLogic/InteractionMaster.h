#ifndef __INTERACTIONMASTER_H
#define __INTERACTIONMASTER_H

class InteractionMaster
{
public:
	InteractionMaster() = default;
	InteractionMaster(const InteractionMaster& other) = delete;
	InteractionMaster& operator=(const InteractionMaster& other) = delete;


public:
	virtual void flush() = 0;
	virtual void doInteraction() = 0;
};

#endif // !__INTERACTIONMASTER_H

