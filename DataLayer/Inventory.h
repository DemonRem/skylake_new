#ifndef INVENTORY_H
#define INVENTORY_H

#include "../Base/ServerDefs.h"
#include "../Base/typeDefs.h"
#include "../Base/win32.h"
#include "../Models/Item.h"
#include "../Models/ItemTemplate.h"
#include "../Config/ArbiterConfig.h"
#include "../DataLayer/ItemsDBO.h"

#include "../contrib/mysql/include/mysql_connection.h"

struct Player;
struct ConnectionNetPartial;

struct ISlot {
	UINT16 id;
	ULONG  flags;

	Item * item;

	inline const bool IsEmpty() const noexcept {
		return item == nullptr;
	}

	inline void Clear() noexcept {
		if (IsEmpty()) {
			flags = 0;
			return;
		}

		delete item;
		item = nullptr;
		flags = 0;
	}
};

struct Inventory {
	Player* player;
	CRITICAL_SECTION invLock;

	UINT64 gold;
	UINT64 bankGold;
	UINT32 profileItemLevel;
	UINT16 slotsCount;
	UINT16 bankSlotsCount;

	ISlot profileSlots[PLAYER_INVENTORY_PROFILE_SLOTS_COUNT];
	ISlot inventorySlots[PLAYER_INVENTORY_MAX_SLOTS];
	ISlot bankSlots[2]; //@TODO get slots count

	inline void lock() {
		EnterCriticalSection(&invLock);
	}
	inline void unlock() {
		LeaveCriticalSection(&invLock);
	}

	INT32 Init();

	INT32 InsertNonDb(UINT32 itemId, UINT32 stackCount);
	INT32 InsertNonDb(Item * item);
	INT32 StackNonDb(UINT32 itemId, INT32 stackCount);
	INT32 DestroyNonDbStack(UINT32 itemId, INT32 stackCount);
	INT32 Insert(Item* item);
	INT32 InsertProfile(Item* item, UINT16 slotId);
	Item* ExtractItem(UINT32 itemId);
	Item* ExtractItemNoRemove(UINT32 itemId);
	Item* ExtractItemNoRemove(UINT64 itemDbId);
	Item* ExtractSlot(UINT16 slotId);
	INT32 EquipeItem(UINT16 slotId, sql::Connection * sql);
	INT32 UnequipeItem(UINT16 slotId, sql::Connection * sql);
	INT32 EquipeCrystal(UINT16 profileSlotId, UINT16 slotId, sql::Connection * sql);
	INT32 UnequipeCrystal(UINT16 profileSlotId, UINT64 itemId, sql::Connection * sql);

	INT32 Send(ConnectionNetPartial * net, bool show, bool safe);
	INT32 SendItemLevels();
	INT32 Clear();
	INT32 Clear(sql::Connection* sql);

	inline Item* GetProfileItem(UINT16 slotId) const noexcept {
		return (((slotId) >= 0) && ((slotId) < PLAYER_INVENTORY_PROFILE_SLOTS_COUNT)) ? (profileSlots[slotId].item ? profileSlots[slotId].item : nullptr) : nullptr;
	}
	inline UINT32 GetProfileItemId(UINT16 slotId) const noexcept {
		return (((slotId) >= 0) && ((slotId) < PLAYER_INVENTORY_PROFILE_SLOTS_COUNT)) ? (profileSlots[slotId].item ? profileSlots[slotId].item->iTemplate->id : 0) : 0;
	}
	inline UINT16 GetProfileItemEnchantLevel(UINT16 slotId) const noexcept {
		return (((slotId) >= 0) && ((slotId) < PLAYER_INVENTORY_PROFILE_SLOTS_COUNT)) ? (profileSlots[slotId].item ? profileSlots[slotId].item->enchantLevel : 0) : 0;
	}

