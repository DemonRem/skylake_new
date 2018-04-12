#ifndef MYSQL_DRIVER_H
#define MYSQL_DRIVER_H

#include "../contrib/mysql/include/mysql_driver.h"
#include "../contrib/mysql/include/mysql_connection.h"
#include "../contrib/mysql/include/mysql_error.h"
#include "../contrib/mysql/include/cppconn\resultset.h"
#include "../contrib/mysql/include/cppconn\statement.h"
#include "../contrib/mysql/include/cppconn\datatype.h"
#include "../contrib/mysql/include/cppconn\prepared_statement.h"

#include "../Base/typeDefs.h"

struct MySqlDriver
{
	MySqlDriver() :_driver(nullptr) {}
	~MySqlDriver();

	const BOOL InitDriver(const char* hostAddress, const char* hostUsername, const char * hostPassword, const char* databaseName);
	sql::Connection * NewConnection();

private:
	sql::Driver * _driver;
	BOOL _isValid = false;

	sql::SQLString _hostAddress;
	sql::SQLString _hostUsername;
	sql::SQLString _hostPassword;
	sql::SQLString _dbName;
};
#endif
