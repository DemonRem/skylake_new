#ifndef IOCP_HANDLING_H
#define IOCP_HANDLING_H

#include "typeDefs.h" 
#include "win32.h"
#include "winsock.h"
#include "WorkItems.h"

#include <stdio.h>

FORCEINLINE BOOL PostWork(HANDLE queue, Work * w) {
	register INT32 result = PostQueuedCompletionStatus(queue, 1, NULL, (OVERLAPPED*)w);
	if (!result) {
		result = WSAGetLastError();
		printf("Failed to PostWork, WSAERROR:%d\n", result);
		//@TODO investigate and log
		return 1;
	}

	return 0;
}

#endif

