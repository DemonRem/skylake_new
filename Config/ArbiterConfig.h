#ifndef CONFIG_H
#define CONFIG_H

#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

#include "../Base/typeDefs.h"
#include "../Base/MathStructs.h"
#include "../Base/Atomic.h"
#include  "../Base/ServerDefs.h"

#pragma warning(disable: 4473)

struct ArbiterConfig {
	struct server_c
	{
		UINT32	id;
		UINT32	arbiterProfile;
		UINT16	worldServerListenPort;
		UINT16  maxPlayersPerAccount;

		char serverName[32];
		char worldServerListenIp[16];
		
	} static server;

	struct net_c
	{
		char	ip[16];
		UINT16	port;
	} static net;

	struct dir_c
	{
		char	dataNpc[FILENAME_MAX];
		char	dataCustomizingItems[FILENAME_MAX];
		char	dataNpcSkills[FILENAME_MAX];
		char	dataPlayerSkills[FILENAME_MAX];
		char	dataItems[FILENAME_MAX];
		char	dataAbnormalities[FILENAME_MAX];
		char	dataPassivities[FILENAME_MAX];
		char	dataPassivityCategories[FILENAME_MAX];
		char	dataEquipmentData[FILENAME_MAX];
		char	dataEquipmentEnchantData[FILENAME_MAX];
		char	dataWorld[FILENAME_MAX];
		char	dataScripts[FILENAME_MAX];
	} static dir;

	struct mysql_c
	{
		char	mysqlIp[16];
		char	mysqlUser[32];
		char	mysqlPassword[32];
		char	mysqlDbName[16];

		UINT32	mysqlPort;
	} static mysql;

	struct player_c
	{
		UINT32	startInventorySlotsCount;
		BOOL	soulbindingEnabled;

		UINT64	startInventoryGold;
		UINT64	maxInventoryGold;

		UINT64	startItems[PLAYER_START_ITEMS_MAX];
	} static player;

	struct start_c
	{
		Vector3	startPosition;
		INT16	startHeading;

		UINT64	startContinent;
		UINT64	startWorldMapWroldId;
		UINT64	startWorldMapGuardId;
		UINT64	startWorldMapSectionId;

		INT32	startArea;
		INT32	startChannel;

	} static player_start;

	struct chat_c
	{
		a_flag	enabled;
		a_flag	gmCommandsEnabled;
		a_flag	playerCanUserGmCommands;
	} static chat;

	struct account_c {
		UINT32  maxPlayers;
	} static account;
};

bool InitArbiterConfig(const char* fileName);

#endif
