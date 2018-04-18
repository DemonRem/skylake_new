#ifndef DATA_STORE_H
#define DATA_STORE_H

#include  "../Base/typeDefs.h"

#include "Abnormality.h"
#include "CustomizingItem.h"
#include "EnchantData.h"
#include "EquipmentData.h"
#include "EquipmentSet.h"
#include "PassivityCategory.h"
#include "Passivity.h"

#include "NpcTemplate.h"
#include "ItemTemplate.h"
#include "SkillTemplate.h"
#include "ZoneTemplate.h"

//need update on every new tera DC update [last update 03.2018]
#define MAX_ITEMS_COUNT 80000U 
#define MAX_CUSTOMIZING_ITEMS_COUNT 1100U 
#define MAX_EQUIPMENT_DATA_COUNT 26000U
#define MAX_EQUIPMENT_SET_DATA_COUNT 100U
#define MAX_PASSIVITY_DATA_COUNT 10500U
#define MAX_ENCHANT_SET_DATA_COUNT 500U
#define MAX_PASSIVITY_CATEGORY_DATA_COUNT 500U
#define MAX_ABNORMALITY_DATA_COUNT 7100U

static BOOL										isInit;
static UINT32									passivitiesCount;
static UINT32									passivityCategoriesCount;
static UINT32									abnormalitiesCount;
static UINT32									enchantSetsCount;
static UINT32									equipmentSetDataCount;
static UINT32									equipmentDataCount;
static UINT32									npcTemplatesCount;
static UINT32									customizingItemsCount;
static UINT32									skillsCount;
static UINT32									itemsCount;

static ResourceIndex 							itemTemplatesIndexes[MAX_ITEMS_COUNT];
static ItemTemplate 							itemTemplates[MAX_ITEMS_COUNT];
static ItemTemplateInventoryData 				itemTemplateInventoryData[MAX_ITEMS_COUNT];
static ItemTemplateLinks						itemTemplateLinks[MAX_ITEMS_COUNT];
static ItemTemplatePtrs 						itemTemplatePtrs[MAX_ITEMS_COUNT];
static ItemTemplateStats 						itemTemplateStats[MAX_ITEMS_COUNT];

static ResourceIndex *							skillTemplateIndexs;
static SkillTemplateTargetingsAndActions *		skillTemplateTargetingsAndActions;
static SkillTemplateAttackData *				skillTemplateAttackDatas;
static SkillTemplateBase *						skillTemplateBases;
static SkillTemplate *							skillTemplates;

static ResourceIndex *							npcTemplateIndexes;
static NpcTemplate *							npcTemplates;

static ResourceIndex 							passivitiesIndexes[MAX_PASSIVITY_DATA_COUNT];
static Passivity 								passivities[MAX_PASSIVITY_DATA_COUNT];

static ResourceIndex 							abnormalitiesIndexes[MAX_ABNORMALITY_DATA_COUNT];
static Abnormality 								abnormalities[MAX_ABNORMALITY_DATA_COUNT];

static PassivityCategory 						passivityCategories[MAX_PASSIVITY_CATEGORY_DATA_COUNT];
static EnchantSet 								enchantSets[MAX_ENCHANT_SET_DATA_COUNT];
static EquipmentData 							equipmentData[MAX_EQUIPMENT_DATA_COUNT];
static EquipmentSetData 						equipmentSetData[MAX_EQUIPMENT_SET_DATA_COUNT];
static CusotmizingItem 							cusotmizingItems[MAX_CUSTOMIZING_ITEMS_COUNT];

BOOL InitDataStore();

FORCEINLINE UINT32 GetItemIndex(UID itemId) {
	//@TODO optimize search
	u32for(itemsCount) {
		if (itemTemplatesIndexes[i].id == itemId.id) {
			return itemTemplatesIndexes[i].index;
		}
	}

	return UINT32_MAX;
}

FORCEINLINE UINT32 GetSkillIndex(UID skillId)
{
	//@TODO optimize search
	u32for(skillsCount) {
		if (skillTemplateIndexs[i].id == skillId.id) {
			return skillTemplateIndexs[i].index;
		}
	}

	return UINT32_MAX;
}

FORCEINLINE UINT32 GetNpcIndex(UID Id)
{
	//@TODO optimize search
	u32for(npcTemplatesCount) {
		if (npcTemplateIndexes[i].id == Id.id) {
			return npcTemplateIndexes[i].index;
		}
	}

	return UINT32_MAX;
}

