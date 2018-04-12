#ifndef LFE_TASK_ENUM_H
#define LFE_TASK_ENUM_H

#include "../TypeDefs.h"

enum LfeTaskType :UINT32 {
	LFE_TASK_REGEN_HP,
	LFE_TASK_REGEN_MP,
	LFE_TASK_DO_DAMAGE,

	LFE_TASK_MAX
};

#endif
