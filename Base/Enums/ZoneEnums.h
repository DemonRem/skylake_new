#ifndef ZONE_ENUMS_H
#define ZONE_ENUMS_H

#include "../typeDefs.h"

enum EZoneFlags : UINT16 {
	EZoneFlags_RestExpBonus = 1 << 0,
	EZoneFlags_Ride = 1 << 1,
	EZoneFlags_Maze = 1 << 2,
	EZoneFlags_Vender = 1 << 3,
	EZoneFlags_Pk = 1 << 4,
	EZoneFlags_PcMoveCylinder = 1 << 5,
	EZoneFlags_IgnoreObstacleShortTel = 1 << 6,
	EZoneFlags_Pad = 1 << 8
};

#endif