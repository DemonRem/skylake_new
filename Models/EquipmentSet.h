#ifndef EQUIPMENTSETTEMPLATE_H
#define EQUIPMENTSETTEMPLATE_H

#define ITEM_DELEGATOR_NAME_MAX_LEN 32
#define EQUIPMENT_SET_EFFECT_MAX_PASSIVITIES 4
#define EQUIPMENT_SET_MAX_EFFECTS 4
#define EQUIPMENT_SET_MAX_ITEMS 5

#include "../Base/typeDefs.h"

#include <vector>

struct ItemTemplateIndex;
struct PassivityTemplateIndex;

//effects available for items from same set
struct EquipmentSetEffect
{
	UINT32 countOfEquipment;
	UINT16 passivitiesCount;
	const  PassivityTemplateIndex  * passivities[EQUIPMENT_SET_EFFECT_MAX_PASSIVITIES];
};

//items in the set and for slot
struct EquipmentSetItem
{
	UINT32 slotId;
	//indices direct into the items arrays
	UINT32 indicesCount;
	const UINT32 * itemsIndices; //avg cout : 7 , max count : 117
	char itemDelegatorName[ITEM_DELEGATOR_NAME_MAX_LEN];
};

//the item set, ex: [weap, chest, gloves, boots , belt][#setName]
struct EquipmentSetData {
	UID id;

	UINT16 effectsCount;
	UINT16 itemsCount;
	const EquipmentSetEffect* effects[EQUIPMENT_SET_MAX_EFFECTS];
	const EquipmentSetItem* items[EQUIPMENT_SET_MAX_ITEMS];
};

#endif
