#ifndef STRUCTS_H
#define STRUCTS_H

#include "../Base/typeDefs.h"
#include "../Base/win32.h"
#include "../Base/winsock.h"
#include "../Base/WorkItems.h"
#include "../Base/Atomic.h"

#include "../contrib/mysql/include/mysql_connection.h"

struct ArbiterState {
	WSADATA wsa;
	SOCKET acceptSock;

	HANDLE workQueue;
	UINT32  workerThreadsCount;
	HANDLE * workerThreads;
	HANDLE acceptThread;
	WSAEVENT acceptEvent;
	HANDLE shutdownEvent;

	a_uint32 connectionsCount;
};
struct WorkerState {
	sql::Connection * mysqlConnection;
	DWORD numberOfBytesTransfered;
	UINT64 completionKey;
	Work * work;
};

#endif
