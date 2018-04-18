#include "Core.h"

#include "../Base/SimpleStack.h"
#include "../Base/ServerDefs.h"
#include "../Base/IOCP.h"
#include "../Config/ArbiterConfig.h"
#include "../DataLayer/DBO.h"
#include "../Network/NetworkIO.h"
#include "../Base/MemoryStreams.h"

#include "Structs.h"
#include "ServerActions.h"

#include <memory>

#define WORKERROUTINE __stdcall
typedef  DWORD(WORKERROUTINE *WorkerSubroutine)(Work*);

WorkerSubroutine workerSubroutines[WorkerItemType_MAX];
CRITICAL_SECTION	connectionsLock;
static SimpleStack	freeIdsStack;
UINT8 recvBuffers[MAX_CONNECTIONS][CONNECTION_RECV_BUFFER_LEN];

ArbiterState arbiterState;
__declspec(thread) WorkerState wState;

Connection * GetNewConnection() noexcept {
	register Connection * out = nullptr;

	EnterCriticalSection(&connectionsLock);

	UINT64 freeId = freeIdsStack.pop();
	if (freeId != UINT64_MAX) {
		out = connections + freeId;
	}

	LeaveCriticalSection(&connectionsLock);

	return out;
}
const INT32 ReleaseConnection(UID id) noexcept {
	register INT32 result = FALSE;

	Account& account = accounts[id.id];
	Connection& conn = connections[id.id];
	ConnectionNetPartial& net = connectionNetData[id.id];

	//!TODO save, clear connection state here

	net.flags = EConnectionNetFlags::EConnectionNetFlags_None;
	net.workFlags = EWorkItemFlags_ShouldNotDelete;
	result = CloseSocket(net.sock);
	if (result) {
		//@TODO investigate and log
		return 1;
	}

	EnterCriticalSection(&connectionsLock);
	result = freeIdsStack.push(id.id);
	LeaveCriticalSection(&connectionsLock);

	return 0;
}

//@@@@@@@@@@@@@@@@@@ ACCEPT ROUTINE @@@@@@@@@@@@@@@@@@@@@@@@@@

