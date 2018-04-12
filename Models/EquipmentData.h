#ifndef EQUIPMENTDATATEMPLATE_H
#define EQUIPMENTDATATEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/EquipmentEnums.h"

struct PassivityTemplate;

//x64 :  40 bytes out of 64(cache line)
struct EquipmentData
{
	UID	id;

	//max: 1
	const PassivityTemplate * passivityG;

	UINT32	minAttack;
	UINT32	maxAttack;
	UINT32	defense;
	UINT32	impact;
	UINT32	balance;
	UINT32	countOfSlot;
	EEquipmentDataPartType	part;
	EEquipmentDataType type;
};
#endif
