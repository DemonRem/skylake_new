#include "ItemsDBO.h"

#include "PassivityCore.h"

#include "../Base/win32.h"
#include "../Base/MemoryStreams.h"
#include "../Models/Item.h"
#include "../Models/Passivity.h"
#include "../Models/DataStore.h"

#include <sstream>

volatile UID lastUID;

INT32 InitItemsDBO(sql::Connection * conn) {
	sql::PreparedStatement * p = nullptr;
	sql::ResultSet * rs = nullptr;

	try {
		p = conn->prepareStatement("SELECT max(Id) FROM items");
		rs = p->executeQuery();

		if (rs && rs->next()) {
			UINT64 lId = rs->getUInt64(1);
			printf("Last Item ID[%lld]\n", lId);
			lId++;

			InterlockedExchange(&lastUID.id, lId);
			rs->close();
			delete rs;
			rs = nullptr;
		}
		else {
			p->close();
			delete p;
			return 2;
		}
	}
	catch (sql::SQLException & e) {
		printf("Failed to init ItemsDBO. ex[%s]\n", e.what());
		return 1;
	}

	if (p) {
		p->close();
		delete p;
	}
	if (rs) {
		rs->close();
		delete rs;
	}

	return 0;
}
FORCEINLINE UID GetNewItemUID() {
	return InterlockedIncrement(&lastUID.id);
}

