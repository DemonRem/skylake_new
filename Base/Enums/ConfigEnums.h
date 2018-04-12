#ifndef CONFIG_ENUMS_H
#define CONFIG_ENUMS_H

#include "../TypeDefs.h"

enum EServerProfile :UINT16 {
	EServerProfile_NONE = 0,
	EServerProfile_LIGHT = 1,
	EServerProfile_NORMAL = 2,
	EServerProfile_MEDIUM = 3,
	EServerProfile_HEAVY = 4,
	EServerProfile_EXTREME_HEAVY = 5,

	EServerProfile_MAX,
};

#endif
