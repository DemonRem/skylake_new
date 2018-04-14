#include "Stream.h"

#include <iostream>

Stream::Stream()
{
	_raw = 0;
	_size = 0;
	_pos = 0;
}

Stream::Stream(std::istream * str)
{
	str->seekg(0, std::istream::end);
	_size = (UINT16)str->tellg();
	str->seekg(0, std::istream::beg);

	_raw = new UINT8[_size];
	str->read((char*)_raw, _size);
	_pos = 0;
}

Stream::Stream(UINT16 size)
{
	_size = size;
	_raw = (UINT8*)malloc(size);
	memset((void*)_raw, 0, _size);
	_pos = 0;
}

Stream::Stream(UINT8 * data, UINT16 size)
{
	_size = size;
	_pos = 0;
	_raw = new UINT8[_size];
	if (memcpy_s((void*)_raw, _size, (const void*)data, _size) != 0)
	{
		if (_raw)
		{
			delete[] _raw;
			_raw = 0;

		}
		return;
	}
}

Stream::Stream(UINT8 * data, UINT16 size, const UINT8 santinel)
{
	_raw = data;
	_size = size;
	_pos = 0;
	_isGet = TRUE;
}

Stream::Stream(Stream & d)
{
	_size = _pos = 0;
	_raw = nullptr;

	Resize(d._size);
	Write(d._raw, d._size);
}

Stream::~Stream()
{
	if (!_isGet) {
		if (_raw)
		{
			delete[] _raw;
			_raw = 0;
		}
	}
	else {
		_raw = nullptr;
	}

	_size = 0;
	_pos = 0;
	_isGet = FALSE;
}


//WRITE_*******************************************************
void Stream::Resize(UINT16 size)
{
	if (_isGet) {
		std::cout << "::WORLD_SERVER::CANT RESIZE STREAM WHILE [isGet]\n";
		return;
	}


	if (size <= 0 || _size + size > (UINT16)STREAM_MAX_SIZE)
		return;

	if (!_raw)
	{
		_raw = new UINT8[size];
		_size = size;
		memset((void*)_raw, 0, _size);
	}
	else
	{
		UINT16 newSize = _size + size;
		UINT8 * newRaw = (UINT8*)realloc((void*)_raw, newSize);

		memset((void*)&newRaw[_size], 0, size);
		_size = newSize;
		_raw = newRaw;
	}
}

void Stream::Write(UINT8 * data, UINT16 size) {
	if (_size + size > (UINT16)STREAM_MAX_SIZE) //0xffff because the packets header has only 2 bytes [00 00] for the size
		return;

	INT16 allocSzie = size - _size + _pos;

	if (allocSzie > 0)
		Resize(allocSzie);

	if (memcpy_s((void*)&_raw[_pos], size, (const void*)data, size) != 0) return;


	if (allocSzie > 0)
	{
		_pos = _size;
	}
	else {
		_pos += size;
	}
}

void Stream::WriteString(std::string s, bool reverse)
{
	UINT8 * data = new UINT8[s.size() * 2];
	UINT8 * pos = &data[0];

	for (size_t i = 0; i < s.size(); i++)
	{
		if (!reverse)
		{
			pos[0] = (UINT8)s[i];
			pos[1] = 0x00;
		}
		else
		{
			pos[1] = (UINT8)s[i];
			pos[0] = 0x00;
		}
		pos += 2;
	}

	Write(data, (UINT32)(s.size() * 2));
	WriteInt16(0); // string end
}

void Stream::WriteStringRef(std::string& s, bool reverse)
{
	UINT8 * data = new UINT8[s.size() * 2];
	UINT8 * pos = &data[0];

	for (size_t i = 0; i < s.size(); i++)
	{
		if (!reverse)
		{
			pos[0] = (UINT8)s[i];
			pos[1] = 0x00;
		}
		else
		{
			pos[1] = (UINT8)s[i];
			pos[0] = 0x00;
		}
		pos += 2;
	}

	Write(data, (UINT32)(s.size() * 2));
	WriteInt16(0); // string end
}


