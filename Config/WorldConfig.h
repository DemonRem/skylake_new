#ifndef W_SERVER_CONFIG_H
#define W_SERVER_CONFIG_H

#define _CRT_SECURE_NO_WARNINGS

#include "../Base/typeDefs.h"

#include <string>

#pragma warning(disable: 4473)

#define SERVER_STEPSTONE_ISLE 512
#define SERVER_STEPSTONE_VELIKA 1

#define SERVER_CLUSTER_CELL_COUNT  SERVER_STEPSTONE_ISLE

struct WorldConfig {
	struct server_c {
		UINT32	active_thread_count;
		UINT32  worker_thread_count;
		UINT32	area_id;
		UINT32	continent_id;
		INT32	channel_id;
		UINT32	port;
		UINT32	use_config;
		UINT16	arbiter_port;
		INT32   start_mode;

		std::string name;
		std::string area_file;
		std::string data_file;
		std::string player_skills_file;
		std::string npc_skills_file;
		std::string	npc_file;

		char	arbiter_ip[16];
	}static server;

	struct gameplay_c {
		INT16 hp_regen_rate;
		INT16 mp_regen_rate;
		INT16 hp_combat_regen_rate;
		INT16 mp_combat_regen_rate;
	} static gameplay;

	struct environment_c {
		INT16 hp_regen_rate;
		INT16 mp_regen_rate;
		INT16 hp_combat_regen_rate;
		INT16 mp_combat_regen_rate;

	}static environment;
};

bool config_load();
#endif
