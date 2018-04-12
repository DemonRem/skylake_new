#ifndef CONNEcIONENUMS_H
#define CONNEcIONENUMS_H

#include "../TypeDefs.h"

//connection phase
enum EConnectionRecvState : UINT16
{
	EConnectionRecvState_PacketHead = 0,
	EConnectionRecvState_PacketBody = 1,

	EConnectionRecvState_ClientKey1 = 2,
	EConnectionRecvState_ClientKey2 = 3,

};

enum EConnectionNetFlags : ULONG {
	EConnectionNetFlags_None = 0,
	EConnectionNetFlags_InitSent = 1 << 0,
	EConnectionNetFlags_SentKey1 = 1 << 1,
	EConnectionNetFlags_RecvKey1 = 1 << 2,
	EConnectionNetFlags_SentKey2 = 1 << 3,
	EConnectionNetFlags_RecvKey2 = 1 << 4,


	EConnectionFlags_Ready = 1 << 5,

};

enum EConnectionFlags : ULONG {

};

#endif
