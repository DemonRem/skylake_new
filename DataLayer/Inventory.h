#ifndef INVENTORY_H
#define INVENTORY_H

#include "../Base/ServerDefs.h"
#include "../Base/typeDefs.h"
#include "../Base/win32.h"

struct Item;
struct Player;

struct ISlot {
	UINT16 id;
	UINT16 bIsEmpty;
	ULONG  flags;

	Item * item;

	inline const bool HasItem() const noexcept {
		return item != nullptr;
	}
};

struct Inventory {
	Player* player;

	ISlot profileSlots[PLAYER_INVENTORY_PROFILE_SLOTS_COUNT];
	ISlot inventorySlots[PLAYER_INVENTORY_MAX_SLOTS];
	ISlot bankSlots[2]; //@TODO get slots count
	

};

#endif
