#include "MySqlDriver.h"

MySqlDriver::~MySqlDriver(){
	_driver = 0;
}

const BOOL MySqlDriver::InitDriver(const char* hostAddress, const char* hostUsername, const char * hostPassword, const char* databaseName)
{
	_driver = sql::mysql::get_driver_instance();
	if (!_driver) {
		return FALSE;
	}

	_hostAddress = sql::SQLString(hostAddress);
	_hostUsername = sql::SQLString(hostUsername);
	_hostPassword = sql::SQLString(hostPassword);
	_dbName = sql::SQLString(databaseName);

#if INIT_LOG
	printf("Mysql::Init(%s, %s, %s, %s)\n", _hostAddress.c_str(), _hostUsername.c_str(), _hostPassword.c_str(), _dbName.c_str());
#endif
	return TRUE;
}

sql::Connection * MySqlDriver::NewConnection()
{
	sql::Connection * newConnecion = nullptr;
	try
	{
		newConnecion = _driver->connect(_hostAddress, _hostUsername, _hostPassword);
	}
	catch (sql::SQLException & ex)
	{
		printf("SQL-EX:%s\n", ex.what());
	}

	if (!newConnecion)
		return nullptr;
	else if (!newConnecion->isValid())
	{
		delete newConnecion;
		return nullptr;
	}

	try
	{
		newConnecion->setSchema(_dbName);
	}
	catch (sql::SQLException & ex)
	{
		printf("SQL-EX:%s\n", ex.what());

		newConnecion->close();

		delete newConnecion;
		newConnecion = nullptr;
	}

	return newConnecion;
}