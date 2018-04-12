#include "arbiterConfig.h"

#include "../Base/StringUtils.h"
#include "ServerConfig.h"
#include "../Base/Enums/ConfigEnums.h"

#include <fstream>

bool InitArbiterConfig(const char* fileName)
{
	std::fstream file = std::fstream(fileName);
	if (!file.is_open())
		return false;

	for (UINT8 i = 0; i < 16; i++) {
		ArbiterConfig::server.worldServerListenIp[i] = '0';
	}

	std::string error_message;
	std::string line;
	UINT32 lineCount = 0;
	while (!file.eof())
	{
		std::getline(file, line);
		lineCount++;

		if ((line[0] == '/' && line[1] == '/') || (line[0] == '#')) {
			continue;
		}
		else if (stringStartsWith(line, "server.id"))
		{
			if (!sscanf(line.c_str(), "server.id= %d", &ArbiterConfig::server.id))
			{
				error_message = "wrong id format!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.name"))
		{
			if (!sscanf(line.c_str(), "server.name=%s", ArbiterConfig::server.serverName))
			{
				error_message = "server_name max 32 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.ip"))
		{
			if (!sscanf(line.c_str(), "server.ip= %s", ArbiterConfig::net.ip))
			{
				error_message = "wrong ip format!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.port"))
		{
			if (!sscanf(line.c_str(), "server.port= %hu", &ArbiterConfig::net.port))
				goto error_proc;
		}
		else if (stringStartsWith(line, "server.chat.enable_gm_commands"))
		{
			int val = 0;
			if (!sscanf(line.c_str(), "server.chat.enable_gm_commands= %d", &val))
			{
				error_message = "bad enable_gm_commands value! use '1' for [true] and '0' for [false]";
				goto error_proc;
			}

			if (val) { ArbiterConfig::chat.gmCommandsEnabled.test_and_set(); }
		}
		else if (stringStartsWith(line, "server.chat.enabled"))
		{
			int val = 0;
			if (!sscanf(line.c_str(), "server.chat.enabled= %d", &val))
			{
				error_message = "bad enabled value! use '1' for [true] and '0' for [false]";
				goto error_proc;
			}

			if (val) { ArbiterConfig::chat.enabled.test_and_set(); }
		}
		else if (stringStartsWith(line, "server.chat.player_can_user_use_gm_commands"))
		{
			int val = 0;
			if (!sscanf(line.c_str(), "server.chat.player_can_user_use_gm_commands= %d", &val))
			{
				error_message = "bad player_can_user_use_gm_commands value! use '1' for [true] and '0' for [false]";
				goto error_proc;
			}

			if (val) { ArbiterConfig::chat.playerCanUserGmCommands.test_and_set(); }
		}
		else if (stringStartsWith(line, "server.mysql.ip"))
		{
			if (!sscanf(line.c_str(), "server.mysql.ip= %s", ArbiterConfig::mysql.mysqlIp))
			{
				error_message = "wrong ip format!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.mysql.port"))
		{
			if (!sscanf(line.c_str(), "server.mysql.port= %d", &ArbiterConfig::mysql.mysqlPort))
			{
				error_message = "bad port value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.mysql.db_name"))
		{
			if (!sscanf(line.c_str(), "server.mysql.db_name= %s", ArbiterConfig::mysql.mysqlDbName))
			{
				error_message = "db_name max 16 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.mysql.username"))
		{
			if (!sscanf(line.c_str(), "server.mysql.username= %s", &ArbiterConfig::mysql.mysqlUser))
			{
				error_message = "username max 32 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.mysql.password"))
		{
			if (!sscanf(line.c_str(), "server.mysql.password= %s", &ArbiterConfig::mysql.mysqlPassword))
			{
				error_message = "password max 32 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.npc"))
		{
			if (!sscanf(line.c_str(), "server.dir.npc= %s", ArbiterConfig::dir.dataNpc))
			{
				error_message = "npcs dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.skills.player"))
		{
			if (!sscanf(line.c_str(), "server.dir.skills.player= %s", ArbiterConfig::dir.dataPlayerSkills))
			{
				error_message = "player skills dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.skills.npc"))
		{
			if (!sscanf(line.c_str(), "server.dir.skills.npc= %s", ArbiterConfig::dir.dataNpcSkills))
			{
				error_message = "npc skills dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.items"))
		{
			if (!sscanf(line.c_str(), "server.dir.items= %s", &ArbiterConfig::dir.dataItems))
			{
				error_message = "items dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.abnormalities"))
		{
			if (!sscanf(line.c_str(), "server.dir.abnormalities= %s", &ArbiterConfig::dir.dataAbnormalities))
			{
				error_message = "abnormalities dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.customizing_items"))
		{
			if (!sscanf(line.c_str(), "server.dir.customizing_items= %s", &ArbiterConfig::dir.dataCustomizingItems))
			{
				error_message = "customizing_items dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.passivities"))
		{
			if (!sscanf(line.c_str(), "server.dir.passivities= %s", &ArbiterConfig::dir.dataPassivities))
			{
				error_message = "passivities dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.passivity_categories"))
		{
			if (!sscanf(line.c_str(), "server.dir.passivity_categories= %s", &ArbiterConfig::dir.dataPassivityCategories))
			{
				error_message = "passivity categories dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.equipment_data"))
		{
			if (!sscanf(line.c_str(), "server.dir.equipment_data= %s", &ArbiterConfig::dir.dataEquipmentData))
			{
				error_message = "equipment_data dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.equipment_enchant_data"))
		{
			if (!sscanf(line.c_str(), "server.dir.equipment_enchant_data= %s", &ArbiterConfig::dir.dataEquipmentEnchantData))
			{
				error_message = "equipment_enchant_data dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.world"))
		{
			if (!sscanf(line.c_str(), "server.dir.world= %s", ArbiterConfig::dir.dataWorld))
			{
				error_message = "world dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "server.dir.scripts"))
		{
			if (!sscanf(line.c_str(), "server.dir.scripts= %s", ArbiterConfig::dir.dataScripts))
			{
				error_message = "scripts dir. max 259 characters!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.inventory.start_items"))
		{
			char buffer[1024];
			UINT32 i = 0;
			if (!sscanf(line.c_str(), "player.inventory.start_items= %s", buffer))
			{
				error_message = "start_items max 1023 characters!";
				goto error_proc;
			}


			char *ptr = strtok(buffer, ",");
			if (ptr == buffer) {

				if (strlen(ptr)) {
					ArbiterConfig::player.startItems[i] = atoll(ptr);
					ArbiterConfig::player.startItems[i] = atoll(ptr);
					if (!ArbiterConfig::player.startItems[i]) {
						error_message = "0 is not a valid item id";
						goto error_proc;
					}
				}
				else {
					error_message = "invalid value for start_items";
					goto error_proc;
				}
			}
			else {
				error_message = "invalid value for start_items";
				goto error_proc;
			}

			while (ptr) {
				i++;

				if (i >= PLAYER_START_ITEMS_MAX) {
					break;
				}

				ptr = strtok(NULL, ",");
				if (ptr) {
					ArbiterConfig::player.startItems[i] = atoll(ptr);
					if (!ArbiterConfig::player.startItems[i]) {
						error_message = "0 is not a valid item id";
						goto error_proc;
					}
				}
			}
		}
		else if (stringStartsWith(line, "player.inventory.start_slots_count"))
		{
			if (!sscanf(line.c_str(), "player.inventory.start_slots_count= %lu", &ArbiterConfig::player.startInventorySlotsCount))
			{
				error_message = "bad start_slots_count max[72] value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.inventory.max_glod"))
		{
			if (!sscanf(line.c_str(), "player.inventory.max_glod= %llu", &ArbiterConfig::player.maxInventoryGold))
			{
				error_message = "bad max_glod max[0xffffffffffffffffu] value!";
				goto error_proc;
			}

			if (ArbiterConfig::player.maxInventoryGold == 0) ArbiterConfig::player.maxInventoryGold = UINT64_MAX;
		}
		else if (stringStartsWith(line, "player.inventory.start_gold"))
		{
			if (!sscanf(line.c_str(), "player.inventory.start_gold = %llu", &ArbiterConfig::player.startInventoryGold))
			{
				error_message = "bad start_gold max[0xffffffffffffffffu] value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.inventory.enable_soulbinding")) {
			if (!sscanf(line.c_str(), "player.inventory.enable_soulbinding = %I32u", &ArbiterConfig::player.soulbindingEnabled))
			{
				error_message = "bad enable_soulbinding max[0xffffffffffffffffu] value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_channel"))
		{
			if (!sscanf(line.c_str(), "player.start_channel = %I32u", &ArbiterConfig::player_start.startChannel))
			{
				error_message = "bad player_start_channel!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_positon"))
		{
			//@TODO remove the z component and get it from the height map
			if (!sscanf(line.c_str(), "player.start_positon= %f %f %f",
				&ArbiterConfig::player_start.startPosition.x,
				&ArbiterConfig::player_start.startPosition.y,
				&ArbiterConfig::player_start.startPosition.z))
			{
				error_message = "bad player.start_position value! [x] [y] [z]";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_heading"))
		{
			if (!sscanf(line.c_str(), "player.start_heading= %hd", &ArbiterConfig::player_start.startHeading))
			{
				error_message = "bad player.start_heading value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_continent"))
		{
			if (!sscanf(line.c_str(), "player.start_continent= %lld", &ArbiterConfig::player_start.startContinent))
			{
				error_message = "bad start_continent value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_area"))
		{
			if (!sscanf(line.c_str(), "player.start_area= %d", &ArbiterConfig::player_start.startArea))
			{
				error_message = "bad start_area value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_channel"))
		{
			if (!sscanf(line.c_str(), "player.start_channel= %d", &ArbiterConfig::player_start.startChannel))
			{
				error_message = "bad start_channel value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_world_map_world_id"))
		{
			if (!sscanf(line.c_str(), "player.start_world_map_world_id= %lld", &ArbiterConfig::player_start.startWorldMapWroldId))
			{
				error_message = "bad start_world_map_world_id value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_world_map_guard_id"))
		{
			if (!sscanf(line.c_str(), "player.start_world_map_guard_id= %lld", &ArbiterConfig::player_start.startWorldMapGuardId))
			{
				error_message = "bad start_world_map_guard_id value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "player.start_world_map_section_id"))
		{
			if (!sscanf(line.c_str(), "player.start_world_map_section_id= %lld", &ArbiterConfig::player_start.startWorldMapSectionId))
			{
				error_message = "bad start_world_map_section_id value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "world_server.listening_port"))
		{
			if (!sscanf(line.c_str(), "world_server.listening_port= %hu", &ArbiterConfig::server.worldServerListenPort))
			{
				error_message = "bad world_server.listening_port value!";
				goto error_proc;
			}
		}
		else if (stringStartsWith(line, "world_server.listening_ip"))
		{
			INT32 ip_part[4];
			int result = sscanf(line.c_str(), "world_server.listening_ip= %d.%d.%d.%d", &ip_part[0], &ip_part[1], &ip_part[2], &ip_part[3]);

			std::string ip_f = std::to_string(ip_part[0]) + '.' + std::to_string(ip_part[1]) + '.' + std::to_string(ip_part[2]) + '.' + std::to_string(ip_part[3]);
			if (result != 4 || ip_f.size() >= 16)
			{
				error_message = "bad world_server.listening_ip value!";
				goto error_proc;
			}

			strcpy_s(ArbiterConfig::server.worldServerListenIp, 16, ip_f.c_str());
		}
		else if (!string_is_null_or_white_space(line) && line != "\n" && line != "\n\r" && line != "\0") {
			error_message = "Unknown config name";
			goto error_proc;
		}
	}

	file.close();

	if (ArbiterConfig::server.worldServerListenPort == 0) {
		ArbiterConfig::server.worldServerListenPort = SERVER_WORLD_LISTENING_PORT;
	}

	return true;

error_proc:
	printf("\nFailed to load config_file. ERROR LINE-NO[%d]\nLINE[%s]\nMESSAGE[%s]\n", lineCount, line.c_str(), error_message.c_str());
	file.close();

	return false;
}

ArbiterConfig::dir_c			ArbiterConfig::dir;
ArbiterConfig::server_c			ArbiterConfig::server;
ArbiterConfig::start_c			ArbiterConfig::player_start;
ArbiterConfig::mysql_c			ArbiterConfig::mysql;
ArbiterConfig::net_c			ArbiterConfig::net;
ArbiterConfig::player_c			ArbiterConfig::player;
ArbiterConfig::chat_c			ArbiterConfig::chat;