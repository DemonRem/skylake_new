#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/ItemEnums.h"

struct ItemTemplate;
struct Passivity;

#define ITEM_MAX_PASSIVITIES 16
#define ITEM_SIZE 

//!!!DONT CHANCHE A THING HERE, IT WILL BREAK THE DB-SERIALIZER
struct Item {
	UID				id;

	// SERIALIZER _START
	INT32			stackCount;
	INT32			crystals[4];
	UINT32			binderDBId;
	UINT32			crafterDBId;
	INT32			itemLevel;
	ULONG			flags;
	float			masterworkRate;
	// SERIALIZER _END [40 bytes]

	ItemTemplate *	iTemplate;

	Passivity*		passivities[ITEM_MAX_PASSIVITIES];

	inline const BOOL HasFlag(const EItemFlags flag) const noexcept {
		return flags & flag;
	}
	inline void AddFlag(const EItemFlags flag) noexcept {
		flags |= flag;
	}
	inline void RemoveFlag(const EItemFlags flag) noexcept {
		flags &= !flag;
	}

	Item() :iTemplate(0) { memset(passivities, 0, sizeof(Passivity*) * ITEM_MAX_PASSIVITIES); }
};

#endif
