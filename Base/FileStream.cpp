#include "FileStream.h"
#include <fstream>

FileStream::FileStream()
{
	_raw = 0;
	_size = 0;
	_pos = 0;
}

FileStream::FileStream(std::istream * str)
{
	str->seekg(0, std::istream::end);
	_size = (UINT64)str->tellg();
	str->seekg(0, std::istream::beg);

	_raw = new UINT8[_size];
	str->read((char*)_raw, _size);
	_pos = 0;
}

FileStream::FileStream(UINT64 size)
{
	_size = size;
	_raw = (UINT8*)malloc(size);
	memset((void*)_raw, 0, _size);
	_pos = 0;
}

FileStream::FileStream(UINT8 * data, UINT64 size)
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

FileStream::FileStream(FileStream & d)
{
	_size = _pos = 0;
	_raw = nullptr;

	Resize(d._size);
	Write(d._raw, d._size);
}

FileStream::~FileStream()
{
	if (_raw)
	{
		delete[] _raw;
		_raw = 0;
	}
	_size = 0;
	_pos = 0;
}

bool FileStream::load_from_file(const char *file){
	Clear();
	std::ifstream f = std::ifstream(file, std::ios::binary);
	if (!f.is_open())
		return  false;
	if (!f.good()) {
		f.close();
		return  false;
	}

	f.seekg(0, std::fstream::end);
	_size = (UINT64)f.tellg();
	f.seekg(0, std::fstream::beg);

	_raw = new UINT8[_size];
	if (!_raw) {
		f.close();
		return false;
	}

	f.read((char*)_raw, _size);
	f.close();
	return true;
}


//WRITE_*******************************************************
void FileStream::Resize(UINT64 size)
{
	if (size <= 0 || _size + size > UINT64_MAX)
		return;

	if (!_raw)
	{
		_raw = new UINT8[size];
		_size = size;
		memset((void*)_raw, 0, _size);
	}
	else
	{
		UINT64 newSize = _size + size;
		UINT8 * newRaw = (UINT8*)realloc((void*)_raw, newSize);

		memset((void*)&newRaw[_size], 0, size);
		_size = newSize;
		_raw = newRaw;
	}
}

