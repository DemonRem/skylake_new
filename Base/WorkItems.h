#ifndef WORK_ITEMS_H
#define WORK_ITEMS_H

#include "typeDefs.h"
#include "Enums/WorkItemType.h"
#include "../Base/Stream.h"
#include "../Base/win32.h"
#include "../Base/winsock.h"

struct Connection;

struct Work {
	OVERLAPPED w;
	const EWorkItemType type;
	DWORD workFlags;

	Work(const EWorkItemType t) : type(t) { memset(&w, 0, sizeof(OVERLAPPED)); }

	inline const BOOL HasWorkFlag(const EWorkItemFlags flag) const noexcept {
		return workFlags & flag;
	}
	inline void AddWorkFlag(const EWorkItemFlags flag) noexcept {
		workFlags |= flag;
	}
	inline void RemoveWorkFlag(const EWorkItemFlags flag) noexcept {
		workFlags &= !flag;
	}
};

struct HandleNewConnection : Work {
	HandleNewConnection(Connection *conn) :Work(WorkItemType_NewConnection), connection(conn) {}

	Connection* connection;
};

struct SendInit : Work {
	SendInit(UID connId) :Work(WorkItemType_SendInit), connectionId(connId) {  }

	const UID connectionId;
	WSABUF buff;
};

struct SendKey : Work {
	SendKey(UID connId) :Work(WorkItemType_SendKey), connectionId(connId) {  }

	const UID connectionId;
	WSABUF buff;
};

struct SendToConnection : Work {
	SendToConnection(UID connId) :Work(WorkItemType_SendToConnection), connectionId(connId) {}

	const UID connectionId;
	WSABUF buff;
};


#endif
