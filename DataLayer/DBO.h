#ifndef DBO_H
#define DBO_H

#include "AccountDBO.h"
#include "ItemsDBO.h"
#include "AchievementsDBO.h"
#include "SkillsDBO.h"

#include "MySqlDriver.h"

INT32 InitDBO(sql::Connection * conn);

static MySqlDriver driver;
FORCEINLINE MySqlDriver* GetMysqlDriver() {
	return &driver;
}

#endif
