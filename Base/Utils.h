#ifndef UTILS_H
#define UTILS_H

#include "typeDefs.h"

#define MB_SHOW_ERROR(a) MessageBox(GetConsoleWindow() , a ,"Error", MB_OK | MB_ICONERROR)
#define MB_SHOW_WARNING(a) MessageBox(GetConsoleWindow() , a ,"Error", MB_OK | MB_ICONASTERISK)

#define MB_SHOW_ERROR_T(a,b) MessageBox(GetConsoleWindow() , a ,b, MB_OK | MB_ICONERROR)
#define MB_SHOW_WARNING_T(a,b) MessageBox(GetConsoleWindow() , a ,b, MB_OK | MB_ICONASTERISK)

bool  file_exists(const char*);
const char*  get_first_machine_ip();

INT32	getClassFromTemplateId(INT32 templateId);
INT32	getRaceFromTemplateId(INT32 templateId);
INT32	getGenderFromTemplateId(INT32 templateId);

UINT32  get_skill_base_id(UINT32 skillId);

void print_packet(UINT8 * data, UINT16 size);
void print_packet_hex(UINT8 * data, UINT16 size);
void wchar_to_little_endian(UINT16 *wchar);
void hwstr_to_str(char * wchar, char*out, size_t maxCount);
void nwstr_to_str(char * wchar, char*out, size_t maxCount);

#endif
