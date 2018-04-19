#include "Inventory.h"

INT32 Inventory::MoveItem(UINT16 slotIdFrom, UINT16 slotIdTo) noexcept
{
	lock();

	if ((slotIdFrom < 40 || slotIdFrom >= (slotsCount + 40)) || (slotIdTo < 40 || slotIdTo >= (slotsCount + 40))) {
		unlock();
		return 1;
	}

	ISlot * slotFrom = inventorySlots + slotIdFrom;
	ISlot * slotTo = inventorySlots + slotIdTo;

	if (slotFrom->IsEmpty()) 
	{
		//@TODO log
		unlock();
		return 2;
	}
	else if (slotTo->IsEmpty()) 
	{
		InterchangeItems(slotFrom, slotTo);
		unlock();
		return 0;
	}

	//if is stackable (nonDB) we process stack stuff
	if (slotFrom->item->iTemplate->id == slotTo->item->iTemplate->id && //same item template
		slotTo->item->iTemplate->HasFlag(EItemTemplateFlags_IsNonDb))
	{
		UINT32 totalStack = slotFrom->item->stackCount + slotTo->item->stackCount;
		if (totalStack > slotTo->item->iTemplate->maxStack) 
		{ //if stack is greater than the maxStack admited by the item template we keep (totalStack - maxStack) in slotFrom->item->stackCount
			slotTo->item->stackCount = slotTo->item->iTemplate->maxStack;
			slotFrom->item->stackCount = slotTo->item->iTemplate->maxStack - totalStack;
		}
		else 
		{ //if sum of stacks is less than the maxStack we add it to the slotTo->item stack and destory the slotFrom->item
			slotTo->item->stackCount += slotFrom->item->stackCount;
			slotFrom->Clear();
		}
	}
	else 
	{
		InterchangeItems(slotFrom, slotTo);
	}


	unlock();
	return 0;
}