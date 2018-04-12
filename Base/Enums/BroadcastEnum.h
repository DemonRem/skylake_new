#ifndef BROADCAST_ENUM_H
#define BROADCAST_ENUM_H

#include "../TypeDefs.h"

enum WorldBroadcastType :UINT32 {

	BROADCAST_ALL = 1,
	BROADCAST_VISIBLE = 2,
	BROADCAST_AREA = 3,
	BROADCAST_WORLD = 4,
	BROADCAST_PARTY = 5,
	BROADCAST_RAID = 6,
	BROADCAST_ENEMIES = 7,
	BROADCAST_ALLIES = 8,
	BROADCAST_FRIENDS = 9,
	BROADCAST_GUILD = 10,
};

#endif
