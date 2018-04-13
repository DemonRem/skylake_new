#ifndef SERVER_ACTIONS_H
#define SERVER_ACTIONS_H

#include "../Base/typeDefs.h"
#include "../Opcodes/Opcodes.h"

#include "Structs.h"

typedef INT32(*ServerAction)(WorkerState * wState);



INT32 InitServerActions();
const ServerAction GetAction(UINT16 opcode);

#endif
