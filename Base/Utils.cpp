#include "Utils.h"
#include "win32.h"
#include "winsock.h"

#include <sstream>
#include <iostream>

bool file_exists(const char *szPath) {
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

const char *  get_first_machine_ip() {
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	wVersionRequested = MAKEWORD(1, 1);

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
			{
				int nCount = 0;
				return  inet_ntoa(*(
					struct in_addr *)hostinfo->h_addr_list[nCount]);
			}
		}
	return nullptr;
}

INT32 getClassFromTemplateId(INT32 templateId)
{
	return (templateId % 100) - 1;
}

INT32 getRaceFromTemplateId(INT32 templateId)
{
	return (templateId - 10101) / 200;
}

INT32 getGenderFromTemplateId(INT32 templateId)
{
	return ((((templateId - 10101) / 100) * 100) / 500);
}

UINT32 get_skill_base_id(UINT32 skill_id) {
	skill_id /= 10000;
	skill_id *= 10000;
	skill_id += 100;
	return skill_id;
}

void print_packet(UINT8 * data, UINT16 size)
{
	for (int i = 0; i < size; ++i) {
		std::cout << /*std::hex << (int)data[i] << "(" <<*/ data[i];
	}

	std::cout << std::endl;
}

void print_packet_hex(UINT8 * data, UINT16 size)
{
	for (int i = 0; i < size; ++i) {
		printf("%02hhX", data[i]);
	}

	std::cout << std::endl;
}

void wchar_to_little_endian(UINT16 * wchar)
{
	UINT16 * ptr = wchar;
	while (*ptr) {
		*ptr = ntohs(*ptr);
		ptr++;
	}
}

void hwstr_to_str(char * wchar, char * out, size_t maxCount) {
	register size_t i = 0;

	while (wchar[0] || wchar[1]) {
		*out = wchar[1];
		wchar += 2;
		out++;
		i++;

		if (i >= maxCount) {
			return;
		}
	}

	++out[0] = 0x00;
}

void nwstr_to_str(char * wchar, char * out, size_t maxCount) {
	register size_t i = 0;

	while (wchar[0] || wchar[1]) {
		out[0] = wchar[0];
		wchar += 2;
		out++;
		i++;

		if (i >= maxCount) {
			return;
		}
	}

	++out[0] = 0x00;
}
