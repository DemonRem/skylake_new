#ifndef ITEMENUMS_H
#define ITEMENUMS_H

#include "../TypeDefs.h"

enum EItemCategory : UINT16
{
	EItemCategory_combat,
	EItemCategory_magical,
	EItemCategory_charm,
	EItemCategory_customize_armor,
	EItemCategory_customize_weapon,
	EItemCategory_pkitem,
	EItemCategory_medal,
	EItemCategory_enchant_agent,
	EItemCategory_service,
	EItemCategory_earring,
	EItemCategory_necklace,
	EItemCategory_ring,
	EItemCategory_skillbook,
	EItemCategory_token,
	EItemCategory_order,
	EItemCategory_etc,
	EItemCategory_petAdult,
	EItemCategory_petOrb,
	EItemCategory_dyeItem,
	EItemCategory_dyeRaw,
	EItemCategory_dyeRecipe,
	EItemCategory_dual,
	EItemCategory_lance,
	EItemCategory_twohand,
	EItemCategory_axe,
	EItemCategory_circle,
	EItemCategory_bow,
	EItemCategory_staff,
	EItemCategory_rod,
	EItemCategory_metal,
	EItemCategory_style_hair,
	EItemCategory_enchant_material,
	EItemCategory_weaponMaterial,
	EItemCategory_armorMaterial,
	EItemCategory_keyItem,
	EItemCategory_generalMaterial,
	EItemCategory_fiber,
	EItemCategory_alchemy,
	EItemCategory_leather,
	EItemCategory_alchemyMaterial,
	EItemCategory_fireworkMaterial,
	EItemCategory_recipe,
	EItemCategory_weaponComponent,
	EItemCategory_armorComponent,
	EItemCategory_bodyMail,
	EItemCategory_handMail,
	EItemCategory_feetMail,
	EItemCategory_bodyLeather,
	EItemCategory_handLeather,
	EItemCategory_feetLeather,
	EItemCategory_bodyRobe,
	EItemCategory_handRobe,
	EItemCategory_feetRobe,
	EItemCategory_quest,
	EItemCategory_document,
	EItemCategory_artisan,
	EItemCategory_enchantScroll,
	EItemCategory_brooch,
	EItemCategory_crest,
	EItemCategory_customize_accessory,
	EItemCategory_chain,
	EItemCategory_extractRecipe,
	EItemCategory_belt,
	EItemCategory_blaster,
	EItemCategory_gauntlet,
	EItemCategory_shuriken,
	EItemCategory_accessoryFace,
	EItemCategory_style_blaster,
	EItemCategory_TOKEN,
	EItemCategory_enchantComponent,
	EItemCategory_glaive,
	EItemCategory_style_glaive,
	EItemCategory_style_face,
	EItemCategory_accessoryHair,
	EItemCategory_style_body,
	EItemCategory_style_chain,
	EItemCategory_style_dual,
	EItemCategory_style_lance,
	EItemCategory_style_twohand,
	EItemCategory_style_axe,
	EItemCategory_style_circle,
	EItemCategory_style_bow,
	EItemCategory_style_staff,
	EItemCategory_style_rod,
	EItemCategory_underwear,
	EItemCategory_style_back,
	EItemCategory_style_foot_print,
	EItemCategory_style_gauntlet,
	EItemCategory_style_shuriken,

	EItemEategory_MAX

};

enum EItemRresourceType : UINT16
{
	EItemRresourceType_small,

	EItemRresourceType_MAX
};

enum EItemType : UINT16
{
	EItemType_DISPOSAL,
	EItemType_NO_COMBAT,
	EItemType_CUSTOM,
	EItemType_CHANGE_NAME,
	EItemType_EQUIP_ACCESSORY,
	EItemType_SKILLBOOK,
	EItemType_DUNGEON_COIN,
	EItemType_CHANGE_COLOR_ITEM,
	EItemType_MIX_DISPOSAL,
	EItemType_CHANGE_RACE,
	EItemType_CHANGE_GENDER,
	EItemType_CHANGE_LOOKS,
	EItemType_EQUIP_WEAPON,
	EItemType_DUNGEON_RESET_SCROLL,
	EItemType_RESET_SCROLL,
	EItemType_EQUIP_STYLE_ACCESSORY,
	EItemType_IMMEDIATE,
	EItemType_GACHA,
	EItemType_MEDAL_USEABLE,
	EItemType_ENCHANT_MATERIAL,
	EItemType_RECIPE,
	EItemType_EQUIP_ARMOR_BODY,
	EItemType_EQUIP_ARMOR_ARM,
	EItemType_EQUIP_ARMOR_LEG,
	EItemType_DOCUMENT,
	EItemType_TELEPORT_TO_VILLAGE,
	EItemType_RECOVERY_FATIGUE_POINT,
	EItemType_EnchantScroll,
	EItemType_CREST,
	EItemType_GUILD_TOWER,
	EItemType_CITY_WAR_GUILD_TOWER_TELEPORT,
	EItemType_EQUIP_INHERITANCE,
	EItemType_ENCHANTER,
	EItemType_LOOT_MOTION_ONLY,
	EItemType_EQUIP_STYLE_WEAPON,
	EItemType_TOKEN,
	EItemType_ENCHANT_COMPONENT_WEAPON,
	EItemType_QUEST,
	EItemType_BUILD_OBJECT_NOTICE,
	EItemType_EQUIP_STYLE_BODY,
	EItemType_INC_WAREHOUSE_SLOT,
	EItemType_INC_CHARACTER_EXP,
	EItemType_INC_STYLE_WAREHOUSE_SLOT,
	EItemType_SHARED_INC_STYLE_WAREHOUSE_PAGE,
	EItemType_UNBINDER,
	EItemType_EQUIP_UNDERWEAR,
	EItemType_RAWSTONE,
	EItemType_RENAME_GUILD,
	EItemType_EQUIP_STYLE_BACK,
	EItemType_PREMIUM_RENAME,
	EItemType_INC_INVEN_SLOT,
	EItemType_SOCIALBOOK,
	EItemType_EQUIP_STYLE_EFFECT,
	EItemType_LOCKBOX_KEY,
	EItemType_MEGAPHONE,
	EItemType_SYNTHESIZER,
	EItemType_BOOKMARK,
	EItemType_RESET_EP,
	EItemType_GAIN_EP_POINT,
	EItemType_FloatingCastle_partsstore,

