#include "DBOTest.h"
#include "../DataLayer/DBO.h"

#include <mysql_connection.h>
#include <exception>

UINT32 DBOTest() {

	MySqlDriver * driver = new MySqlDriver();
	if (!driver) {
		return 1;
	}

	if (!driver->InitDriver("127.0.0.1", "root", "root", "tera_q")) {
		return 2;
	}
	
	sql::Connection * conn = driver->NewConnection();
	if (!conn) {
		return 3;
	}

	return  0;
}
