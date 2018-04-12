#ifndef NETWORKIO_H
#define NETWORKIO_H

#include "../Base/typeDefs.h"

#include "../Base/win32.h"
#include "../Base/winsock.h"
#include "../Models/Connection.h"

struct ConnectionNetPartial;
struct SendToConnection;

const INT32 StartInitProcess(ConnectionNetPartial* conn);
const INT32 SendServerKey(ConnectionNetPartial * conn, INT32 index);
const INT32 PostSend(ConnectionNetPartial* conn, SendToConnection* packet);
const INT32 PostSend(ConnectionNetPartial* conn, UINT8* data, UINT32 size);
const INT32 PostRecv(ConnectionNetPartial * conn);

FORCEINLINE INT32 CloseSocket(SOCKET s) {
	shutdown(s, SD_BOTH);
	return closesocket(s);
}

#endif
