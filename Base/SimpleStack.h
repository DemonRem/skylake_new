#ifndef SIMPLE_STACK_H
#define SIMPLE_STACK_H

#include "typeDefs.h" 

struct SimpleStack {
	UINT32 size;
	UINT32 top;
	UINT64 *data;

	SimpleStack() {
		data = nullptr;
		size = 0;
		top = 0;
	}
	~SimpleStack();

	const BOOL InitStack(UINT32 size);
	const inline BOOL push(UINT64 t) noexcept {
		if (top + 1 >= size) {
			return FALSE;
		}

		data[top++] = t;

		return TRUE;
	}
	const inline UINT64 pop() noexcept {
		if (top - 1 < 0) {
			return UINT64_MAX;
		}

		return data[--top];
	}
};

#endif