	inline BOOL IsFullUnsafe() const noexcept {
		for (UINT16 i = 0; i < slotsCount; i++) {
			if (inventorySlots[i].IsEmpty()) {
				return FALSE;
			}
		}

		return TRUE;
	}
	inline BOOL IsFull() {
		lock();

		for (UINT16 i = 0; i < slotsCount; i++) {
			if (inventorySlots[i].IsEmpty()) {
				unlock();
				return FALSE;
			}
		}

		unlock();
		return TRUE;
	}

	INT32 GetEmptySlotUnsafe() const noexcept {
		for (UINT16 i = 0; i < slotsCount; i++) {
			if (inventorySlots[i].IsEmpty()) {
				return (UINT32)i;
			}
		}

		return -1;
	}
	INT32 GetEmptySlot() {
		lock();
		for (UINT16 i = 0; i < slotsCount; i++) {
			if (inventorySlots[i].IsEmpty()) {
				unlock();
				return (UINT32)i;
			}
		}

		unlock();
		return -1;
	}

	INT32 GetProfilePassivities(Passivity ** outPassivities);

	INT32 RefreshEnchantEffect();
	INT32 RefreshItemsModifiers();

	inline INT32 AddGoldUnsafe(UINT64 val) noexcept {
		if (ArbiterConfig::player.maxInventoryGold < (gold + val)) {
			return 1;
		}

		gold += val;

		return 0;
	}
	inline INT32 AddGold(UINT64 val) noexcept {
		lock();
		if (ArbiterConfig::player.maxInventoryGold < (gold + val)) {
			unlock();
			return 1;
		}

		gold += val;

		unlock();
		return 0;
	}

	inline  ISlot * operator[](UINT16 slotId)  noexcept {
		if (slotId >= PLAYER_INVENTORY_MAX_SLOTS) {
			return nullptr;
		}
		else if (slotId <= PLAYER_INVENTORY_PROFILE_SLOTS_COUNT) {
			return profileSlots + slotId;
		}

		return inventorySlots + slotId;
	}

	inline UINT32 GetItemId(UINT16 slotId) noexcept {
		if ((slotId - 1) < 0 || (slotId - 1) >= slotsCount) {
			return 0;
		}

		if (!inventorySlots[slotId].IsEmpty()) {
			return inventorySlots[slotId].item->iTemplate->id;
		}

		return 0;
	}

	INT32 MoveItem(UINT16 slotIdFrom, UINT16 slotIdTo) noexcept;

	inline UINT16 CountProfileItems()  noexcept {
		UINT16 count = 0;
		lock();

		for (UINT16 i = 0; i < PLAYER_INVENTORY_PROFILE_SLOTS_COUNT; i++) {
			if (!profileSlots[i].IsEmpty())
			{
				count++;
			}
		}

		unlock();
		return count;
	}
	inline UINT16 CountProfileItemsUnsafe() const noexcept {
		UINT16 count = 0;
		for (UINT16 i = 0; i < PLAYER_INVENTORY_PROFILE_SLOTS_COUNT; i++) {
			if (!profileSlots[i].IsEmpty())
			{
				count++;
			}
		}
		return count;
	}
	inline UINT16 CountInventoryItems()  noexcept {
		UINT16 count = 0;
		lock();

		for (UINT16 i = 0; i < PLAYER_INVENTORY_MAX_SLOTS; i++) {
			if (!inventorySlots[i].IsEmpty())
			{
				count++;
			}
		}

		unlock();
		return count;
	}
	inline UINT16 CountInventoryItemsUnsafe() const noexcept {
		UINT16 count = 0;
		for (UINT16 i = 0; i < PLAYER_INVENTORY_MAX_SLOTS; i++) {
			if (!inventorySlots[i].IsEmpty())
			{
				count++;
			}
		}
		return count;
	}

	inline INT32 RecalculateLevels() noexcept {
		//@TODO
		return 0;
	}
	inline INT32 RecalculateLevelsUnsafe() const noexcept {
		//@TODO
		return 0;
	}

};

FORCEINLINE void InterchangeItems(ISlot* slotFrom, ISlot * slotTo) noexcept {
	register Item* tempItem = slotFrom->item;

	slotFrom->item = slotTo->item;
	slotTo->item = tempItem;
}

#endif
