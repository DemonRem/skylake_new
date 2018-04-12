#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include "typeDefs.h"
#include <string>
#include <vector>

//@TODO: Refactor

bool stringStartsWith(std::string str, std::string with, bool ignoreWhiteSpaces = true);
std::string string_split_get_right(std::string, char);
std::string string_split_get_left(std::string, char);
bool	string_is_null_or_white_space(std::string&);
std::vector<int> string_split_skill(std::string, char);
std::vector<std::string> string_split(std::string, char);
std::string string_get_containing(std::string, char, char);
void dump_packet(UINT8 * data, UINT32 size);

#endif
