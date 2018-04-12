#ifndef DBHANDLER_H
#define DBHANDLER_H

#include "../Base/typeDefs.h"
#include "../Base/win32.h"

#include "MySqlDriver.h"

static MySqlDriver  *mysqlDriver;

BOOL WINAPI MySqlInit();
void WINAPI MySqlRelease();

FORCEINLINE MySqlDriver *  WINAPI GetMysqlDriver() {
	return mysqlDriver;
}

#endif