void Stream::WriteUInt8(UINT8 val)
{
	Write(&val, 1);
}

void Stream::WriteInt16(INT16 data)
{
	UINT8 shortBytes[2];
	shortBytes[0] = (data & 0xff);
	shortBytes[1] = ((data >> 8) & 0xff);

	Write(shortBytes, 2);
}

void Stream::WriteUInt16(UINT16 val)
{
	UINT8 shortBytes[2];
	shortBytes[0] = (val & 0xff);
	shortBytes[1] = ((val >> 8) & 0xff);
	Write(shortBytes, 2);
}

void Stream::WriteInt32(INT32 data)
{
	UINT8 intBytes[4];
	intBytes[0] = data & 0x000000ff;
	intBytes[1] = (data & 0x0000ff00) >> 8;
	intBytes[2] = (data & 0x00ff0000) >> 16;
	intBytes[3] = (data & 0xff000000) >> 24;

	Write(intBytes, 4);
}

void Stream::WriteUInt32(INT32 data)
{
	UINT8 intBytes[4];
	intBytes[0] = data & 0x000000ff;
	intBytes[1] = (data & 0x0000ff00) >> 8;
	intBytes[2] = (data & 0x00ff0000) >> 16;
	intBytes[3] = (data & 0xff000000) >> 24;

	Write(intBytes, 4);
}

void Stream::WriteInt64(INT64 data)
{
	UINT8 intBytes[8];

	intBytes[0] = ((data >> 0) & 0xff);
	intBytes[1] = ((data >> 8) & 0xff);
	intBytes[2] = ((data >> 16) & 0xff);
	intBytes[3] = ((data >> 24) & 0xff);
	intBytes[4] = ((data >> 32) & 0xff);
	intBytes[5] = ((data >> 40) & 0xff);
	intBytes[6] = ((data >> 48) & 0xff);
	intBytes[7] = ((data >> 56) & 0xff);

	Write(intBytes, 8);
}

void Stream::WriteUInt64(UINT64 data)
{
	UINT8 intBytes[8];

	intBytes[0] = ((data >> 0) & 0xff);
	intBytes[1] = ((data >> 8) & 0xff);
	intBytes[2] = ((data >> 16) & 0xff);
	intBytes[3] = ((data >> 24) & 0xff);
	intBytes[4] = ((data >> 32) & 0xff);
	intBytes[5] = ((data >> 40) & 0xff);
	intBytes[6] = ((data >> 48) & 0xff);
	intBytes[7] = ((data >> 56) & 0xff);

	Write(intBytes, 8);
}

void Stream::WriteFloat(float val)
{
	Write(reinterpret_cast<UINT8*>(&val), 4);
}

void Stream::WriteDouble(double val)
{
	UINT8 * doubleBytes = reinterpret_cast<UINT8*>(&val);
	Write(doubleBytes, 4);
}

void Stream::WritePos(UINT16 s, INT16 offset)
{
	UINT16 temp = _pos;
	_pos = s;
	WriteInt16(temp + offset);
	_pos = temp;
}

void Stream::WriteNext(UINT16 next, UINT16 value)
{
	_pos = next;
	WriteUInt16(value);
	_pos = _size;
}



//READ_********************************************************
void Stream::Read(UINT8 * out_buffer, UINT16 size)
{
	if (size > _size - _pos)
	{
		INT16 temp = (_size - _pos);

		memcpy_s((void*)out_buffer, size, (const void*)&_raw[_pos], temp);
		_pos = temp;

		return;
	}
	memcpy_s((void*)out_buffer, size, (const void*)&_raw[_pos], size);
	_pos += size;
}

char Stream::ReadInt8()
{
	return _raw[_pos++];
}

UINT8 Stream::ReadUInt8()
{
	return _raw[_pos++];
}

INT16 Stream::ReadInt16()
{
	if (_pos > _size - 2)
		return -1;

	INT16 out = (_raw[_pos + 1] << 8) | _raw[_pos];
	_pos += 2;
	return out;
}

