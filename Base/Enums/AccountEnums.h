#ifndef ACCOUNTENUMS_H
#define ACCOUNTENUMS_H

#include "../typeDefs.h"

enum EAccountFlags :ULONG {
	EAccountFlags_None = 0,

	EAccountFlags_IsGM = 1 << 0,
	EAccountFlags_IsVIP = 1 << 1,
	EAccountFlags_IsPremium = 1 << 2,

};

#endif
