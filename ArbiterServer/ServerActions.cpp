#include "ServerActions.h"
#include "Structs.h"

#define OP_DUMP

extern ArbiterState arbiterState;
ServerAction actions[OPCODE_MAX];

INT32 CheckVersionAction(WorkerState * w)
{

#ifdef OP_DUMP
	printf("RECV OP[%s]\n", __FUNCTION__);
#endif

	return  0;
}

INT32 InitServerActions() {
	actions[C_CHECK_VERSION] = CheckVersionAction;


	return 0;
}

const ServerAction GetAction(UINT16 opcode)
{
	if (opcode >= OPCODE_MAX) {
		return nullptr;
	}

	return actions[opcode];
}