UINT16 Stream::ReadUInt16()
{
	if (_pos > _size - 2)
		return -1;

	UINT16 out = (_raw[_pos + 1] << 8) | _raw[_pos];
	_pos += 2;
	return out;
}

INT32 Stream::ReadInt32()
{
	if (_size - 4 < _pos)
		return INT_MAX;

	INT32 out = ((_raw[_pos + 3] << 24) | (_raw[_pos + 2] << 16) | (_raw[_pos + 1] << 8) | _raw[_pos]);
	_pos += 4;

	return out;
}

UINT32 Stream::ReadUInt32()
{
	if (_size - 4 < _pos)
		return INT_MAX;

	UINT32 out = ((_raw[_pos + 3] << 24) | (_raw[_pos + 2] << 16) | (_raw[_pos + 1] << 8) | _raw[_pos]);
	_pos += 4;

	return out;
}

INT64 Stream::ReadInt64()
{
	if (_size < _pos + 8)
		return INT64_MAX;

	INT64 l = 0;
	for (UINT8 i = 0; i < 8; i++) {
		l = l | ((unsigned long long)_raw[_pos + i] << (8 * i));
	}
	_pos += 8;
	return l;
}

UINT64 Stream::ReadUInt64()
{
	if (_size < _pos + 8)
		return INT64_MAX;

	UINT64 l = 0;
	for (UINT8 i = 0; i < 8; i++) {
		l = l | ((unsigned long long)_raw[_pos + i] << (8 * i));
	}
	_pos += 8;
	return l;
}

float Stream::ReadFloat()
{
	if (_size < _pos + 4)
		return FLT_MAX;

	float out = *(float*)(&_raw[_pos]);
	_pos += 4;
	return out;
}

double Stream::ReadDouble()
{
	if (_size < _pos + 4)
		return FLT_MAX;

	double out = *(double*)(&_raw[_pos]);
	_pos += 4;
	return out;
}

std::string Stream::ReadUTF16StringBigEdianToASCII() {

	std::string out;
	INT32 count = 0;
	for (size_t i = _pos; i < _size; i += 2)
	{
		if (_raw[i] == 0x00 && _raw[i + 1] == 0x00)
			break;
		count += 2;
		out.push_back(_raw[i]);
	}
	count += 2;
	_pos += count;

	return out;
}

std::string Stream::ReadASCIIString()
{
	if (_size - _pos < 1)
		return "-1";

	std::string out;
	INT32 kk = 0;
	for (size_t i = _pos; i < _size; i++)
	{
		if (_raw[i] != 0x00)
		{
			if (_raw[i] != '\r' || _raw[i] != '\n')
			{
				out += (char)_raw[i];
			}
			kk++;
		}
		else
			break;
	}
	_pos += kk;
	return out;
}

bool Stream::ReadASCIIStringTo(UINT8 * out, UINT16 max_len)
{
	if (!out)
		return false;

	std::string text = ReadUTF16StringBigEdianToASCII();
	if (text.size() > max_len)
		return false;


	return memcpy(out, text.c_str(), text.size() + 1) ? true : false;
}

std::string Stream::ReadUTF16StringLittleEdianToASCII()
{
	std::string out;
	for (size_t i = _pos; i < _size; i += 2)
	{
		if (_raw[i] == 0x00 && _raw[i + 1] == 0x00)
			break;

		out.push_back(_raw[i + 1]);
	}
	_pos += (UINT16)(out.size() * 2) + 2;

	return out;
}


//MISC_**************************************************
void Stream::Clear()
{
	if (!_isGet) {
		if (_raw)
		{
			delete[] _raw;
			_raw = 0;
		}
	}
	else {
		_raw = nullptr;
	}

	_size = 0;
	_pos = 0;
	_isGet = FALSE;
}

void Stream::Free(){
	_raw = nullptr;
	_pos = _size = 0;
}

void Stream::SetEnd(){
	_pos = _size;
}

void Stream::SetFront(UINT16 offset){
	_pos = 0 + offset;
}

UINT16 Stream::NextPos(){
	UINT16 tempPos = _pos;
	WriteInt16(0);
	return tempPos;
}

