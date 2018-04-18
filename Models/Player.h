#ifndef PLAYER_H
#define PLAYER_H

#include "../Base/win32.h"
#include "../Base/typeDefs.h"
#include "../Base/Atomic.h"
#include "../Base/ServerDefs.h"
#include "../Base/Enums/PlayerEnum.h"

#include "../Models/Stats.h"

struct Connection;
struct Account;

struct Player {
	UINT32			dbId;
	DWORD			flags;

	Connection *	connection;
	Account *		account;

	a_single		x;
	a_single		y;
	a_single		z;
	a_int16			h;

	a_uint32		continentId;
	a_uint32		areaId;
	a_int32			channel;

	//@TODO emmbed class, race, gender into an uin32 bitfiled
	EPlayerClass	pClass;
	EPlayerRace		pRace;
	EPlayerGender	pGender;

	UINT32			worldMapWorldId;
	UINT32			worldMapGuardId;
	UINT32			worldMapSectionId;

	UINT64			exp;
	UINT64			restedExp;

	UINT64			level;

	UINT64			banTime;
	UINT64			lastOnline;
	UINT64			createdAt;

	char			name[PLAYER_NAME_MAX_LENGTH];

	UINT8			details1[PLAYER_DETAILS_1_BUFFER_SIZE];
	UINT8			details2[PLAYER_DETAILS_2_BUFFER_SIZE];
	UINT8			details3[PLAYER_DETAILS_3_BUFFER_SIZE];

	UINT32			lobbyIndex;

	//player stats
	CRITICAL_SECTION lock;

	GeneralPlayerStats	gStats;
	PlayerStats			pStats;

	inline const BOOL HasFlag(const EPlayerFlags flag) const noexcept {
		return flags & flag;
	}	
	inline void AddFlag(const EPlayerFlags flag) noexcept {
		flags |= flag;
	}
	inline void RemoveFlag(const EPlayerFlags flag) noexcept {
		flags &= !flag;
	}
};
#endif