#include "DBHandler.h"

#include "../Config/ArbiterConfig.h"

BOOL WINAPI MySqlInit()
{
	mysqlDriver =  new MySqlDriver();
	return mysqlDriver->InitDriver(
		ArbiterConfig::mysql.mysqlIp, 
		ArbiterConfig::mysql.mysqlUser,
		ArbiterConfig::mysql.mysqlPassword, 
		ArbiterConfig::mysql.mysqlDbName);
}

void WINAPI MySqlRelease() {
	if (mysqlDriver)
	{
		delete mysqlDriver;
		mysqlDriver = NULL;
	}
}
