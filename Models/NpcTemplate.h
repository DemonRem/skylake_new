#ifndef NPCTEMPLATE_H
#define NPCTEMPLATE_H

#include "../Base/typeDefs.h"
#include "../Base/Enums/NpcEnums.h"

#include <vector>

#define NPC_ALT_ANIMATIONS_MAX 16
#define NPC_ALT_ANIMATION_NAME_SIZE 32

struct NpcNamePlate
{
	UINT32	namePlateHeight;
	UINT32	deathNamePlateHeight;
};

struct NpcStat
{
	UINT32 level;
	UINT32 base_max_hp;
};

struct NpcAltAnimation
{
	ENpcAltAnimType type;
	char name[NPC_ALT_ANIMATION_NAME_SIZE];
};

struct NpcTemplate
{
	ENpcFlags flags;
	float	scale;

	UINT32	gender;
	UINT32	huntingZoneId;
	UINT32	spawnScriptId;
	UINT32	despawnScriptId;
	UINT32	basicActionId;
	UINT32	parentId;
	UINT32	resourceSize;
	UINT32	local_index;


	//@TODO DOD
	//npc_name_plate
	//	namePlate;
	//npc_stat
	//	stats;
	//npc_alt_animation				altAnimations[NPC_ALT_ANIMATIONS_MAX];

	EMobSize						size;
	ENpcRace						race;
	ENpcResourceType				resourceType;

	inline const BOOL HasFlag(const ENpcFlags flag) const noexcept {
		return flags & flag;
	}
};

#endif
