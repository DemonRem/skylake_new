#ifndef ITEMS_DBO_H
#define ITEMS_DBO_H

#include "../Base/typeDefs.h"

#include "MySqlDriver.h"

struct Item;
struct Player;
struct ItemTemplate;
struct MemoryStream;

INT32 InitItemsDBO(sql::Connection * conn);

INT32 SerializeItem(Item* i, MemoryStream * outData);
INT32 DeserializeItem(Item* i, MemoryStream * data);

Item *CreateItem(Item * existing, UID playerId, sql::Connection * sql);
Item *CreateItemFromTemplate(UINT32 iTemplateIndex, UID playerId, sql::Connection * sql);
Item *CreateItem(UINT64 itemId, UID playerId, sql::Connection * sql);

Item* CreateNonDbItem(Item * existing);
Item* CreateNonDbItemFromTemplate(UINT32 iTemplateIndex, UINT32 stackCount);
Item* CreateNonDbItem(UINT64 itemId, UINT32 stack);

INT32 UpdateItem(Item * i, sql::Connection * conn);
INT32 DeleteItem(UID id, sql::Connection * conn);
Item * GetItem(UID dbId, sql::Connection* conn);
INT32 GetInventory(Player* player, sql::Connection * conn);

BOOL CopyItem(Item* src, Item * dest);

#endif
