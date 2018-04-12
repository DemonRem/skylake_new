#include <iostream>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "../Config/ArbiterConfig.h"
#include "Core.h"

int InitServer() {
	if (!InitArbiterConfig("./data/config.slc")) {
		printf("FAILED TO INITIALIZE CONFIG\n");
		return 1;
	}

	if (InitArbiterCore()) {
		return 2;
	}

	printf("SUCCESSFULLY LOADED THE CONFIG FILE.\n");
	return 0;
}


int main(int argc, char** argv) {
	if (InitServer()) {
		system("pause");
		return 1;
	}


	printf("::SKY_LAKE UP!\n::ACCEPTING CONNECTIONS...\n\n");

#pragma region COMMAND LINE

	std::string cmdLine;
	while (1)
	{
		std::cin >> cmdLine;

		if (cmdLine == "exit")
		{
			break;
		}
		else if (cmdLine == "rlstats")
		{

		}
		else if (cmdLine == "rlskilllearn")
		{

		}
		else if (cmdLine == "rates") {
			//print rates
		}
		else if (cmdLine == "cls") {
			system("cls");
		}

		Sleep(0);
	}
#pragma endregion

	return 0;
}