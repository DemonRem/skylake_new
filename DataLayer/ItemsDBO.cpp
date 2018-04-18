#include "ItemsDBO.h"

#include "../Base/MemoryStreams.h"
#include "../Models/Item.h"
#include "../Models/Passivity.h"


#include "../Models/DataStore.h"

INT32 SerializeItem(Item * i, MemoryStream * data) {
	const UINT16 pCount = i->PassivitiesCount();
	data->Alloc(42 + (12 * pCount)); 

	UINT8* ptr = (UINT8*)&i->stackCount;
	data->Write(ptr, 40);
	data->WriteUInt16(pCount);

	Passivity ** pPtr = i->passivities;
	while (*pPtr) {
		Passivity * p = *pPtr;

		data->WriteUID(p->id);
		data->WriteUInt32(p->index); //cached index 

		pPtr++;
	}

	return 0;
}

INT32 DeserializeItem(Item * i, MemoryStream * data) {
	UINT8* ptr = (UINT8*)&i->stackCount;
	data->Read(ptr, 40);

	UINT16 pCount = data->ReadUInt16();
	if (pCount >= ITEM_MAX_PASSIVITIES) {
		//@TODO log
		return 3;
	}

	Passivity ** pPtr = i->passivities;
	while (pCount) {
		UINT64 uid = data->ReadUInt64();
		UINT32 index = data->ReadUInt32();

		const Passivity* p = GetPassivity(index);
		if (!p) {
			//@TODO need to redo the items db passivities indices
			//@TODO log

			index = GetPassivityIndex(uid); //O(n)
			if (index == UINT32_MAX) {
				return 1;
			}

			p = GetPassivity(index); //O(1)
			if (!p) {
				//@TODO log
				return 2;
			}
		}

		*pPtr = (Passivity*)p;

		pPtr++;
		pCount--;
	}

	return 0;
}
