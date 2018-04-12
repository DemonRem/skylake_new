#ifndef PLAYER_ENUM_H
#define PLAYER_ENUM_H

#include "../TypeDefs.h"

enum EPlayerClass : UINT32
{
	EPlayerClass_WARRIOR = 0,
	EPlayerClass_LANCER = 1,
	EPlayerClass_SLAYER = 2,
	EPlayerClass_BERSERKER = 3,
	EPlayerClass_SORCERER = 4,
	EPlayerClass_ARCHER = 5,
	EPlayerClass_PRIEST = 6,
	EPlayerClass_MYSTIC = 7,
	EPlayerClass_REAPER = 8,
	EPlayerClass_ENGINEER = 9,//gunner
	EPlayerClass_FIGHTER = 10, //brawler
	EPlayerClass_ASSASSIN = 11, //ninja
	EPlayerClass_VALKYRIE = 12,

	EPlayerClass_MAX
};

enum EPlayerGender :UINT32
{
	EPlayerGender_MALE = 0,
	EPlayerGender_FEMALE = 1,

	EPlayerGender_MAX
};

enum EPlayerRace : UINT32
{
	EPlayerRace_HUMAN = 0,
	EPlayerRace_HIGHELF = 1,
	EPlayerRace_AMAN = 2,
	EPlayerRace_CASTANIC = 3,
	EPlayerRace_ELIN = 4,
	EPlayerRace_POPORI = 5,
	EPlayerRace_BARAKA = 6,

	EPlayerRace_MAX
};

enum EPlayerFlags :ULONG {

};

#endif

