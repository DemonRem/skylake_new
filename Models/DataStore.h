#ifndef DATA_STORE_H
#define DATA_STORE_H

#include  "../Base/typeDefs.h"

#define STORE_TYPE_WORLD 0
#define STORE_TYPE_ARBITER_SERVER 1

struct ItemTemplate;
struct ItemTemplateLinks;
struct ItemTemplateInventoryData;
struct ItemTemplatePtrs;
struct ItemTemplateStats;
struct SkillTemplate;
struct SkillTemplateBase;
struct SkillTemplateTargetingsAndActions;
struct SkillTemplateAttackData;
struct NpcTemplate;
struct Abnormality;
struct PassivityCategory;
struct Passivity;
struct EnchantSet;
struct EquipmentData;
struct EquipmentSetData;
struct CusotmizingItem;

BOOL InitDataStore();

const UINT32 GetItemIndex(const UID Id);
const UINT32 GetSkillIndex(const UID Id);
const UINT32 GetNpcIndex(const UID Id);
const UINT32 GetAbnormalityIndex(const UID Id);
const UINT32 GetPassivityIndex(const UID Id);

//inline getters
FORCEINLINE const ItemTemplate* GetItemTemplate(const UINT32 index);
FORCEINLINE const ItemTemplateLinks* GetItemTemplateInventoryLinks(const UINT32 index);
FORCEINLINE const ItemTemplateInventoryData* GetItemTemplateInventoryData(const UINT32 index);
FORCEINLINE const ItemTemplatePtrs* GetItemTemplateInventoryPtrs(const UINT32 index);
FORCEINLINE const ItemTemplateStats* GetItemTemplateInventoryStats(const UINT32 index);

FORCEINLINE const SkillTemplate* GetSkillTemplate(const UINT32 index);
FORCEINLINE const SkillTemplateBase* GetSkillTemplateBase(const UINT32 index);
FORCEINLINE const SkillTemplateTargetingsAndActions* GetSkillTemplateTAndA(const UINT32 index);
FORCEINLINE const SkillTemplateAttackData* GetSkillTemplateAttackData(const UINT32 index);

FORCEINLINE const NpcTemplate * GetNpcTemplate(const UINT32 index);
FORCEINLINE const Abnormality * GetAbnormalityTemplate(const UINT32 index);
FORCEINLINE const Passivity * GetPassivity(const UINT32 index);

//direct inline getters
FORCEINLINE const PassivityCategory * GetPassivityCategory(const UID uid);
FORCEINLINE const EnchantSet * GetEnchantSet(const UID uid);
FORCEINLINE const EquipmentData * GetEquipmentData(const UID uid);
FORCEINLINE const EquipmentSetData * GetEquipmentSetData(const UID uid);
FORCEINLINE const CusotmizingItem * GetCusotmizingItem(const UID uid);

FORCEINLINE const BOOL IsDataStoreInit();

#endif
