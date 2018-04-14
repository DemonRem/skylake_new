#ifndef SERVER_ACTIONS_H
#define SERVER_ACTIONS_H

#include "../Base/typeDefs.h"

struct WorkerState;
struct ConnectionNetPartial;
typedef INT32(*ServerAction)(WorkerState * wState, ConnectionNetPartial* net);


INT32 InitServerActions();
const ServerAction GetAction(UINT16 opcode);

#endif
