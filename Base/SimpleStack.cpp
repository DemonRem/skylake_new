#include "SimpleStack.h"

SimpleStack::~SimpleStack()
{
	if (data) {
		delete[] data;
		data = nullptr;
	}
}

const BOOL SimpleStack::InitStack(UINT32 size)
{
	if (data) {
		delete[] data;
		data = nullptr;
	}

	this->size = size;
	top = 0;

	data = new UINT64[size];
	if (!data) {
		return FALSE;
	}

	return TRUE;
}
