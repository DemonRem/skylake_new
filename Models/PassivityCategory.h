#ifndef PASSIVITYCATEGORYTEMPLATE_H
#define PASSIVITYCATEGORYTEMPLATE_H

#include "../Base/typeDefs.h"

struct Passivity;
struct PassivityCategory
{
	UID id;
	BOOL unchangeable;
	UINT32 passivitiesCount;
	const Passivity * passivities;
};

#endif
