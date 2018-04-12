#ifndef AREATEMPLATE_H
#define AREATEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/ZoneEnums.h"

struct ZoneTempalte
{
	EZoneFlags flags;

	INT32	continentId;
	INT32	worldMapWorldId;
	INT32	worldMapGuardId;
	INT32	worldMapSectionId;
	INT32	huntingZoneId;
	INT32	priority;
	INT32	campId;
	INT32	maxPlayerCount;
	INT32	floor;
	
	float	substractMinZ;
	float	addMaxZ;

	char* name;
	//std::vector<float[3]> fences;

	const BOOL HasFlag(const EZoneFlags flag) const noexcept {
		return flags & flag;
	}
};

#endif
