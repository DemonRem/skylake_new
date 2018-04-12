#ifndef CORE_H
#define CORE_H

#include "../Base/win32.h"
#include "../Base/winsock.h"
#include "../Base/typeDefs.h"
#include "../Base/ServerDefs.h"

#include "../Models/Connection.h"

static Account accounts[MAX_CONNECTIONS];
static Connection connections[MAX_CONNECTIONS];
static ConnectionNetPartial connectionNetData[MAX_CONNECTIONS];

const BOOL InitArbiterCore();

FORCEINLINE Connection * GetConnection(UID id) noexcept {
	return connections + id.id;
}
FORCEINLINE Account * GetAccount(UID id) noexcept {
	return accounts + id.id;
}
FORCEINLINE ConnectionNetPartial * GetConnectionNetData(UID id) noexcept {
	return connectionNetData + id.id;
}

Connection * GetNewConnection() noexcept;
const INT32 ReleaseConnection(UID id) noexcept;

#endif