FORCEINLINE UINT32 GetAbnormalityIndex(UID Id)
{
	//@TODO optimize search
	u32for(abnormalitiesCount) {
		if (abnormalitiesIndexes[i].id == Id.id) {
			return abnormalitiesIndexes[i].index;
		}
	}

	return UINT32_MAX;
}

FORCEINLINE UINT32 GetPassivityIndex(UID Id)
{
	//@TODO optimize search
	u32for(passivitiesCount) {
		if (passivitiesIndexes[i].id == Id.id) {
			return passivitiesIndexes[i].index;
		}
	}

	return UINT32_MAX;
}

//inline getters
FORCEINLINE const ItemTemplate* GetItemTemplate(const UINT32 index) {
	if (index >= itemsCount) {
		return nullptr;
	}

	return itemTemplates + index;
}
FORCEINLINE const ItemTemplateLinks* GetItemTemplateInventoryLinks(const UINT32 index) {
	if (index >= itemsCount) {
		return nullptr;
	}

	return itemTemplateLinks + index;
}
FORCEINLINE const ItemTemplateInventoryData* GetItemTemplateInventoryData(const UINT32 index) {
	if (index >= itemsCount) {
		return nullptr;
	}

	return itemTemplateInventoryData + index;
}
FORCEINLINE const ItemTemplatePtrs* GetItemTemplateInventoryPtrs(const UINT32 index) {
	if (index >= itemsCount) {
		return nullptr;
	}

	return itemTemplatePtrs + index;
}
FORCEINLINE const ItemTemplateStats* GetItemTemplateInventoryStats(const UINT32 index) {
	if (index >= itemsCount) {
		return nullptr;
	}

	return itemTemplateStats + index;
}

FORCEINLINE const SkillTemplate* GetSkillTemplate(const UINT32 index)
{
	if (index >= skillsCount) {
		return nullptr;
	}

	return skillTemplates + index;
}
FORCEINLINE const SkillTemplateBase* GetSkillTemplateBase(const UINT32 index)
{
	if (index >= skillsCount) {
		return nullptr;
	}

	return skillTemplateBases + index;
}
FORCEINLINE const SkillTemplateTargetingsAndActions* GetSkillTemplateTAndA(const UINT32 index)
{
	if (index >= skillsCount) {
		return nullptr;
	}

	return skillTemplateTargetingsAndActions + index;
}
FORCEINLINE const SkillTemplateAttackData* GetSkillTemplateAttackData(const UINT32 index)
{
	if (index >= skillsCount) {
		return nullptr;
	}

	return skillTemplateAttackDatas + index;
}

FORCEINLINE const NpcTemplate * GetNpcTemplate(const UINT32 index)
{
	if (index >= npcTemplatesCount) {
		return nullptr;
	}

	return npcTemplates + index;
}
FORCEINLINE const Abnormality * GetAbnormalityTemplate(const UINT32 index)
{
	if (index >= abnormalitiesCount) {
		return nullptr;
	}

	return abnormalities + index;
}
FORCEINLINE const Passivity * GetPassivity(const UINT32 index)
{
	if (index >= passivitiesCount) {
		return nullptr;
	}

	return passivities + index;
}

//direct inline getters
FORCEINLINE const PassivityCategory * GetPassivityCategory(UID uid)
{
	//@TODO optimize search

	u32for(passivityCategoriesCount) {
		if (passivityCategories[i].id == uid) {
			return passivityCategories + i;
		}
	}

	return nullptr;
}
FORCEINLINE const EnchantSet * GetEnchantSet(UID uid)
{
	//@TODO optimize search

	u32for(enchantSetsCount) {
		if (enchantSets[i].id == uid) {
			return enchantSets + i;
		}
	}

	return nullptr;
}
FORCEINLINE const EquipmentData * GetEquipmentData(UID uid)
{
	//@TODO optimize search

	u32for(equipmentDataCount) {
		if (equipmentData[i].id == uid) {
			return equipmentData + i;
		}
	}

	return nullptr;
}
FORCEINLINE const EquipmentSetData * GetEquipmentSetData(UID uid)
{
	//@TODO optimize search

	u32for(equipmentSetDataCount) {
		if (equipmentSetData[i].id == uid) {
			return equipmentSetData + i;
		}
	}

	return nullptr;
}
FORCEINLINE const CusotmizingItem * GetCusotmizingItem(UID uid)
{
	//@TODO optimize search

	u32for(customizingItemsCount) {
		if (cusotmizingItems[i].id == uid) {
			return cusotmizingItems + i;
		}
	}

	return nullptr;
}

FORCEINLINE const BOOL IsDataStoreInit()
{
	return isInit;
}

#endif
