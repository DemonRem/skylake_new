#ifndef ENCHANTDATATEMPLATE_H
#define ENCHANTDATATEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/EquipmentEnums.h"

struct PassivityCategory;

struct EnchantEffect {
	UINT16 step;
	PassivityCategory *  passivitiesCategory;
};

struct BasicStatEnchant {
	float rate;
	UINT16 enchantStep;
	EBasicStatEnchantKind kind;
};

struct EnchantSet {
	UID id;

	UINT16 effectsCount;
	UINT16 statsCount;
	EnchantEffect*		effects;
	BasicStatEnchant *	stats;
};

#endif