	EItemType_MAX
};

enum EItemBoundType :UINT16 {
	EItemBoundType_NONE = 1,
	EItemBoundType_EQUIP = 2,
	EItemBoundType_LOOT = 3,
	EItemBoundType_EQUIPTOITEM = 4,
	EItemBoundType_NONE_2 = 5,
	EItemBoundType_EQUIP_2 = 6,

	EItemBoundType_MAX
};

enum EItemRareGrade : UINT16
{
	EItemRareGrade_NORMAL = 0,
	EItemRareGrade_UNCOMMON = 1,
	EItemRareGrade_RARE = 2,
	EItemRareGrade_SUPERIOR = 3,

	EItemRareGrade_MAX
};

enum EItemGrade : UINT16
{
	EItemGrade_NORMAL = 0,
	EItemGrade_MASTERWORK = 1,
	EItemGrade_AWAKENED = 2,

	EItemGrade_MAX
};

enum EProfileSlotType : UINT16
{
	EProfileSlotType_WEAPON = 0,
	EProfileSlotType_ARMOR = 2,
	EProfileSlotType_GLOVES = 3,
	EProfileSlotType_BOOTS = 4,
	EProfileSlotType_EARRING_L = 5,
	EProfileSlotType_EARRING_R = 6,
	EProfileSlotType_RING_L = 7,
	EProfileSlotType_RING_R = 8,
	EProfileSlotType_NECKLACE = 9,
	EProfileSlotType_INNERWARE = 10,
	EProfileSlotType_HEAD_ADRONMENT = 11,
	EProfileSlotType_MASK = 12,
	EProfileSlotType_SKIN_HEAD = 13,
	EProfileSlotType_SKIN_FACE = 14,	//good
	EProfileSlotType_SKIN_WEAPON = 15,
	EProfileSlotType_SKIN_BODY = 16,	//good
	EProfileSlotType_SKIN_BACK = 17,	//good
	EProfileSlotType_BELT = 18,
	EProfileSlotType_BROOCH = 19,

	EProfileSlotType_MAX
};

enum EEquipmentPart : UINT16 {
	EEquipmentPart_BODY = 1,
	EEquipmentPart_HAND = 2,
	EEquipmentPart_FEET = 3,
	EEquipmentPart_FINGER = 4,
	EEquipmentPart_NECK = 5,
	EEquipmentPart_BROOCH = 6,
	EEquipmentPart_EAR = 7,
	EEquipmentPart_UNDERWEAR = 8,
	EEquipmentPart_BELT = 9,
	EEquipmentPart_ACCESSORYFACE = 10,
	EEquipmentPart_ACCESSORYHAIR = 11,
	EEquipmentPart_STYLE_FACE = 12,
	EEquipmentPart_STYLE_HAIR = 13,
	EEquipmentPart_STYLE_WEAPON = 14,
	EEquipmentPart_STYLE_BODY = 15,
	EEquipmentPart_STYLE_BACK = 16,

	EEquipmentPart_MAX
};

enum EItemFlags :UINT32 {
	EIFChangeColorEnable = 1 << 0,
	EIFChangeLook = 1 << 1,
	EIFTradable = 1 << 2,
	EIFWarehouseStoreable = 1 << 3,
	EIFDestroyable = 1 << 4,
	EIFDismantlable = 1 << 5,
	EIFSellable = 1 << 6,
	EIFObtainable = 1 << 7,
	EIFEnchantEnable = 1 << 8,
	EIFArtisanable = 1 << 9,
	EIFUseOnlyByGender = 1 << 10,
	EIFUseOnlyTerritory = 1 << 11,
	EIFUseOnlyByRace = 1 << 12,
	EIFHasBonus = 1 << 13,
	EIFBankStorable = 1 << 14,
	EIFGuildBankStorable = 1 << 15,
	EIFUseOnlyByClass = 1 << 16,

	//others come here

	EIFIsNonDB = 1 << 30,
};

#endif