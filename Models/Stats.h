#ifndef STATS_H
#define STATS_H

#include "../Base/typeDefs.h"

struct GeneralPlayerStats {
	INT32	level;
	float	infamy;

	float	decreaseCooldown;
	float	decrSlowTime;

	float	harvestSpeed;
	float	miningSpeed;
	float	gatherSpeed;
	float	craftSpeed;

	float	harvestSkill;
	float	miningSkill;
	float	gatherSkill;
};

struct PlayerStats {
	INT32	attack;
	INT32	bonus_attack;

	INT32	defense;
	INT32	bonus_defense;

	INT32	impact;
	INT32	bonus_impact;

	INT32	balance;
	INT32	bonus_balance;

	INT32	max_hp;
	INT32	bonus_max_hp;

	float	hpRegenEnterCombat;
	float	increaseHealValue;

	INT32	five_hp_regen;
	INT32	five_mp_regen;

	INT32	three_hp_regen;
	INT32	three_mp_regen;

	INT32	max_mp;
	INT32	bonus_max_mp;
	float	mpRegenEnterCombat;
	float	hitMpRegen;

	INT32	power;
	INT32	bonus_power;

	INT32	endurance;
	INT32	bonus_endurance;

	INT32	impact_factor;
	INT32	bonus_impact_factor;

	INT32	balance_factor;
	INT32	bonus_balance_factor;

	INT32	attack_speed;
	INT32	bonus_attack_speed;

	INT32	run_speed;
	INT32	bonus_run_speed;

	INT32	movement_speed;
	INT32	bonus_movement_speed;

	INT32	special;
	INT32	bonus_special;

	INT32	specialRegenRate;
	INT32	specialRegen;

	float	crit_power;
	float	bonus_crit_power;

	float	crit_rate;
	float	bonus_crit_rate;

	float	crit_resist;
	float	bonus_crit_resist;

	float	stun_rate;
	float	bonus_stun_rate;
	float	damageStun;

	float	stun_resist;
	float	bonus_stun_resist;
	float	defenseStun;

	float	poison_rate;
	float	bonus_poison_rate;

	float	poison_resist;
	float	bonus_poison_resist;

	float	weakening_rate;
	float	bonus_weakening_rate;

	float	weakening_resist;
	float	bonus_weakening_resist;

	float	defenseEnrage;
	float	defenseKd;
	float	defenseFrontal;
	float	defenseBack;
	float	defencePvp;
	float	defenseAggro;

	float	damageEnrage;
	float	damageKd;
	float	damageFrontal;
	float	damagePvp;
	float	damageBack;
	float	damageAggro;

	float	reflectDamage;
	float	decreaseDamage;
};

BOOL ExchangeStats(GeneralPlayerStats * src, GeneralPlayerStats * dest);
BOOL ExchangeStats(PlayerStats * src, PlayerStats * dest);

#endif

