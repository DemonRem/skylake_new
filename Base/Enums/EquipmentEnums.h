#ifndef EQUIPMENTENUMS_H
#define EQUIPMENTENUMS_H

#include "../TypeDefs.h"

enum EBasicStatEnchantKind : UINT16
{
	attack = 1,
	impact,
	defence,
	balance,
};

enum EEquipmentDataType : UINT16 {
	EEquipmentDataType_DUAL,
	EEquipmentDataType_LANCE,
	EEquipmentDataType_TWOHAND,
	EEquipmentDataType_AXE,
	EEquipmentDataType_CIRCLE,
	EEquipmentDataType_BOW,
	EEquipmentDataType_STAFF,
	EEquipmentDataType_ROD,
	EEquipmentDataType_CHAIN,
	EEquipmentDataType_BLASTER,
	EEquipmentDataType_GAUNTLET,
	EEquipmentDataType_SHURIKEN,
	EEquipmentDataType_GLAIVE,
	EEquipmentDataType_MAIL,
	EEquipmentDataType_LEATHER,
	EEquipmentDataType_ROBE,
	EEquipmentDataType_RING,
	EEquipmentDataType_NECKLACE,
	EEquipmentDataType_BROOCH,
	EEquipmentDataType_EARRING,
	EEquipmentDataType_UNDERWEAR,
	EEquipmentDataType_BELT,
	EEquipmentDataType_ACCESSORYHAIR,
	EEquipmentDataType_ACCESSORYFACE,
	EEquipmentDataType_STYLE,
	EEquipmentDataType_MAX
};

enum EEquipmentDataPartType : UINT16 {
	EEquipmentDataPartType_Weapon,
	EEquipmentDataPartType_BODY,
	EEquipmentDataPartType_HAND,
	EEquipmentDataPartType_FEET,
	EEquipmentDataPartType_FINGER,
	EEquipmentDataPartType_NECK,
	EEquipmentDataPartType_BROOCH,
	EEquipmentDataPartType_EAR,
	EEquipmentDataPartType_UNDERWEAR,
	EEquipmentDataPartType_BELT,
	EEquipmentDataPartType_ACCESSORYHAIR,
	EEquipmentDataPartType_ACCESSORYFACE,
	EEquipmentDataPartType_STYLE_FACE,
	EEquipmentDataPartType_STYLE_HAIR,
	EEquipmentDataPartType_STYLE_WEAPON,
	EEquipmentDataPartType_STYLE_BODY,
	EEquipmentDataPartType_STYLE_BACK,
	EEquipmentDataPartType_STYLE_EFFECT,
};

#endif
