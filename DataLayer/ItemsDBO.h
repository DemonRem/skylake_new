#ifndef ITEMS_DBO_H
#define ITEMS_DBO_H

#include "../Base/typeDefs.h"

#include "MySqlDriver.h"

struct Item;
struct MemoryStream;

INT32 SerializeItem(Item* i, MemoryStream * outData);
INT32 DeserializeItem(Item* i, MemoryStream * data);

#endif