inline BOOL OnNewConnection(SOCKET sock) {
	Connection * newConnection = GetNewConnection();
	if (!newConnection) {
		return 1;
	}

	ConnectionNetPartial * conectionNetInfo = GetConnectionNetData(newConnection->id);
	if (!conectionNetInfo) {
		return 2;
	}

	conectionNetInfo->sock = sock;

	std::unique_ptr<HandleNewConnection> w = std::make_unique<HandleNewConnection>(newConnection);
	if (PostWork(arbiterState.workQueue, w.get())) {
		//@TODO investigate and log
		return 3;
	}

	w.release();
	return 0;
}
DWORD WINAPI ArbiterAcceptRoutine(void* argv)
{
	SOCKET listenSock = arbiterState.acceptSock;
	WSANETWORKEVENTS WSAEvents;

	while (WAIT_OBJECT_0 != WaitForSingleObject(arbiterState.shutdownEvent, 0))
	{
		if (WSA_WAIT_TIMEOUT != WSAWaitForMultipleEvents(1, &arbiterState.acceptEvent, FALSE, 200, FALSE))
		{
			WSAEnumNetworkEvents(listenSock, arbiterState.acceptEvent, &WSAEvents);
			if ((WSAEvents.lNetworkEvents & FD_ACCEPT) && (0 == WSAEvents.iErrorCode[FD_ACCEPT_BIT]))
			{
				sockaddr_in clientInfo;
				INT32 addressSize = sizeof(clientInfo);

				SOCKET sock = accept(listenSock, (sockaddr*)&clientInfo, &addressSize);
				if (sock == INVALID_SOCKET) {
					//@TODO log
					continue;
				}

				INT32 result = OnNewConnection(sock);
				if (result) {
					//@TODO log
				}
			}
		}
	}

	printf("Accept routine shutdown\n");
	return 0;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//@@@@@@@@@@@@@@@@@@ WORKER SUBROUTINES @@@@@@@@@@@@@@@@@@@@@@

DWORD WORKERROUTINE _onNewConnection(HandleNewConnection* w) {
	if (!w) {
		return 1;
	}

	ConnectionNetPartial * netData = GetConnectionNetData(w->connection->id);
	if (!netData) {
		return 2;
	}

	//associate the socket with the workerQueue
	HANDLE iocp = CreateIoCompletionPort((HANDLE)netData->sock, arbiterState.workQueue, NULL, 0);
	if (iocp != arbiterState.workQueue) {
		INT32 result = ReleaseConnection(netData->id);
		if (result) {
			//@TODO investigate, log
		}

		return 3;
	}

	//we start the initializing process
	netData->AddFlag(EConnectionNetFlags_InitSent);

	INT32 result = StartInitProcess(netData);
	if (result) {
		//@TODO investigate, log
		INT32 result = ReleaseConnection(netData->id);
		if (result) {
			//@TODO investigate, log
		}

		printf("Failed to send init packet to new connection\n");
		return 4;
	}

	return 0;
}
DWORD WORKERROUTINE _onConnectInit(SendInit * w) {
	ConnectionNetPartial & net = connectionNetData[w->connectionId.id];

	/*if (!net.session.init_session()) {
		printf("Failed to init session for new connection\n");
		return 1;
	}*/

	net.session.GenerateSeverKeys();
	net.recvState = EConnectionRecvState_ClientKey1;
	net.wsaBuff.len = 128;

	INT32 result = PostRecv(&net);
	if (result) {
		//@TODO log 
		return 1;
	}

	return 0;
}
DWORD WORKERROUTINE _onServerKeySent(SendKey * w) {
	ConnectionNetPartial & net = connectionNetData[w->connectionId.id];

	if (!net.HasFlag(EConnectionNetFlags_SentKey1)) {
		net.AddFlag(EConnectionNetFlags_SentKey1);
		net.recvState = EConnectionRecvState_ClientKey2;

		net.wsaBuff.len = 128;
		INT32 result = PostRecv(&net); //recv client key 2
		if (result) {
			//@TODO log
			return 1;
		}

		return 0;
	}

	if (!net.HasFlag(EConnectionNetFlags_SentKey2)) {
		net.AddFlag(EConnectionNetFlags_SentKey2);
	}

	//connection is ready
	net.AddFlag(EConnectionNetFlags_Ready);

	if (!net.session.init_session()) {
		//@TODO log
		return 2;
	}

	Connection* mainConn = GetConnection(w->connectionId);
	mainConn->connected.test_and_set();

	net.recvState = EConnectionRecvState_PacketHead;
	net.wsaBuff.len = 4; //head size
	INT32 result = PostRecv(&net); //recv first packet head
	if (result) {
		//@TODO log
		return 1;
	}

	return 0;

}
DWORD WORKERROUTINE _onConnectionRecv(ConnectionNetPartial * w) {
	INT32 result;
	register EConnectionRecvState recvState = (EConnectionRecvState)w->recvState;
	switch (recvState)
	{
	case EConnectionRecvState_PacketHead: {

		//@TODO optimize 
		UINT8 *data = (UINT8*)w->recvBuffer;

		w->session.Decrypt(data, 4);

		w->packetSize = (UINT16)((data[1] << 8) | data[0]);
		w->opcode = (ClientOpcodes)((data[3] << 8) | data[2]);

		w->wsaBuff.len = w->packetSize - 4;
		w->wsaBuff.buf = (CHAR*)w->recvBuffer + 4;

		w->recvState = EConnectionRecvState_PacketBody;
		INT32 result = PostRecv(w);
		if (result) {
			result = ReleaseConnection(w->id);
			if (result) {
				//@TODO log
			}

			return 1;
		}

	}break;
	case EConnectionRecvState_PacketBody: {

		UINT8 *data = (UINT8*)w->wsaBuff.buf;

		register UINT16 delta = (UINT16)(w->packetSize - wState.numberOfBytesTransfered) - 4;
		if (delta) { //get remaining packet data
			data += wState.numberOfBytesTransfered;

			w->wsaBuff.buf = (CHAR*)data;
			w->wsaBuff.len = delta;

			w->recvState = EConnectionRecvState_PacketHead;
			INT32 result = PostRecv(w);
			if (result) {
				result = ReleaseConnection(w->id);
				if (result) {
					//@TODO log
				}

				return 1;
			}

			return 0;
		}

		//got whole packet , decrypt it and handle it
		w->session.Decrypt(w->recvBuffer + 4, w->packetSize - 4);

		ServerAction action = GetAction(w->opcode);
		if (action) {
			INT32 result = action(&wState, w);
			if (result) {
				//@TODO log

				result = ReleaseConnection(w->id);
				if (result) {
					//@TODO log
				}
			}
		}
		else {
			printf("UNKNOWN OPCODE[%d]\n", w->opcode);
		}

#ifdef PRINT_PACKETS
		print_packet(w->recvBuffer, w->packetSize);
#endif

		//@TODO , create HandlePacketAsyncWorkItem to handle packets async if not in_lobby


		//@TODO get opcode handler and runt it sync

		w->recvState = EConnectionRecvState_PacketHead;
		w->wsaBuff.len = 4;
		w->wsaBuff.buf = (CHAR*)w->recvBuffer;
		INT32 result = PostRecv(w);
		if (result) {
			result = ReleaseConnection(w->id);
			if (result) {
				//@TODO log
			}

			return 1;
		}
	}break;
	case EConnectionRecvState_ClientKey1: {
		if (memcpy_s(w->session.ClientKey1, 128, w->recvBuffer, 128)) {
			return 3;
		}

		result = SendServerKey(w, 1);
		if (result) {
			//@TODO log
			return 1;
		}

	}break;
	case EConnectionRecvState_ClientKey2: {
		if (memcpy_s(w->session.ClientKey2, 128, w->recvBuffer, 128)) {
			return 4;
		}

		result = SendServerKey(w, 2);
		if (result) {
			//@TODO log
			return 1;
		}
	}	break;
	default:
		//@TODO log
		return 4;
		break;
	}


	return 0;
}
DWORD WORKERROUTINE _onDataSentToConnection(SendToConnection * w) {

#ifdef DEBUG_PACKETS
	printf("sent data size[ %d ] opcode[ %d ]\n", w->size, w->opcode);
#endif


	return 0;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

DWORD WINAPI ArbiterWorkerRoutine(void* argv) {
	wState.mysqlConnection = (sql::Connection *)argv;
	if (!wState.mysqlConnection) {
		printf("Worker::Bad connection object\n");
		return 1;
	}

	while (1) {
		register ULONG result = GetQueuedCompletionStatus(arbiterState.workQueue, &wState.numberOfBytesTransfered, &wState.completionKey, (OVERLAPPED**)&wState.work, INFINITE);
		if (!result) {
			result = WSAGetLastError();
			printf("Worker::Fatal error ERROR:%d\n", result);
			break;
		}

		if (WAIT_OBJECT_0 == WaitForSingleObject(arbiterState.shutdownEvent, 0) || ERROR_ABANDONED_WAIT_0 == WSAGetLastError()) {
			break;
		}

		if (!wState.work) {
			//@TODO handle
			continue;
		}

		register WorkerSubroutine handler = nullptr;
		if (wState.work->type >= WorkerItemType_MAX || !(handler = workerSubroutines[wState.work->type])) {
			//@TODO log
			printf("unknown work item %ld\n", wState.work->type);
		}
		else {
			result = handler(wState.work);
			if (result) {
				//@TODO investigate/log
			}
		}

		if (!wState.work->HasWorkFlag(EWorkItemFlags_ShouldNotDelete)) {
			//@TODO better deallocation logic here
			delete wState.work;
		}
	}
	printf("Worker shutdown\n");
	return 0;
}

void InitWorkerSoubroutines() {
	workerSubroutines[WorkItemType_RecvFromConnection] = (WorkerSubroutine)_onConnectionRecv;
	workerSubroutines[WorkItemType_SendToConnection] = (WorkerSubroutine)_onDataSentToConnection;
	workerSubroutines[WorkItemType_NewConnection] = (WorkerSubroutine)_onNewConnection;
	workerSubroutines[WorkItemType_SendInit] = (WorkerSubroutine)_onConnectInit;
	workerSubroutines[WorkItemType_SendKey] = (WorkerSubroutine)_onServerKeySent;
}
const BOOL InitArbiterCore() {
	InitializeCriticalSection(&connectionsLock);
	InitWorkerSoubroutines();
	InitServerActions();

	if (!freeIdsStack.InitStack(MAX_CONNECTIONS)) {
		printf("Failed to init FreeIdsStack\n");

		return FALSE;
	}

	for (UINT64 i = 1; i < MAX_CONNECTIONS; i++) {
		freeIdsStack.push(MAX_CONNECTIONS - i);

		connections[i].id.id = i;
		connectionNetData[i].id.id = i;
		accounts[i].id.id = i;

		//link the recv buffer
		connectionNetData[i].wsaBuff.buf = (CHAR*)recvBuffers[i];
		connectionNetData[i].recvBuffer = recvBuffers[i];
		connectionNetData[i].AddWorkFlag(EWorkItemFlags_ShouldNotDelete);
	}

	//constexpr int test = (((sizeof(Connection) + sizeof(ConnectionNetPartial) + sizeof(Account)) * MAX_CONNECTIONS) / 1024) / 1024;

	arbiterState.workQueue = CreateIoCompletionPort((HANDLE)INVALID_HANDLE_VALUE, NULL, NULL, ARBITER_WORKERS_COUNT);
	if (arbiterState.workQueue == NULL) {
		printf("Failed to create IOCP\n");
		return 13;
	}

	INT32 result = WSAStartup(MAKEWORD(2, 2), &arbiterState.wsa);
	if (result) {
		printf("WSAStartup failed!\n");
		return 1;
	}

	arbiterState.acceptSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (arbiterState.acceptSock == INVALID_SOCKET) {
		printf("Failed to create accept socket\n");
		return 2;
	}

	SOCKADDR_IN arbiterEndpoint;
	arbiterEndpoint.sin_family = AF_INET;
	arbiterEndpoint.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //@TODO set from config data
	arbiterEndpoint.sin_port = htons(TERA_SERVER_PORT);

	result = bind(arbiterState.acceptSock, (const sockaddr*)&arbiterEndpoint, sizeof(sockaddr));
	if (result == SOCKET_ERROR) {
		printf("Failed to bind to port\n");
		return 3;
	}
	result = listen(arbiterState.acceptSock, SOMAXCONN);
	if (result) {
		printf("Failed to listen()\n");
		return 4;
	}

	arbiterState.acceptEvent = WSACreateEvent();
	if (arbiterState.acceptEvent == WSA_INVALID_EVENT) {
		printf("Failed to create accept event\n");
		return 5;
	}

	result = WSAEventSelect(arbiterState.acceptSock, arbiterState.acceptEvent, FD_ACCEPT);
	if (result) {
		result = WSAGetLastError();
		printf("Failed to select accept event. WSAERROR:%d\n", result);
		return 6;
	}

	arbiterState.shutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (arbiterState.acceptEvent == NULL) {
		printf("Failed to create shutdown event\n");
		return 7;
	}

	MySqlDriver * mysqlDriver = GetMysqlDriver();
	if (!mysqlDriver->InitDriver(
		ArbiterConfig::mysql.mysqlIp,
		ArbiterConfig::mysql.mysqlUser,
		ArbiterConfig::mysql.mysqlPassword,
		ArbiterConfig::mysql.mysqlDbName)) {
		printf("Failed to initialize mysql driver.\n");
		return 8;
	}

	arbiterState.acceptThread = CreateThread(NULL, 0, ArbiterAcceptRoutine, NULL, 0, NULL);
	if (arbiterState.acceptThread == NULL) {
		printf("Failed to create accept thread\n");
		return 9;
	}

	arbiterState.workerThreads = new HANDLE[ARBITER_WORKERS_COUNT];
	for (UINT32 i = 0; i < ARBITER_WORKERS_COUNT; i++) {

		sql::Connection *conn = mysqlDriver->NewConnection();
		if (!conn) {
			printf("Faield to open connection to db. Server might be down or the config is wrong.\n");
			return 10;
		}

		arbiterState.workerThreads[i] = CreateThread(NULL, 0, ArbiterWorkerRoutine, conn, 0, NULL);
		if (!arbiterState.workerThreads[i]) {
			printf("Failed to create worker thread\n");
			return 11;
		}
	}

	return 0;
}

