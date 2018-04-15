#include "AccountDBO.h"

#include "../contrib/mysql/include/cppconn/resultset.h"
#include "../contrib/mysql/include/cppconn/exception.h"
#include "../contrib/mysql/include/cppconn/prepared_statement.h"
#include "../contrib/mysql/include/cppconn/sqlstring.h"

#include "../Models/Connection.h"

#include <time.h>

const INT32 LoginArbiter(const char * username, const char password[32], sql::Connection * conn, Account * account)
{
	sql::PreparedStatement *p = nullptr;
	sql::ResultSet * rs;

	try
	{
		p = conn->prepareStatement("SELECT * FROM accounts WHERE username=? AND password=?");
		p->setString(1, (const char*)username);
		p->setString(2, (const char*)password);
		rs = p->executeQuery();

		if (rs && rs->next()) {
			/*bool isOnline = rs->getBoolean(8);
			if (isOnline) {
				std::cout << "::ARBITER::MULTIPLE CONNECTION ON SAME ACCOUNT ATTEMPT REJECTED!\n";

				p->close();
				rs->close();
				delete p;
				delete rs;

				return 1;
			}*/

			account->dbId = (UINT64)rs->getInt64(1); //id
			account->flags = rs->getInt(5); //flags
			account->remainingPlayTimeUTC = rs->getInt(7);
			account->lastOnlineUTC = time(NULL);

			rs->close();
			delete rs;
		}

		p->close();
		delete p;

		p = conn->prepareStatement("UPDATE accounts SET isOnline=?, lastOnlineUTC=?, connectionIndex=? WHERE id=?");
		p->setBoolean(1, true);
		p->setInt64(2, account->lastOnlineUTC);
		p->setInt64(3, account->id.id);
		p->setInt64(4, account->dbId.id);

		INT32 result = p->executeUpdate();
		if (!result) {
			//@TODO log

			p->close();
			delete p;

			return 2;
		}
	
		p->close();
		delete p;
		p = nullptr;
	}
	catch (sql::SQLException & e)
	{
		printf("::SQL-EX::LN[%d] FN[%s] EX[%s]\n", __LINE__, __FUNCTION__, e.what());
		if (p) {
			delete p;
			p = nullptr;
		}

		return 3;
	}

	if (p) {
		delete p;
	}

	return 0;
}


