#include "ServerActions.h"
#include "Structs.h"

#include "Core.h"

#include "../Base/Utils.h"
#include "../Base/ServerDefs.h"
#include "../Base/IOCP.h"
#include "../Base/MemoryStreams.h"

#include "../Models/Connection.h"
#include "../Models/Player.h"

#include "../DataLayer/AccountDBO.h"
#include "../DataLayer/Inventory.h"

#include "../Network/NetworkIO.h"

#include "../Config/ArbiterConfig.h"
#include "../Opcodes/Opcodes.h"

#define OP_DUMP

const char SERVER_LOGIN_NAME[] = "PlanetSL";
const int SERVER_LOGIN_NAME_SIZE = sizeof(SERVER_LOGIN_NAME);

extern ArbiterState arbiterState;
ServerAction actions[OPCODE_MAX];

INT32 CheckVersionAction(WorkerState * w, ConnectionNetPartial* net) {
#ifdef OP_DUMP
	printf("RECV OP[%s]\n", __FUNCTION__);
#endif

	return  0;
}
INT32 LoginArbiterAction(WorkerState* w, ConnectionNetPartial* net) {
#ifdef OP_DUMP
	printf("RECV OP[%s]\n", __FUNCTION__);
#endif
	Account * account = GetAccount(net->id);

	UINT8 * data = net->recvBuffer + 4;

	UINT16 nameOffset = r_u16(data);
	UINT16 ticketOffset = r_u16(data + 2);
	UINT16 ticketSize = r_u16(data + 4);

	char * wname = (char *)net->recvBuffer + nameOffset;
	char name[PLAYER_NAME_MAX_LENGTH];
	nwstr_to_str(wname, name, PLAYER_NAME_MAX_LENGTH);
	char* ticket = (char*)(net->recvBuffer + ticketOffset);
	ticket[32] = 0x00;

	INT32 result = LoginArbiter(name, ticket, w->mysqlConnection, account);

	if (result == 1) { //account is online already
		//@TODO send back ...already logged in

		return 1;
	}
	else if (result) {
		return result;
	}

	MemoryStream packet = MemoryStream(5);

	packet.WriteUInt16(5);
	packet.WriteUInt16(S_CHECK_VERSION);
	packet.WriteUInt8(1);
	result = PostSendStream(net, packet);
	if (result) {
		//@TODO log
		return 1;
	}

	packet.Resize(5);
	packet.WriteUInt16(5);
	packet.WriteUInt16(S_LOADING_SCREEN_CONTROL_INFO);
	packet.WriteUInt8(0);
	result = PostSendStream(net, packet);
	if (result) {
		//@TODO log
		return 1;
	}

	packet.Resize(12);
	packet.WriteUInt16(12);
	packet.WriteUInt16(S_REMAIN_PLAY_TIME);
	packet.WriteInt32(6);
	packet.WriteInt32(0);
	result = PostSendStream(net, packet);
	if (result) {
		//@TODO log
		return 1;
	}

	packet.Resize(23);
	packet.WriteUInt16(23);
	packet.WriteUInt16(S_LOGIN_ARBITER);
	packet.WriteInt16(1);
	packet.WriteInt16(0); //unk?
	packet.WriteInt32(0);
	packet.WriteInt16(0);
	packet.WriteInt32(6);
	packet.WriteInt32(0);
	packet.WriteUInt8(0);
	result = PostSendStream(net, packet);
	if (result) {
		//@TODO log
		return 1;
	}

	packet.Resize(14 + (SERVER_LOGIN_NAME_SIZE * 2));
	packet.WriteInt16(0);
	packet.WriteInt16(S_LOGIN_ACCOUNT_INFO);
	packet.WriteInt16(14); // server name offset
	packet.WriteInt64(3656625); //??? SERVER_ID??
	packet.WriteString(SERVER_LOGIN_NAME);
	packet.WritePos();
	result = PostSendStream(net, packet);
	if (result) {
		//@TODO log
		return 1;
	}

	return 0;
}
INT32 SetVisibleRangeAction(WorkerState* w, ConnectionNetPartial* net) {
#ifdef OP_DUMP
	printf("RECV OP[%s]\n", __FUNCTION__);
#endif

	return 0;
}
INT32 GetUserListAction(WorkerState* w, ConnectionNetPartial* net) {
#ifdef OP_DUMP
	printf("RECV OP[%s]\n", __FUNCTION__);
#endif
	sql::Connection * con = w->mysqlConnection;

	Account * account = GetAccount(net->id);
	Connection * userConn = GetConnection(net->id);
	Inventory* inv = GetStorage(net->id);

	INT32 result = GetPlayerList(w->mysqlConnection, userConn, account, inv);
	if (result == 1) {
		// no charachters
	}
	else if (result) {
		return result;
	}

	UINT16 packetLength = S_GET_USER_LIST_HEADER_LENGTH + (S_GET_USER_LIST_PLAYER_NO_NAME_LENGTH * userConn->playerCount);
	MemoryStream packet = MemoryStream(packetLength);
	packet.ZeroOut();

	packet.WriteUInt16(0);
	packet.WriteUInt16(S_GET_USER_LIST);
	packet.WriteUInt16(userConn->playerCount);

	UINT16 nextPos = packet._pos;
	packet._pos += 2;

	//stream.WriteInt32(0);
	//stream.WriteByte(0);
	packet._pos += 5;
	packet.WriteInt32((int)ArbiterConfig::server.maxPlayersPerAccount);

	packet.WriteInt32(1);
	packet._pos += 2;

	packet.WriteInt32(40);
	//stream.WriteInt32(0);
	packet._pos += 4;
	packet.WriteInt32(24);

	for (UINT16 i = 0; i < userConn->playerCount; i++) {
		Player* player = &userConn->players[i];


		//@TODO write player sub packet 

	}


	return 0;
}
INT32 SelectUserAction(WorkerState* w, ConnectionNetPartial* net) {
#ifdef OP_DUMP
	printf("RECV OP[%s]\n", __FUNCTION__);
#endif
	sql::Connection * con = w->mysqlConnection;

	Account * account = GetAccount(net->id);
	Connection * userConn = GetConnection(net->id);
	Inventory* inv = GetStorage(net->id);

	UINT32 playerDbId = r_u32(net->recvBuffer + 4);
	Player * player = userConn->SelectPlayer(playerDbId);
	if (!player) {
		//@TODO send back error

		return 1;
	}
	
	//@TODO get world node and do the async world connect process 

	return 0;
}

INT32 InitServerActions() {
	actions[C_CHECK_VERSION] = CheckVersionAction;
	actions[C_LOGIN_ARBITER] = LoginArbiterAction;
	actions[C_SET_VISIBLE_RANGE] = SetVisibleRangeAction;
	actions[C_GET_USER_LIST] = GetUserListAction;
	actions[C_SELECT_USER] = SelectUserAction;


	return 0;
}

const ServerAction GetAction(UINT16 opcode)
{
	if (opcode >= OPCODE_MAX) {
		return nullptr;
	}

	return actions[opcode];
}