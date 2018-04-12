#ifndef CUSTOMIZINGITEMTEMPLATE_H
#define CUSTOMIZINGITEMTEMPLATE_H

#include <vector>
#include "../Base/typeDefs.h"

struct Passivity;
#define CUSTOMIZING_ITEM_MAX_PASSIVITIES 2
#define CUSTOMIZING_ITEM_TAKE_SLOT 1 //must be checked against the newest DC

struct CusotmizingItem
{
	UID					id;
	float				destroyProbOnDeath;
	//UINT32				takeSlot;	// only 1
	const Passivity *	passivities[CUSTOMIZING_ITEM_MAX_PASSIVITIES];
};
#endif
