#ifndef PASSIVITY_ENUMS_H
#define PASSIVITY_ENUMS_H

#include "../TypeDefs.h"

enum EPassivityType : UINT32
{
	EPassivityType_INCREASE_MAX_HP = 1,
	EPassivityType_INCREASE_MAX_MP = 2,
	EPassivityType_INCREASE_POWER = 3,
	EPassivityType_INCREASE_ENDURANCE = 4,
	EPassivityType_INCREASE_MOVEMENT_SPEED = 5,
	EPassivityType_INCREASE_CRIT_FACTOR = 6,
	EPassivityType_INCREASE_DAMAGE_BY = 152,
	EPassivityType_INCREASE_IMPACT_FACTOR = 8,
	EPassivityType_INCREASE_BALANCE_FACOTR = 9,
	EPassivityType_INCREASE_WEAKENING_APPLY_RATE = 10,
	EPassivityType_INCREASE_PERIODIC_APPLY_RATE = 11,
	EPassivityType_INCREASE_STUN_APPLY_RATE = 12,
	EPassivityType_INCREASE_WEAKENING_RESISTANCE = 14,
	EPassivityType_INCREASE_PERIODIC_RESISTANCE = 15,
	EPassivityType_INCREASE_STUN_RESISTANCE = 16,
	EPassivityType_INCREASE_CRIT_POWER = 19,
	EPassivityType_SKILLS_PRODUCES_LESS_AGGRO = 20,
	EPassivityType_INCREASE_MP_REPLENISHMENT = 21,
	EPassivityType_INCREASE_ATTACK_SPEED = 25,
	EPassivityType_REOVERS_HP_EVERY_5_SECONDS = 51,
	EPassivityType_REOVERS_MP_EVERY_5_SECONDS = 52,
	EPassivityType_INCREASE_GATHERING_SKILL = 64,
	EPassivityType_INCREASE_PLANT_HARVEST_SPEED = 65,
	EPassivityType_INCREASE_GATHERING_SPEED_ARUN = 67,
	EPassivityType_INCREASE_ATTACK_SPEED_DECREASE_SKILL_COOLDOWN = 71,
	EPassivityType_INCREASE_KNOCKDOWN_RESISTANCE_WHILE_SKILL = 74,
	EPassivityType_REFLECT_DAMAGE_TO_ATTACKER = 203,
	EPassivityType_INCREASE_CRAFTING_SPEED = 204,
	EPassivityType_CHANCE_REPLENISH_MP_COMBAT_ENTER = 207,
	EPassivityType_DECREASE_DURATION_OF_STUN = 228, //??
	EPassivityType_INCREASE_PVP_DAMAGE = 176,
	EPassivityType_DECREASE_PVP_DAMAGE = 113,
	EPassivityType_DECREASE_DAMAGE_TAKEN = 102,


	EPassivityType_DISSIPATE_EFFECT_ETCHING = 1000,
	EPassivityType_DISABLE = 1001,//2 unk
	//MORE TODO

	EPassivityType_MAX
};

enum EPassivityFlags : UINT16 {
	EPassivityFlags_JudgmentOnce = 1 << 0,
	EPassivityFlags_BalancedByTargetCount  = 1 << 1
};

#endif
