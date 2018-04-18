#include "AccountDBO.h"

#include "../contrib/mysql/include/cppconn/resultset.h"
#include "../contrib/mysql/include/cppconn/exception.h"
#include "../contrib/mysql/include/cppconn/prepared_statement.h"
#include "../contrib/mysql/include/cppconn/sqlstring.h"

#include "../Base/ServerDefs.h"
#include "../Models/Connection.h"
#include "../Models/Player.h"
#include "../Config/ArbiterConfig.h"

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

const INT32 GetPlayerList(sql::Connection * sqlConn, Connection * conn, Account * account) {

	sql::PreparedStatement *p = nullptr;
	sql::ResultSet * rs = nullptr;

	try {
		p = sqlConn->prepareStatement("SELECT * FROM players WHERE accountId=?");
		p->setInt64(1, account->id.id);

		rs = p->executeQuery();

		if (!rs) {
			p->close();
			delete p;
			p = nullptr;

			return 1;
		}

		UINT32 playersCount = (UINT32)rs->rowsCount();
		conn->players = new Player[playersCount];
		conn->playerCount = playersCount;

		if (!conn->players) {
			p->close();
			delete p;
			p = nullptr;

			return 2;
		}
		memset(conn->players, 0, sizeof(Player) * playersCount);

		Player * player = conn->players;
		while (rs->next()) {
			sql::SQLString name = rs->getString(3);
			if (strcpy_s(player->name, PLAYER_NAME_MAX_LENGTH, name.c_str())) {
				throw sql::SQLException("Bad player name");
			}

			player->dbId = rs->getInt(1); //id

			player->x.store((float)rs->getDouble(4));
			player->y.store((float)rs->getDouble(5));
			player->z.store((float)rs->getDouble(6));
			player->h.store((INT16)rs->getInt(7));

			player->flags = rs->getInt(8);

			player->pRace = (EPlayerRace)rs->getInt(9);
			player->pGender = (EPlayerGender)rs->getInt(10);
			player->pClass = (EPlayerClass)rs->getInt(11);

			player->exp = rs->getInt64(12);
			player->restedExp = rs->getInt64(13);

			player->level = rs->getInt(14);

			player->lastOnline = rs->getInt64(18);
			player->createdAt = rs->getInt64(19);
			player->banTime = rs->getInt64(20);

			player->worldMapGuardId = rs->getInt(21);
			player->worldMapWorldId = rs->getInt(22);
			player->worldMapSectionId = rs->getInt(23);

			player->continentId = rs->getInt(24);
			player->areaId = rs->getInt(25);
			player->channel = rs->getInt(26);

			player->lobbyIndex = rs->getInt(27);

			std::istream * blob = rs->getBlob("details1");
			if (blob)
			{
				blob->read((char*)player->details1, PLAYER_DETAILS_1_BUFFER_SIZE);
				delete blob;
			}
			blob = rs->getBlob("details2");
			if (blob)
			{
				blob->read((char*)player->details2, PLAYER_DETAILS_2_BUFFER_SIZE);
				delete blob;
			}
			blob = rs->getBlob("details3");
			if (blob)
			{
				blob->read((char*)player->details3, PLAYER_DETAILS_3_BUFFER_SIZE);
				delete blob;
			}

			player->account = account;
			player->connection = conn;

			player++;
		}

	}
	catch (sql::SQLException& e) {
		printf("::SQL-EX::LN[%d] FN[%s] EX[%s]\n", __LINE__, __FUNCTION__, e.what());

		if (p) {
			p->close();
			delete p;
			p = NULL;
		}
		if (rs) {
			rs->close();
			delete rs;
			rs = NULL;
		}

		if (conn->players) {
			delete[] conn->players;
			conn->players = nullptr;
			conn->playerCount = 0;
		}
	}

	if (p) {
		p->close();
		delete p;
		p = NULL;
	}
	if (rs) {
		rs->close();
		delete rs;
		rs = NULL;
	}

	return 0;
}