void FileStream::Write(UINT8 * data, UINT64 size)
{
	if (_size + size > UINT64_MAX) //0xffff because the packets header has only 2 bytes [00 00] for the size
		return;

	INT64 allocSzie = size - _size + _pos;

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

void FileStream::WriteString(std::string s, bool reverse)
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

void FileStream::WriteUInt8(UINT8 val)
{
	Write(&val, 1);
}

void FileStream::WriteInt16(INT16 data)
{
	UINT8 shortBytes[2];
	shortBytes[0] = (data & 0xff);
	shortBytes[1] = ((data >> 8) & 0xff);

	Write(shortBytes, 2);
}

void FileStream::WriteUInt16(UINT16 val)
{
	UINT8 shortBytes[2];
	shortBytes[0] = (val & 0xff);
	shortBytes[1] = ((val >> 8) & 0xff);
	Write(shortBytes, 2);
}

void FileStream::WriteInt32(INT32 data)
{
	UINT8 intBytes[4];
	intBytes[0] = data & 0x000000ff;
	intBytes[1] = (data & 0x0000ff00) >> 8;
	intBytes[2] = (data & 0x00ff0000) >> 16;
	intBytes[3] = (data & 0xff000000) >> 24;

	Write(intBytes, 4);
}

void FileStream::WriteUInt32(INT32 data)
{
	UINT8 intBytes[4];
	intBytes[0] = data & 0x000000ff;
	intBytes[1] = (data & 0x0000ff00) >> 8;
	intBytes[2] = (data & 0x00ff0000) >> 16;
	intBytes[3] = (data & 0xff000000) >> 24;

	Write(intBytes, 4);
}

void FileStream::WriteInt64(INT64 data)
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

void FileStream::WriteUInt64(UINT64 data)
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

void FileStream::WriteFloat(float val)
{
	Write(reinterpret_cast<UINT8*>(&val), 4);
}

void FileStream::WriteDouble(double val)
{
	UINT8 * doubleBytes = reinterpret_cast<UINT8*>(&val);
	Write(doubleBytes, 4);
}

void FileStream::WritePos(UINT16 s, INT16 offset)
{
	UINT64 temp = _pos;
	_pos = s;
	WriteUInt16((UINT16)(temp + offset));
	_pos = temp;
}



//READ_********************************************************
void FileStream::Read(UINT8 * out_buffer, UINT64 size)
{
	if (size > _size - _pos)
	{
		INT64 temp = (_size - _pos);

		memcpy_s((void*)out_buffer, size, (const void*)&_raw[_pos], temp);
		_pos = temp;

		return;
	}
	memcpy_s((void*)out_buffer, size, (const void*)&_raw[_pos], size);
	_pos += size;
}

char FileStream::ReadInt8()
{
	return _raw[_pos++];
}

UINT8 FileStream::ReadUInt8()
{
	return _raw[_pos++];
}

INT16 FileStream::ReadInt16()
{
	if (_pos > _size - 2)
		return -1;

	INT16 out = (_raw[_pos + 1] << 8) | _raw[_pos];
	_pos += 2;
	return out;
}

UINT16 FileStream::ReadUInt16()
{
	if (_pos > _size - 2)
		return -1;

	UINT16 out = (_raw[_pos + 1] << 8) | _raw[_pos];
	_pos += 2;
	return out;
}

INT32 FileStream::ReadInt32()
{
	if (_size - 4 < _pos)
		return INT_MAX;

	INT32 out = ((_raw[_pos + 3] << 24) | (_raw[_pos + 2] << 16) | (_raw[_pos + 1] << 8) | _raw[_pos]);
	_pos += 4;

	return out;
}

UINT32 FileStream::ReadUInt32()
{
	if (_size - 4 < _pos)
		return INT_MAX;

	UINT32 out = ((_raw[_pos + 3] << 24) | (_raw[_pos + 2] << 16) | (_raw[_pos + 1] << 8) | _raw[_pos]);
	_pos += 4;

	return out;
}

INT64 FileStream::ReadInt64()
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

UINT64 FileStream::ReadUInt64()
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

float FileStream::ReadFloat()
{
	if (_size < _pos + 4)
		return FLT_MAX;

	float out = *(float*)(&_raw[_pos]);
	_pos += 4;
	return out;
}

double FileStream::ReadDouble()
{
	if (_size < _pos + 4)
		return FLT_MAX;

	double out = *(double*)(&_raw[_pos]);
	_pos += 4;
	return out;
}

std::string FileStream::ReadUTF16StringBigEdianToASCII() {

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

std::string FileStream::ReadASCIIString()
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

bool FileStream::ReadASCIIStringTo(UINT8 * out, UINT16 max_len)
{
	if (!out)
		return false;

	std::string text = ReadUTF16StringBigEdianToASCII();
	if (text.size() > max_len)
		return false;


	return memcpy(out, text.c_str(), text.size() + 1) ? true : false;
}

std::string FileStream::ReadUTF16StringLittleEdianToASCII()
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
void FileStream::Clear()
{
	if (_raw)
	{
		delete[] _raw;
		_raw = 0;
	}
	_size = 0;
	_pos = 0;
}

void FileStream::Zero(){
	memset(_raw, 0, sizeof(UINT8)*_size);
}

UINT64 FileStream::SetEnd()
{
	_pos = _size;
	return _pos;
}

UINT64 FileStream::SetFront()
{
	_pos = 0;
	return 0;

}

UINT64 FileStream::NextPos()
{
	UINT64 tempPos = _pos;
	WriteInt16(0);
	return tempPos;
}

