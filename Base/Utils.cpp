#include "Utils.h"
#include "win32.h"
#include "winsock.h"

#include <sstream>

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
