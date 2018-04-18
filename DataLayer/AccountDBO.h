#ifndef ACCOUNT_DBO_H
#define ACCOUNT_DBO_H

#include "../Base/typeDefs.h"
#include "../contrib/mysql/include/mysql_connection.h"

struct Account;
struct Connection;
struct Inventory;

const INT32 LoginArbiter(const char* username, const char password[32], sql::Connection * conn, Account * account);
const INT32 GetPlayerList(sql::Connection * sqlConn, Connection* conn, Account * account, Inventory* inv);

#endif
