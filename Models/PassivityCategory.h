#ifndef PASSIVITYCATEGORYTEMPLATE_H
#define PASSIVITYCATEGORYTEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Random.h"

#include "Passivity.h"

struct PassivityCategory {
	UID id;
	BOOL unchangeable;
	UINT32 passivitiesCount;
	const Passivity * passivities;

	inline const Passivity * GetRandom() {
		if (!passivitiesCount) {
			return nullptr;
		}

		if (passivitiesCount == 1) {
			return passivities;
		}

		LONG rIndex = random_range(0, passivitiesCount - 1);
		return passivities + rIndex;
	}
};

#endif
