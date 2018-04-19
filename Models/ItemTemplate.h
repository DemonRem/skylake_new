#ifndef ITEMTEMPLATE_H
#define ITEMTEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/ItemEnums.h"
#include "../Base/Enums/PlayerEnum.h"

#define ITEM_MAX_PASSIVITIES 16

struct PassivityTemplate;
struct PassivityCategory;
struct CusotmizingItem;
struct EquipmentData;
struct EquipmentSetData;
struct EnchantSet;

struct ItemTemplate {
	UINT32		id;
	UINT32		index;
	UINT32		maxStack;

	EItemTemplateFlags	itemFlags;

	EItemBoundType		bind_type;
	EEquipmentPart		part;
	EItemType			combatItemType;
	EItemCategory		category;
	EItemType			type;
	EItemType			requiredEquipmentType;
	EItemGrade			itemGrade;
	EItemRareGrade		rareGrade;

	float masterpieceRate;

	inline const BOOL HasFlag(const EItemTemplateFlags flag) const noexcept {
		return itemFlags & flag;
	}

	inline const BOOL HasFlags(const FLAG16 flags) const noexcept {
		return itemFlags & flags;
	}
};

struct ItemTemplateInventoryData {
	UINT64		id;

	FLAG		requiredClasses;
	FLAG16		requiredRaces;
	FLAG16		requiredGenders;

	INT16		requiredLevel;
	INT16		enchantLevel;
	INT16		rank;
	INT16		sortingNumber;
	INT16		slotLimit;
	INT16		countOfSlot;
	INT16		coolTime;
	INT16		crystalCount;
	INT16		coolTimeGroup;
	INT16		unidentifyItemGrade;

	const BOOL AcceptsClass(const EPlayerClass classE) const noexcept {
		return requiredClasses & classE;
	}

	const BOOL AcceptsRace(const EPlayerRace race) const noexcept {
		return requiredRaces & race;
	}

	const BOOL AcceptsGender(const EPlayerGender gender) const noexcept {
		return requiredGenders & gender;
	}
};

struct ItemTemplatePtrs {
	PassivityCategory * masterpiecePassivityCategory;
	PassivityCategory * passivityCategory;
	CusotmizingItem * customizingItem;
	EquipmentSetData * equipmentSetData;
	EquipmentData  * equipmentData;

	// if enchatLevel <= 9 [_enchant] else if enchantLeve >=10 [_masterpieceEnchant]
	EnchantSet * enchant;
	EnchantSet * masterpieceEnchant;

	// if enchatLevel <= 9 [_passivities] else if enchantLeve >=10 [_masterpiecePassivities]
	PassivityTemplate * passivities[ITEM_MAX_PASSIVITIES]; //satic passivities
	PassivityTemplate * masterpiecePassivities[32]; //satic msterwork passivities
};

struct ItemTemplateStats {

	INT32		minAtk;
	INT32		maxAtk;
	INT32		impact;
	INT32		def;
	INT32		buyPrice;
	INT32		sellPrice;
};

struct ItemTemplateLinks {

	UINT32	passivityLinkG;
	UINT32	linkCrestId;
	UINT32	linkLookInfoId;
	UINT32	linkPetAdultId;
	UINT32	linkPetOrbId;
	UINT32	linkSkillId;

	//@TODO resolve links methods here
};

#endif
