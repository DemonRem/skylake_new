#include "NetworkIO.h"

#include "../Models/Connection.h"
#include "../Base/WorkItems.h"
#include "../Base/MemoryStreams.h"

#include <memory>

//@TODO get an allocator for the send work items
#ifdef DEBUG_PACKETS
#include "../Base/Utils.h"
#endif // DEBUG_PACKETS

const CHAR INIT_BUFFER[4]{ 1,0,0,0 };

const INT32 StartInitProcess(ConnectionNetPartial* conn) {
	SendInit* packet = new SendInit(conn->id);

	packet->buff.len = 4;
	packet->buff.buf = (CHAR*)INIT_BUFFER;

	DWORD bytesSent = 0;
	INT32 result = WSASend(conn->sock, &packet->buff, 1, &bytesSent, 0, (OVERLAPPED*)packet, NULL);
	if (result == SOCKET_ERROR && ((result = WSAGetLastError()) != WSA_IO_PENDING)) {
		delete packet;

		return result;
	}
	else if (!result && !bytesSent) {
		delete packet;

		return 2;
	}

	return 0;
}
const INT32 SendServerKey(ConnectionNetPartial * conn, INT32 index) {
	std::unique_ptr<SendKey> packet = std::make_unique<SendKey>(conn->id);

	if (index == 1) {
		packet->buff.buf = (CHAR*)conn->session.ServerKey1;
	}
	else {
		packet->buff.buf = (CHAR*)conn->session.ServerKey2;
	}

	packet->buff.len = 128;

	DWORD bytesSent = 0;
	INT32 result = WSASend(conn->sock, &packet->buff, 1, &bytesSent, 0, (OVERLAPPED*)packet.get(), NULL);
	if (result == SOCKET_ERROR && ((result = WSAGetLastError()) != WSA_IO_PENDING)) {
		return 1;
	}
	else if (!result && !bytesSent) {
		return 2;
	}

	packet.release();
	return 0;
}
const INT32 PostSend(ConnectionNetPartial * conn, SendToConnection * packet) {

	conn->session.Encrypt((UINT8*)packet->buff.buf, (INT32)packet->buff.len);

	DWORD bytesSent = 0;
	INT32 result = WSASend(conn->sock, &packet->buff, 1, &bytesSent, 0, (OVERLAPPED*)packet, NULL);
	if (result == SOCKET_ERROR && ((result = WSAGetLastError()) != WSA_IO_PENDING)) {
		return 1;
	}
	else if (!result && !bytesSent) {
		return 2;
	}
	return 0;
}
const INT32 PostSend(ConnectionNetPartial * conn, UINT8 * data, UINT32 size) {
	std::unique_ptr<SendToConnection> packet = std::make_unique<SendToConnection>(conn->id);

	packet->buff.len = size;
	packet->buff.buf = (CHAR*)data;

	conn->session.Encrypt(data, (INT32)size);

	DWORD bytesSent = 0;
	INT32 result = WSASend(conn->sock, &packet->buff, 1, &bytesSent, 0, (OVERLAPPED*)packet.get(), NULL);
	if (result == SOCKET_ERROR && ((result = WSAGetLastError()) != WSA_IO_PENDING)) {
		return result;
	}
	else if (!result && !bytesSent) {
		return 2;
	}

	packet.release();
	return 0;
}
const INT32 PostSendStream(ConnectionNetPartial * conn, MemoryStream & pPacket) {
	SendToConnection * packet = new SendToConnection(conn->id);

	packet->buff.buf = (CHAR*)pPacket._raw;
	packet->buff.len = (ULONG)pPacket._size;

#ifdef DEBUG_PACKETS
	pPacket._pos = 0;

	packet->size = pPacket.ReadUInt16();
	packet->opcode = pPacket.ReadUInt16();

	printf("sending size[%d] opcode[%d]\n", packet->size, packet->opcode);
	print_packet(pPacket._raw, pPacket._size);

#endif // DEBUG_PACKETS


	conn->session.Encrypt((UINT8*)packet->buff.buf, (INT32)packet->buff.len);

	DWORD bytesSent = 0;
	INT32 result = WSASend(conn->sock, &packet->buff, 1, &bytesSent, 0, (OVERLAPPED*)packet, NULL);
	if (result == SOCKET_ERROR && ((result = WSAGetLastError()) != WSA_IO_PENDING)) {
		packet->Release();
		delete packet;
		return 1;
	}
	else if (!result && !bytesSent) {
		packet->Release();
		delete packet;
		return 2;
	}

	pPacket.Release();
	return 0;
}

const INT32 PostRecv(ConnectionNetPartial * conn) {
	DWORD bytesReceived = 0;
	DWORD flags = 0;
	INT32 result = WSARecv(conn->sock, &conn->wsaBuff, 1, &bytesReceived, &flags, (OVERLAPPED*)conn, NULL);
	if (result == SOCKET_ERROR && ((result = WSAGetLastError()) != WSA_IO_PENDING)) {
		return result;
	}
	else if (!result && !bytesReceived) {
		return 2;
	}

	return 0;
}
