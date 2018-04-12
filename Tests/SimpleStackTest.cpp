#include "SimpleStackTest.h"

const BOOL DoSimpleStackTest()
{
	SimpleStack t;
	if (!t.InitStack(1024)) {
		return FALSE;
	}

	UINT64 v = 102;
	t.push(v);
	if (t.pop() != v) {
		return FALSE;
	}

	return TRUE;
}
