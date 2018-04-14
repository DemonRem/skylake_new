#include "ServerActions.h"
#include "Structs.h"

#include "Core.h"

#include "../Opcodes/Opcodes.h"
#include "../Models/Connection.h"
#include "../Base/Utils.h"
#include "../Base/ServerDefs.h"
#include "../DataLayer/AccountDBO.h"
#include "../Network/NetworkIO.h"
#include "../Base/IOCP.h"

#define OP_DUMP

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

	INT32 result = LoginArbiter(name, ticket, w->mysqlConnection, account);

	if (result == 1) { //account is online already
		/*SendStream * packet = new SendStream(23);
		Stream &data = packet->s;
		data.WriteInt16(23);
		data.WriteInt16(S_LOGIN_ARBITER);
		data.WriteInt16(0);
		data.WriteInt16(262);
		data.WriteUInt8(0);
		data.WriteInt32(8);
		data.WriteInt32(0);
		data.WriteUInt8(0);
		data.WriteInt16(1);
		data.WriteInt16(0);
		data.WriteUInt8(0);
		


		result = PostSend(net, data._raw, data._size);*/
	}
	else if (result) {



	}

	return result;
}

INT32 InitServerActions() {
	actions[C_CHECK_VERSION] = CheckVersionAction;
	actions[C_LOGIN_ARBITER] = LoginArbiterAction;


	return 0;
}

const ServerAction GetAction(UINT16 opcode)
{
	if (opcode >= OPCODE_MAX) {
		return nullptr;
	}

	return actions[opcode];
}