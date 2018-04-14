#ifndef WORKITEM_TYPE_H
#define WORKITEM_TYPE_H

#include "../typeDefs.h"

enum EWorkItemType : LONG {
	WorkItemType_RecvFromConnection,
	WorkItemType_NewConnection,
	WorkItemType_SendInit,
	WorkItemType_SendKey,
	WorkItemType_SendToConnection,
	WorkItemType_SendStream,

	WorkerItemType_MAX
};

enum EWorkItemFlags : ULONG {
	EWorkItemFlags_None = 0,
	EWorkItemFlags_ShouldNotDelete = 1 << 0,
	EWorkItemFlags_ShouldNotDeleteData = 1 << 1
};

#endif
