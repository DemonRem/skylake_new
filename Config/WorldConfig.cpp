#include "worldConfig.h"
#include "serverConfig.h"

#include "../Base/typeDefs.h"
#include "../Base/Utils.h"
#include "../Base/StringUtils.h"
#include "../Base/win32.h"

#include <fstream>

WorldConfig::server_c			WorldConfig::server;
WorldConfig::gameplay_c			WorldConfig::gameplay;
WorldConfig::environment_c		WorldConfig::environment;


void  config_defaults() {
	WorldConfig::server.name = "STEPSTONE_ISLE[DEFAULT-CONFIG]";
	strcpy(WorldConfig::server.arbiter_ip, "127.0.0.1");
	WorldConfig::server.area_id = 1;
	WorldConfig::server.continent_id = 5;
	WorldConfig::server.arbiter_port = 2000;
	WorldConfig::server.channel_id = 1;
	WorldConfig::server.worker_thread_count = 1;
	WorldConfig::server.active_thread_count = 1;

	WorldConfig::gameplay.hp_combat_regen_rate = 50;
	WorldConfig::gameplay.mp_combat_regen_rate = 20;

	WorldConfig::server.player_skills_file = "./data/playerSkills.bin";
	WorldConfig::server.npc_skills_file = "./data/npcSkills.bin";
	WorldConfig::server.start_mode = SERVER_START_TEST;
}
bool  config_load() {
	if (!file_exists("config.slc")) {
		MB_SHOW_WARNING_T("Could not find 'config.slc' file!", "CONFIG FILE?");
		return  false;
	}

	config_defaults();

	std::fstream file = std::fstream("config.slc");
	if (!file.is_open()) {
		MB_SHOW_ERROR_T("Could not open 'config.slc' file!", "CONFIG FILE?");
		return false;
	}


	SYSTEM_INFO s_info;
	GetSystemInfo(&s_info);
	UINT32 line_c = 0;
	std::string what;
	std::string line;
	while (!file.eof()) {
		std::getline(file, line); line_c++;
		if (stringStartsWith(line, "server.event_system_thread_count")) {
			if (s_info.dwNumberOfProcessors == 1) {
				printf("COULD NOT SET 'event_system_thread_count', NO OF CORES ON THE CPU[%d]\n", s_info.dwNumberOfProcessors);
				continue;
			}

			if (EOF == sscanf(line.c_str(), "server.event_system_thread_count = %d", &WorldConfig::server.active_thread_count)) {
				what = "server.event_system_thread_count = [1," + std::to_string(s_info.dwNumberOfProcessors) + "]";
				goto error_proc;
			}

			if (WorldConfig::server.active_thread_count == 0) {
				WorldConfig::server.active_thread_count = 1;
			}
			else if (WorldConfig::server.active_thread_count > s_info.dwNumberOfProcessors) {
				printf("YOU CAN NOT SET [%d] THREADS FOR THE EVENT SYSTEM, THATS MORE THAN CORE_COUNT/2!!\n");
				WorldConfig::server.active_thread_count = s_info.dwNumberOfProcessors;
				printf("EVENT_SYSTEM_THREAD_COUNT=%d\n", WorldConfig::server.active_thread_count);
			}
		}
		if (stringStartsWith(line, "server.active_thread_count")) {
			if (s_info.dwNumberOfProcessors == 1) {
				printf("COULD NOT SET 'active_thread_count', NO OF CORES ON THE CPU[%d]\n", s_info.dwNumberOfProcessors);
				continue;
			}

			if (EOF == sscanf(line.c_str(), "server.active_thread_count = %d", &WorldConfig::server.worker_thread_count)) {
				what = "server.active_thread_count = [1," + std::to_string(s_info.dwNumberOfProcessors) + "]";
				goto error_proc;
			}

			if (WorldConfig::server.worker_thread_count == 0) {
				WorldConfig::server.worker_thread_count = 1;
			}
			else if (WorldConfig::server.worker_thread_count > s_info.dwNumberOfProcessors) {
				printf("YOU CAN NOT SET [%d] THREADS FOR THE ACTIVE SERVER, THATS MORE THAN CORE_COUNT/2!!\n");
				WorldConfig::server.worker_thread_count = s_info.dwNumberOfProcessors;
				printf("ACTIVE_SERVER_THREAD_COUNT=%d\n", WorldConfig::server.worker_thread_count);
			}
		}
		else if (stringStartsWith(line, "server.arbiter_ip")) {
			UINT32 ip[4];
			if (4 != sscanf(line.c_str(), "server.arbiter_ip = %d.%d.%d.%d", &ip[0], &ip[1], &ip[2], &ip[3])) {
				what = "server.arbiter_ip = [1-255].[1-255].[1-255].[1-255]";
				goto error_proc;
			}
			std::string f_ip = std::to_string(ip[0]) + '.' + std::to_string(ip[1]) + '.' + std::to_string(ip[2]) + '.' + std::to_string(ip[3]);
			if (f_ip.size() >= 16) {
				what = "server.arbiter_ip = [1-255].[1-255].[1-255].[1-255]";
				goto error_proc;
			}
			strcpy_s(WorldConfig::server.arbiter_ip, f_ip.c_str());
		}
		else if (stringStartsWith(line, "server.arbiter_port")) {
			if (EOF == sscanf(line.c_str(), "server.arbiter_port = %hu", &WorldConfig::server.arbiter_port) || WorldConfig::server.arbiter_port == 0) {
				what = "server.arbiter_port = [positive integer]";
				goto error_proc;
			}

		}
		else if (stringStartsWith(line, "server.area_file")) {
			char buffer[_MAX_DIR];
			INT32 result = sscanf(line.c_str(), "server.area_file = %s", buffer);
			if (!result || result == EOF) {
				what = "invalid server.area_file value MAX_DIR_LENGTH = " + std::to_string(_MAX_DIR);
				goto error_proc;
			}
			if (!file_exists(buffer)) {
				what = "area file not found!!";
				goto error_proc;
			}
			WorldConfig::server.area_file = buffer;
		}
		else if (stringStartsWith(line, "server.player_skills_file")) {
			char buffer[_MAX_DIR];
			INT32 result = sscanf(line.c_str(), "server.player_skills_file = %s", buffer);
			if (!result || result == EOF) {
				what = "invalid server.player_skills_file value MAX_DIR_LENGTH = " + std::to_string(_MAX_DIR);
				goto error_proc;
			}
			if (!file_exists(buffer)) {
				what = "player_skills_file not found!!";
				goto error_proc;
			}
			WorldConfig::server.player_skills_file = buffer;
		}
		else if (stringStartsWith(line, "server.npc_skills_file")) {
			char buffer[_MAX_DIR];
			INT32 result = sscanf(line.c_str(), "server.npc_skills_file = %s", buffer);
			if (!result || result == EOF) {
				what = "invalid server.npc_skills_file value MAX_DIR_LENGTH = " + std::to_string(_MAX_DIR);
				goto error_proc;
			}
			if (!file_exists(buffer)) {
				what = "npc_skills_file not found!!";
				goto error_proc;
			}
			WorldConfig::server.npc_skills_file = buffer;
		}
	}
	return true;

error_proc:
	std::string error = "ERROR LINE[" + std::to_string(line_c) + "][" + line + "] -->[" + what + "]";
	MB_SHOW_ERROR_T(error.c_str(), "ERROR[CONFIG.INI PARSER]");
	return false;
}