INT32 SerializeItem(Item * i, MemoryStream * data) {
	const UINT16 pCount = i->PassivitiesCount();
	data->Alloc(42 + (12 * pCount));

	UINT8* ptr = (UINT8*)&i->stackCount;
	data->Write(ptr, ITEM_BODY_SIZE);
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
	data->Read(ptr, ITEM_BODY_SIZE);

	UINT16 pCount = data->ReadUInt16();
	if (pCount >= ITEM_ACTIVE_PASSIVITIES_MAX_COUNT) {
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

Item * CreateItem(UINT64 itemId, UID playerId, sql::Connection * sql) {
	UINT32 iTemplateIndex = GetItemTemplateIndex(itemId);
	if (iTemplateIndex == UINT32_MAX) {
		//@TODO log
		return nullptr;
	}

	const ItemTemplate * iTemplate = GetItemTemplate(iTemplateIndex);
	if (!iTemplate) {
		//@TODO log
		return nullptr;
	}

	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	item->iTemplate = (ItemTemplate*)iTemplate;
	item->id = GetNewItemUID();

	INT32 result = PassivityRollItem(item.get());
	if (result) {
		//@TODO log
		return  nullptr;
	}

	if (iTemplate->category == EItemCategory_twohand || iTemplate->category == EItemCategory_axe || iTemplate->category == EItemCategory_circle || iTemplate->category == EItemCategory_bow || iTemplate->category == EItemCategory_staff || iTemplate->category == EItemCategory_rod || iTemplate->category == EItemCategory_lance ||
		iTemplate->category == EItemCategory_dual || iTemplate->category == EItemCategory_blaster || iTemplate->category == EItemCategory_gauntlet || iTemplate->category == EItemCategory_shuriken || iTemplate->category == EItemCategory_glaive ||
		iTemplate->category == EItemCategory_bodyMail || iTemplate->category == EItemCategory_handMail || iTemplate->category == EItemCategory_feetMail ||
		iTemplate->category == EItemCategory_bodyLeather || iTemplate->category == EItemCategory_handLeather || iTemplate->category == EItemCategory_feetLeather ||
		iTemplate->category == EItemCategory_bodyRobe || iTemplate->category == EItemCategory_handRobe || iTemplate->category == EItemCategory_feetRobe)
	{
		switch (iTemplate->type)
		{
		case EItemType_EQUIP_WEAPON: {

		}break;
		case EItemType_EQUIP_ARMOR_BODY: {

		}break;
		case EItemType_EQUIP_ARMOR_LEG: {

		}break;
		case EItemType_EQUIP_ARMOR_ARM: {

		}break;
		}
	}

	MemoryStream raw;
	result = SerializeItem(item.get(), &raw);
	if (result) {
		//@TODO log
		return nullptr;
	}

	std::stringstream itemBlob = std::stringstream(std::string((char*)raw._raw, raw._size));

	sql::PreparedStatement *p = nullptr;
	try {
		sql::PreparedStatement * p = sql->prepareStatement("INSERT INTO items(id, item_id, item_index, data) VALUES(?,?,?,?)");
		p->setInt64(1, item->id.id);
		p->setInt64(2, itemId);
		p->setInt(3, iTemplateIndex);
		p->setBlob(4, (std::istream*)&itemBlob);

		result = p->executeUpdate();
		if (!result) {
			p->close();
			delete p;

			//@TODO log
			return nullptr;
		}

#ifdef DEBUG
		printf("CREATED ITEM id[%lld]\n", item->id.id);
#endif

	}
	catch (sql::SQLException & e) {
		//@TODO log
		printf("::SQL-EXCEPTION FN[create_item] LINE[%d] MSG[%s]\n", __LINE__, e.what());
		if (p) {
			p->close();
			delete p;
		}

		return nullptr;
	}

	if (p) {
		p->close();
		delete p;
		p = nullptr;
	}

	return item.release();
}
Item * CreateItemFromTemplate(UINT32 iTemplateIndex, UID playerId, sql::Connection * sql) {
	const ItemTemplate * iTemplate = GetItemTemplate(iTemplateIndex);
	if (!iTemplate) {
		//@TODO log
		return nullptr;
	}

	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	item->iTemplate = (ItemTemplate*)iTemplate;
	item->id = GetNewItemUID();

	INT32 result = PassivityRollItem(item.get());
	if (result) {
		//@TODO log
		return  nullptr;
	}

	if (iTemplate->category == EItemCategory_twohand || iTemplate->category == EItemCategory_axe || iTemplate->category == EItemCategory_circle || iTemplate->category == EItemCategory_bow || iTemplate->category == EItemCategory_staff || iTemplate->category == EItemCategory_rod || iTemplate->category == EItemCategory_lance ||
		iTemplate->category == EItemCategory_dual || iTemplate->category == EItemCategory_blaster || iTemplate->category == EItemCategory_gauntlet || iTemplate->category == EItemCategory_shuriken || iTemplate->category == EItemCategory_glaive ||
		iTemplate->category == EItemCategory_bodyMail || iTemplate->category == EItemCategory_handMail || iTemplate->category == EItemCategory_feetMail ||
		iTemplate->category == EItemCategory_bodyLeather || iTemplate->category == EItemCategory_handLeather || iTemplate->category == EItemCategory_feetLeather ||
		iTemplate->category == EItemCategory_bodyRobe || iTemplate->category == EItemCategory_handRobe || iTemplate->category == EItemCategory_feetRobe)
	{
		switch (iTemplate->type)
		{
		case EItemType_EQUIP_WEAPON: {

		}break;
		case EItemType_EQUIP_ARMOR_BODY: {

		}break;
		case EItemType_EQUIP_ARMOR_LEG: {

		}break;
		case EItemType_EQUIP_ARMOR_ARM: {

		}break;
		}
	}

	MemoryStream raw;
	result = SerializeItem(item.get(), &raw);
	if (result) {
		//@TODO log
		return nullptr;
	}

	std::stringstream itemBlob = std::stringstream(std::string((char*)raw._raw, raw._size));

	sql::PreparedStatement *p = nullptr;
	try {
		sql::PreparedStatement * p = sql->prepareStatement("INSERT INTO items(id, item_id, item_index, data) VALUES(?,?,?,?)");
		p->setInt64(1, item->id.id);
		p->setInt64(2, iTemplate->id);
		p->setInt(3, iTemplateIndex);
		p->setBlob(4, (std::istream*)&itemBlob);

		result = p->executeUpdate();
		if (!result) {
			p->close();
			delete p;

			//@TODO log
			return nullptr;
		}

#ifdef DEBUG
		printf("CREATED ITEM id[%lld]\n", item->id.id);
#endif

	}
	catch (sql::SQLException & e) {
		//@TODO log
		printf("::SQL-EXCEPTION FN[create_item] LINE[%d] MSG[%s]\n", __LINE__, e.what());
		if (p) {
			p->close();
			delete p;
		}

		return nullptr;
	}

	if (p) {
		p->close();
		delete p;
		p = nullptr;
	}

	return item.release();
}
Item * CreateItem(Item * existing, UID playerId, sql::Connection * sql) {

	UINT32 iTemplateIndex = existing->iTemplate->index;
	ItemTemplate * iTemplate = existing->iTemplate;

	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	INT32 result = CopyItem(existing, item.get());
	if (result) {
		//@TODO log;
		return nullptr;
	}

	item->id = GetNewItemUID();

	result = PassivityRollItem(item.get());
	if (result) {
		//@TODO log
		return  nullptr;
	}

	if (iTemplate->category == EItemCategory_twohand || iTemplate->category == EItemCategory_axe || iTemplate->category == EItemCategory_circle || iTemplate->category == EItemCategory_bow || iTemplate->category == EItemCategory_staff || iTemplate->category == EItemCategory_rod || iTemplate->category == EItemCategory_lance ||
		iTemplate->category == EItemCategory_dual || iTemplate->category == EItemCategory_blaster || iTemplate->category == EItemCategory_gauntlet || iTemplate->category == EItemCategory_shuriken || iTemplate->category == EItemCategory_glaive ||
		iTemplate->category == EItemCategory_bodyMail || iTemplate->category == EItemCategory_handMail || iTemplate->category == EItemCategory_feetMail ||
		iTemplate->category == EItemCategory_bodyLeather || iTemplate->category == EItemCategory_handLeather || iTemplate->category == EItemCategory_feetLeather ||
		iTemplate->category == EItemCategory_bodyRobe || iTemplate->category == EItemCategory_handRobe || iTemplate->category == EItemCategory_feetRobe)
	{
		switch (iTemplate->type)
		{
		case EItemType_EQUIP_WEAPON: {

		}break;
		case EItemType_EQUIP_ARMOR_BODY: {

		}break;
		case EItemType_EQUIP_ARMOR_LEG: {

		}break;
		case EItemType_EQUIP_ARMOR_ARM: {

		}break;
		}
	}

	MemoryStream raw;
	result = SerializeItem(item.get(), &raw);
	if (result) {
		//@TODO log
		return nullptr;
	}

	std::stringstream itemBlob = std::stringstream(std::string((char*)raw._raw, raw._size));

	sql::PreparedStatement *p = nullptr;
	try {
		sql::PreparedStatement * p = sql->prepareStatement("INSERT INTO items(id, item_id, item_index, data) VALUES(?,?,?,?)");
		p->setInt64(1, item->id.id);
		p->setInt64(2, item->iTemplate->id);
		p->setInt(3, iTemplateIndex);
		p->setBlob(4, (std::istream*)&itemBlob);

		result = p->executeUpdate();
		if (!result) {
			p->close();
			delete p;

			//@TODO log
			return nullptr;
		}

#ifdef DEBUG
		printf("CREATED ITEM id[%lld]\n", item->id.id);
#endif

	}
	catch (sql::SQLException & e) {
		//@TODO log
		printf("::SQL-EXCEPTION FN[create_item] LINE[%d] MSG[%s]\n", __LINE__, e.what());
		if (p) {
			p->close();
			delete p;
		}

		return nullptr;
	}

	if (p) {
		p->close();
		delete p;
		p = nullptr;
	}

	return item.release();
}

Item * CreateNonDbItem(Item * existing) {
	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	item->id = GetNewItemUID();

	INT32 result = CopyItem(existing, item.get());
	if (result) {
		//@TODO log
		return nullptr;
	}


	return item.release();
}
Item * CreateNonDbItem(UINT64 itemId, UINT32 stackCount) {
	UINT32 iTemplateIndex = GetItemTemplateIndex(itemId);
	if (iTemplateIndex == UINT32_MAX) {
		//@TODO log
		return nullptr;
	}

	const ItemTemplate * iTemplate = GetItemTemplate(iTemplateIndex);
	if (!iTemplate) {
		//@TODO log
		return nullptr;
	}

	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	item->id = GetNewItemUID();

	return item.release();
}
Item * CreateNonDbItemFromTemplate(UINT32 iTemplateIndex, UINT32 stackCount) {
	const ItemTemplate * iTemplate = GetItemTemplate(iTemplateIndex);
	if (!iTemplate) {
		//@TODO log
		return nullptr;
	}

	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	item->id = GetNewItemUID();

	return item.release();
}

INT32 UpdateItem(Item * item, sql::Connection * sql) {
	MemoryStream raw;
	INT32 result = SerializeItem(item, &raw);
	if (result) {
		//@TODO log
		return 1;
	}

	std::stringstream itemBlob = std::stringstream(std::string((char*)raw._raw, raw._size));
	sql::PreparedStatement *p = nullptr;
	try {
		sql::PreparedStatement * p = sql->prepareStatement("UPDATE items SET data=?");
		p->setBlob(1, (std::istream*)&itemBlob);

		result = p->executeUpdate();
		if (!result) {
			p->close();
			delete p;

			//@TODO log
			return 2;
		}

#ifdef DEBUG
		printf("UPDATED ITEM id[%lld]\n", item->id.id);
#endif

	}
	catch (sql::SQLException & e) {
		//@TODO log
		printf("::SQL-EXCEPTION FN[create_item] LINE[%d] MSG[%s]\n", __LINE__, e.what());
		if (p) {
			p->close();
			delete p;
		}

		return 3;
	}

	if (p) {
		p->close();
		delete p;
		p = nullptr;
	}

	return 0;
}
INT32 DeleteItem(UID id, sql::Connection * sql) {
	sql::PreparedStatement *p = nullptr;
	try {
		sql::PreparedStatement * p = sql->prepareStatement("DELETE FROM items WHERE id=?");
		p->setUInt64(1, id.id);

		INT32 result = p->executeUpdate();
		if (!result) {
			p->close();
			delete p;

			//@TODO log
			return 1;
		}

#ifdef DEBUG
		printf("UPDATED ITEM id[%lld]\n", item->id.id);
#endif

	}
	catch (sql::SQLException & e) {
		//@TODO log
		printf("::SQL-EXCEPTION FN[create_item] LINE[%d] MSG[%s]\n", __LINE__, e.what());
		if (p) {
			p->close();
			delete p;
		}

		return 2;
	}

	if (p) {
		p->close();
		delete p;
		p = nullptr;
	}

	return 0;
}

Item * GetItem(UID dbId, sql::Connection * sql) {
	auto item = std::make_unique<Item>();
	if (!item.get()) {
		//@TODO log
		return nullptr;
	}

	sql::PreparedStatement *p = nullptr;
	sql::ResultSet * rs = nullptr;

	try {
		sql::PreparedStatement * p = sql->prepareStatement("SELECT * FROM items WHERE id=?");
		p->setUInt64(1, dbId.id);

		rs = p->executeQuery();

		if (rs && rs->next()) {
			item->id = dbId;
			
			UINT64 itemId = rs->getUInt64(2);
			UINT32 iTemplateIndex = GetItemTemplateIndex(itemId);
			if (iTemplateIndex == UINT32_MAX) {
				rs->close();
				delete rs;

				p->close();
				delete p;

				//@TODO log
				return nullptr;
			}

			const ItemTemplate * iTempalte = GetItemTemplate(iTemplateIndex);
			item->iTemplate = (ItemTemplate *)iTempalte;
			
			std::istream * blob = rs->getBlob(4);
			if (!blob) {
				rs->close();
				delete rs;

				p->close();
				delete p;

				//@TODO log
				return nullptr;
			}

			MemoryStream ms = MemoryStream(blob);

			INT32 result = DeserializeItem(item.get(), &ms);
			if (result) {
				rs->close();
				delete rs;

				p->close();
				delete p;

				delete blob;

				//@TODO log
				return nullptr;
			}

			delete blob;
		}

	}
	catch (sql::SQLException & e) {
		//@TODO log
		printf("::SQL-EXCEPTION LINE[%d] MSG[%s]\n", __LINE__, e.what());
		if (p) {
			p->close();
			delete p;
		}

		return nullptr;
	}

	if (p) {
		p->close();
		delete p;
	}

	if (rs) {
		rs->close();
		delete rs;
	}

	return item.release();
}

INT32 GetInventory(Player * player, sql::Connection * conn) {

	//@TODO


	return INT32();
}

BOOL CopyItem(Item * src, Item * dest) {
	if (!src || !dest) {
		return FALSE;
	}

	if (memcpy_s(&dest->stackCount, ITEM_BODY_SIZE, &src->stackCount, ITEM_BODY_SIZE)) {
		return FALSE;
	}

	Passivity ** pPtr = src->passivities;
	Passivity ** destPPstr = dest->passivities;
	while (*pPtr) {
		*destPPstr = *pPtr;
		pPtr++;
	}

	src->iTemplate = dest->iTemplate;

	return TRUE;
}

	
