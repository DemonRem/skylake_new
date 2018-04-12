#ifndef AWOPCODE_H
#define AWOPCODE_H

//ARBITER SERVER <---> WORLD SERVER COMMUNICATION OPCODES

#include "../Base/TypeDefs.h"

enum AWOpcodes : UINT16 {
	C_W_INIT = 1,
	S_W_INIT,
	C_W_CLOSE,
	S_W_CLOSE,
	S_W_PLAYER_ENTER_WORLD,
	S_W_PLAYER_LEAVE_WORLD,
	S_W_PLAYER_MOVE,
	C_W_PLAYER_ENTER_WORLD,
	C_W_PLAYER_LEAVE_WORLD,
	C_W_PLAYER_MOVE_BROADCAST,
	S_W_GET_VISIBLE_PLAYERS,
	S_W_GET_VISIBLE_PLAYERS_NO_DATA,
	C_W_GET_VISIBLE_PLAYERS,
	C_W_GET_VISIBLE_PLAYERS_NO_DATA,
	C_W_PLAYER_SPAWN_BROADCAST,
	C_W_PLAYER_DESPAWN_BROADCAST,
	C_W_PLAYER_DESPAWN_ME_BROADCAST,
	C_W_PLAYER_SPAWN_ME_BROADCAST,
	S_W_ON_COMBAT_ENTER,
	C_W_ON_COMBAT_ENTER,
	S_W_ON_COMBAT_LEAVE,
	C_W_ON_COMBAT_LEAVE,
	S_W_START_SKILL,
	C_W_ACTION_STAGE,
	C_W_ACTION_END,
	S_W_PLAYER_NEW_SKILL,
	C_W_PLAYER_NEW_SKILL_RESULT,
	C_W_PLAYER_CHANGE_WORLD,
	S_W_PLAYER_CHANGE_WORLD,
	S_W_PLAYER_ENTER_NEW_WORLD,
	C_W_PLAYER_ENTER_NEW_WORLD,
	S_W_UPDATE_PLAYER_STATS,
	C_W_GET_PLAYER_STATS,
	C_W_SEND_TO_SINGLE,
	OP_MAX
};
#endif
