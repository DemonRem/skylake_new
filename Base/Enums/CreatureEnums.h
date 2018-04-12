#ifndef CREATUREENUMS_H
#define CREATUREENUMS_H

#include "../TypeDefs.h"

enum ECreatureType
{
	CT_NPC,
	CT_PLAYER,
	CT_GM
};

enum ECreatureReaction : INT32
{
	Friendly = 1

};

enum ECreatureActionState :INT32
{
	STATE_NONCOMBAT = 0,
	STATE_COMBAT = 1,
	STATE_MOUNT = 3,
};

enum ECreatureStatus : INT32
{
	Dead = 0,
	Alive = 1,
	Ghost = 3 //admin only
};

enum ECreatureRelations : INT32
{
	R_NONE,

	R_Ally,
	R_Enemy,
	R_Pvp,
	R_Npc,
	R_PartyMember,
	R_GuildMember,
};

#endif