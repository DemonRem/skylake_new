#ifndef CLUSTER_ENUM_H
#define CLUSTER_ENUM_H

#include "../TypeDefs.h"

enum ClusterTaskType : UINT32 {
	C_TASK_LOCATION,
	C_TASK_PLAYER_ENTER_WORLD,
	C_TASK_CELL_CANGE,

	C_TASK_MAX
};

#endif
