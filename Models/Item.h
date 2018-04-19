#ifndef GAME_ITEM_H
#define GAME_ITEM_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/ItemEnums.h"

#include "../Base/win32.h"

struct ItemTemplate;
struct Passivity;

#define ITEM_ACTIVE_PASSIVITIES_MAX_COUNT 18
#define ITEM_BODY_SIZE 40

//!!!DONT CHANCHE A THING HERE, IT WILL BREAK THE ITEM SERIALIZER/DESERIALIZER
struct Item {
	UID				id;  //db_uid

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

	Passivity*		passivities[ITEM_ACTIVE_PASSIVITIES_MAX_COUNT];

	Item() :iTemplate(0) { ZeroMemory(passivities, sizeof(Passivity*) * ITEM_ACTIVE_PASSIVITIES_MAX_COUNT); }

	inline const BOOL HasFlag(const EItemFlags flag) const noexcept {
		return flags & flag;
	}
	inline void AddFlag(const EItemFlags flag) noexcept {
		flags |= flag;
	}
	inline void RemoveFlag(const EItemFlags flag) noexcept {
		flags &= !flag;
	}
	inline const UINT16 PassivitiesCount() const noexcept {
		const Passivity * const* p = passivities;
		UINT16 count = 0;
		while (*p) {
			p++;
		}

		return (UINT16)(p - passivities);
	}
	inline Passivity** ClearPassivities() {
		ZeroMemory(passivities, sizeof(Passivity*) * ITEM_ACTIVE_PASSIVITIES_MAX_COUNT);
		return passivities;
	}
};

#endif
