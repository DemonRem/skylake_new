#include "stringUtils.h"
#include <sstream>
#include <iostream>
#include <iomanip>
#include <fstream>


bool stringStartsWith(std::string a, std::string with, bool ignoreWhiteSpaces)
{
	if (a.size() < with.size())
		return false;
	if (with.size() == 0)
		return true;

	std::string result;
	if (ignoreWhiteSpaces)
	{
		for (size_t i = 0; i < a.size(); i++)
		{
			if (a[i] != ' ' && a[i] != '\t')
				result += a[i];
		}
	}
	else result = a;

	for (size_t i = 0; i < with.size(); i++)
	{
		if (result[i] != with[i])
		{
			return false;
		}
	}

	return true;
}

std::string string_split_get_right(std::string line, char c)
{
	std::string out;
	bool other_side = false;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (other_side) out += line[i];

		if (line[i] == c) other_side = true;
	}

	return std::move(out);
}

std::string string_split_get_left(std::string line, char c)
{
	std::string out;
	bool other_side = false;
	for (size_t i = 0; i < line.size(); i++)
	{
		if (!other_side) out += line[i];

		if (line[i] == c) other_side = true;
	}

	return std::move(out);
}

bool string_is_null_or_white_space(std::string & text) {
	if (text == "")
		return true;
	
	for (size_t i = 0; i < text.size(); i++){
		if (text[i] != ' ')
			return false;
	}
	return true;
}

std::vector<int> string_split_skill(std::string skills, char c)
{
	std::vector<int> skillsList;
	std::stringstream ss;
	ss.str(skills);
	std::string skill;
	while (std::getline(ss, skill, ',')) {
		skillsList.push_back(atoi(skill.c_str()));
	}

	return skillsList;
}

std::vector<std::string> string_split(std::string s, char d) {
	std::vector<std::string> out;
	std::string out_s;
	for (auto& c : s) {
		if (c == d) {
			out.push_back(out_s);
			out_s.clear();
			continue;
		}
		else if (c == ' ' || c == '\t')
			continue;

		out_s += c;
	}
	if (out_s != "")
		out.push_back(out_s);

	return out;
}

std::string string_get_containing(std::string s, char d1, char d2) {
	std::string out;
	bool started = false;

	for (auto& t : s) {
		if (t == d1 && !started) {
			started = true;
			continue;
		}
		if (t == d2 && started) {
			break;
		}

		if (started) {
			out += t;
		}
	}

	return out;
}

void dump_packet(UINT8 * data, UINT32 size)
{
	std::stringstream ss;
	ss << std::hex;
	for (UINT32 i = 0; i < size; ++i)
		ss << std::setw(2) << std::setfill('0') << (int)data[i];
	std::cout << ss.str() << std::endl;

	std::ofstream file = std::ofstream("c://users//administrator//desktop//dump.bin");
	file.write((const char*)data, size);
	file.close();
}