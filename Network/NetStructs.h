#ifndef NETSTRUCTS_H
#define NETSTRUCTS_H

#include "../Base/typeDefs.h"
#include "../Opcodes/Opcodes.h"

#pragma pack(1)
struct LoginArbiter {
	const UINT16	size = 23;
	const UINT16	opcode = 23;
	const UINT16	a = 0;
	const UINT16	b = 0;
	const UINT8		c = 0;
	const UINT32	d = 0;
	const UINT32	e = 0;
	const UINT8		f = 0;
	const UINT16	g = 0;
	const UINT16	h = 0;
	const UINT8		i = 0;
};
#pragma pop()

#endif
