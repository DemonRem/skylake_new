#ifndef MEMORY_STREAM_H
#define MEMORY_STREAM_H

#include "../Base/typeDefs.h"
#include "WorkItems.h"

#include "../Base/win32.h"
#include "../Base/winsock.h"

#include <istream>

#define DEBUG_PACKETS

#define MEMORY_STREAM_MAX_SIZE 0xffffui16

struct MemoryStream {
	UINT8 * _raw;
	UINT16  _size;
	UINT16  _pos;

	MemoryStream() :_raw(nullptr), _size(0), _pos(0) { }
	MemoryStream(UINT16 size) : _size(size), _pos(0) { _raw = new UINT8[size]; }
	MemoryStream(UINT8* data, UINT16 size) :_raw(data), _size(size), _pos(0) { }
	MemoryStream(std::istream * str)
	{
		str->seekg(0, std::istream::end);
		_size = (UINT16)str->tellg();
		str->seekg(0, std::istream::beg);

		_raw = new UINT8[_size];
		str->read((char*)_raw, _size);
		_pos = 0;
	}

	~MemoryStream() {
		if (_raw) {
			delete[] _raw;
			_raw = nullptr;
		}
	}

	void Resize(UINT16 size) {
		if (size <= 0 || _size + size > MEMORY_STREAM_MAX_SIZE) {
			return;
		}

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
	void Write(UINT8 * data, UINT16 size) {
		if (_size + size > (UINT16)MEMORY_STREAM_MAX_SIZE) {
			return;
		}

		INT16 allocSzie = size - _size + _pos;
		if (allocSzie > 0) {
			Resize(allocSzie);
		}

		if (memcpy_s((void*)&_raw[_pos], size, (const void*)data, size) != 0) {
			return;
		}

		if (allocSzie > 0) {
			_pos = _size;
		}
		else {
			_pos += size;
		}
	}
	inline void WriteUInt8(UINT8 data) {
		_raw[_pos] = data; _pos++;
	}
	inline void WriteInt16(INT16 data) {
		w_16(_raw + _pos, data); _pos += 2;
	}
	inline void WriteUInt16(UINT16 data) {
		w_u16(_raw + _pos, data); _pos += 2;
	}
	inline void WriteInt32(INT32 data) {
		w_32(_raw + _pos, data); _pos += 4;
	}
	inline void WriteUInt32(UINT32 data) {
		w_u32(_raw + _pos, data); _pos += 4;
	}
	inline void WriteInt64(INT64 data) {
		w_64(_raw + _pos, data); _pos += 8;
	}
	inline void WriteUInt64(UINT64 data) {
		w_u64(_raw + _pos, data); _pos += 8;
	}
	inline void WriteFloat(float data) {
		UINT8 * bytes = reinterpret_cast<UINT8*>(&data);
		_raw[_pos + 0] = bytes[0];
		_raw[_pos + 1] = bytes[1];
		_raw[_pos + 2] = bytes[2];
		_raw[_pos + 3] = bytes[3];

		_pos += 4;
	}
	inline void WriteDouble(double data) {
		UINT8 * bytes = reinterpret_cast<UINT8*>(&data);
		_raw[_pos + 0] = bytes[0];
		_raw[_pos + 1] = bytes[1];
		_raw[_pos + 2] = bytes[2];
		_raw[_pos + 3] = bytes[3];
		_raw[_pos + 4] = bytes[4];
		_raw[_pos + 5] = bytes[5];
		_raw[_pos + 6] = bytes[6];
		_raw[_pos + 7] = bytes[7];

		_pos += 8;
	}
	inline void WriteString(const char* str) {
		UINT16 size = (UINT16)strlen(str);
		INT16 delta = _size - ((size + 1) * 2);
		if (delta < 0) {
			Resize(-delta);
		}

		register UINT8* ptr = _raw + _pos;

		for (size_t i = 0; i < size; i++) {
			*ptr = *str;
			ptr++;
			*ptr = 0x00;
			ptr++;

			str++;
		}

		*ptr = 0x00;
		ptr++;
		*ptr = 0x00;

		_pos += (size + 1) * 2;
	}
	inline void WritePos() {
		w_u16(_raw, _pos);
	}
	inline void WriteUID(UID id) {
		w_u64(_raw + _pos, id.id); _pos += 8;
	}

	inline void Read(UINT8 *out, UINT16 size) {
		if (size > _size - _pos)
		{
			INT16 temp = (_size - _pos);

			memcpy_s((void*)out, size, (const void*)&_raw[_pos], temp);
			_pos = _size; //reached end of stream

			return;
		}
		memcpy_s((void*)out, size, (const void*)&_raw[_pos], size);
		_pos += size;
	}
	inline INT8 ReadInt8() {
		return (INT8)_raw[_pos++];
	}
	inline UINT8 ReadUInt8() {
		return _raw[_pos++];
	}
	inline INT16 ReadInt16() {
		INT16 out = r_16(_raw + _pos);
		_pos += 2;
		return out;
	}
	inline UINT16 ReadUInt16() {
		UINT16 out = r_u16(_raw + _pos);
		_pos += 2;
		return out;
	}
	inline INT32 ReadInt32() {
		INT32 out = r_32(_raw + _pos);
		_pos += 4;
		return out;
	}
	inline UINT32 ReadUInt32() {
		UINT32 out = r_u32(_raw + _pos);
		_pos += 4;
		return out;
	}
	inline INT64 ReadInt64() {
		INT64 out = r_64(_raw + _pos);
		_pos += 8;
		return out;
	}
	inline UINT64 ReadUInt64() {
		UINT64 out = r_u64(_raw + _pos);
		_pos += 8;
		return out;
	}
	inline float ReadFloat() {
		float out = r_single(_raw + _pos);
		_pos += 4;
		return out;
	}
	inline double ReadDouble() {
		double out = r_double(_raw + _pos);
		_pos += 8;
		return out;
	}

	inline void Release() {
		_raw = nullptr;
		_size = 0;
		_pos = 0;
	}
	inline void ZeroOut() {
		if (!_size || !_raw) {
			return;
		}

		memset(_raw, 0, sizeof(UINT16) * _size);
	}
	inline void Clear() {
		if (_raw) {
			delete[] _raw;
			_raw = nullptr;
		}

		_size = 0;
		_pos = 0;
	}
	inline INT32 Alloc(UINT16 size) {
		INT32 delta = (_size - _pos) - size;
		if (delta > 0 || !delta) { return 0; }

		Resize((UINT16)-delta);

		return -delta;
	}

	//Is End of Stream
	inline bool IsEOS() const noexcept {
		return _pos == _size;
	}
};
#endif
