#ifndef SENDSTREAM_H
#define SENDSTREAM_H

#include "../Base/typeDefs.h"
#include "WorkItems.h"

#include "../Base/win32.h"
#include "../Base/winsock.h"

#define SEND_STREAM_MAX_SIZE 0xffffui16
struct SendStream :Work {
	WSABUF buff;
	ULONG  _pos;
	UID connectionId;

	SendStream() :Work(WorkItemType_SendStream), buff({ 0, nullptr }), _pos(0) { }
	SendStream(UINT16 size) :Work(WorkItemType_SendStream), _pos(0) { buff.buf = new CHAR[size]; buff.len = size; }
	SendStream(UINT8* data, UINT16 size) : Work(WorkItemType_SendStream), buff{ size, (CHAR*)data }, _pos(0) { }
	SendStream(SendStream & other) :Work(WorkItemType_SendStream), buff({ other.buff.len, other.buff.buf }), _pos(0), connectionId(other.connectionId) {
		other.buff.buf = nullptr;
		other.buff.len = 0;
		other._pos = 0;
	}

	virtual ~SendStream() {
		if (buff.buf) {
			delete[] buff.buf;
			buff.buf = nullptr;
		}
	}

	void Resize(ULONG size) {
		if (size <= 0 || buff.len + size > SEND_STREAM_MAX_SIZE) {
			return;
		}

		if (!((UINT8*)buff.buf))
		{
			buff.buf = new CHAR[size];
			buff.len = size;
			memset((void*)((UINT8*)buff.buf), 0, buff.len);
		}
		else
		{
			ULONG newSize = buff.len + size;
			CHAR * newRaw = (CHAR*)realloc((void*)buff.buf, newSize);
			memset((void*)&newRaw[buff.len], 0, size);
			buff.len = newSize;
			buff.buf = newRaw;
		}
	}
	void Write(UINT8 * data, UINT16 size) {
		if (buff.len + size > (UINT16)SEND_STREAM_MAX_SIZE) {
			return;
		}

		LONG allocSzie = size - buff.len + _pos;
		if (allocSzie > 0) {
			Resize((ULONG)allocSzie);
		}

		if (memcpy_s((void*)&((UINT8*)buff.buf)[_pos], size, (const void*)data, size) != 0) {
			return;
		}

		if (allocSzie > 0) {
			_pos = buff.len;
		}
		else {
			_pos += size;
		}
	}
	inline void WriteUInt8(UINT8 data) {
		((UINT8*)buff.buf)[_pos] = data; _pos++;
	}
	inline void WriteInt16(INT16 data) {
		w_16(((UINT8*)buff.buf), data); _pos += 2;
	}
	inline void WriteUInt16(UINT16 data) {
		w_u16(((UINT8*)buff.buf), data); _pos += 2;
	}
	inline void WriteInt32(INT32 data) {
		w_32(((UINT8*)buff.buf), data); _pos += 4;
	}
	inline void WriteUInt32(UINT32 data) {
		w_u32(((UINT8*)buff.buf), data); _pos += 4;
	}
	inline void WriteInt64(INT64 data) {
		w_64(((UINT8*)buff.buf), data); _pos += 8;
	}
	inline void WriteUInt64(UINT64 data) {
		w_u64(((UINT8*)buff.buf), data); _pos += 8;
	}
	inline void WriteFloat(float data) {
		UINT8 * bytes = reinterpret_cast<UINT8*>(&data);
		((UINT8*)buff.buf)[_pos + 0] = bytes[0];
		((UINT8*)buff.buf)[_pos + 1] = bytes[1];
		((UINT8*)buff.buf)[_pos + 2] = bytes[2];
		((UINT8*)buff.buf)[_pos + 3] = bytes[3];

		_pos += 4;
	}
	inline void WriteDouble(double data) {
		UINT8 * bytes = reinterpret_cast<UINT8*>(&data);
		((UINT8*)buff.buf)[_pos + 0] = bytes[0];
		((UINT8*)buff.buf)[_pos + 1] = bytes[1];
		((UINT8*)buff.buf)[_pos + 2] = bytes[2];
		((UINT8*)buff.buf)[_pos + 3] = bytes[3];
		((UINT8*)buff.buf)[_pos + 4] = bytes[4];
		((UINT8*)buff.buf)[_pos + 5] = bytes[5];
		((UINT8*)buff.buf)[_pos + 6] = bytes[6];
		((UINT8*)buff.buf)[_pos + 7] = bytes[7];

		_pos += 8;
	}
	inline void WriteString(const char* str) {
		size_t size = strlen(str);
		LONG delta = buff.len - ((size + 1) * 2);
		if (delta < 0) {
			Resize(-delta);
		}

		register CHAR* ptr = buff.buf + _pos;

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
		w_u16(buff.buf, (UINT16)_pos);
	}

	inline void Release() {
		buff.buf = nullptr;
		buff.len = 0;
		_pos = 0;
	}
};

struct DataStream : SendStream {
	DataStream() : SendStream() {}
	DataStream(UINT16 size) :SendStream(size) {}
	DataStream(UINT8* data, UINT16 size) : SendStream(data, size) {}

	void Read(UINT8 * out_buffer, UINT16 size)
	{
		if (size > buff.len - _pos)
		{
			LONG temp = (buff.len - _pos);

			memcpy_s((void*)out_buffer, size, (const void*)&buff.buf[_pos], temp);
			_pos = temp;

			return;
		}
		memcpy_s((void*)out_buffer, size, (const void*)&buff.buf[_pos], size);
		_pos += size;
	}

	inline INT8 ReadInt8() {
		return buff.buf[_pos++];
	}
	inline UINT8 ReadUInt8()
	{
		return buff.buf[_pos++];
	}
	inline INT16 ReadInt16() {
		INT16 out = r_16(buff.buf + _pos);
		_pos += 2;
		return out;
	}
	inline UINT16 ReadUInt16() {
		UINT16 out = r_u16(buff.buf + _pos);
		_pos += 2;
		return out;
	}
	inline INT32 ReadInt32() {
		INT32 out = r_32(buff.buf + _pos);
		_pos += 4;
		return out;
	}
	inline UINT32 ReadUInt32() {
		UINT32 out = r_u32(buff.buf + _pos);
		_pos += 4;
		return out;
	}
	inline INT64 ReadInt64() {
		INT64 out = r_64(buff.buf + _pos);
		_pos += 8;
		return out;
	}
	inline UINT64 ReadUInt64() {
		UINT64 out = r_u64(buff.buf + _pos);
		_pos += 8;
		return out;
	}
	inline float ReadFloat() {
		float out = r_single(buff.buf + _pos);
		_pos += 4;
		return out;
	}
	inline double ReadDouble() {
		double out = r_double(buff.buf + _pos);
		_pos += 8;
		return out;
	}
};

struct MemoryStream {
	UINT8 * _raw;
	UINT16  _size;
	UINT16  _pos;

	MemoryStream() :_raw(nullptr), _size(0), _pos(0) { }
	MemoryStream(UINT16 size) : _size(size), _pos(0) { _raw = new UINT8[size]; }
	MemoryStream(UINT8* data, UINT16 size) :_raw(data), _size(size), _pos(0) { }

	~MemoryStream() {
		if (_raw) {
			delete[] _raw;
			_raw = nullptr;
		}
	}

	void Resize(UINT16 size) {
		if (size <= 0 || _size + size > SEND_STREAM_MAX_SIZE) {
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
		if (_size + size > (UINT16)SEND_STREAM_MAX_SIZE) {
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
		w_16(_raw, data); _pos += 2;
	}
	inline void WriteUInt16(UINT16 data) {
		w_u16(_raw, data); _pos += 2;
	}
	inline void WriteInt32(INT32 data) {
		w_32(_raw, data); _pos += 4;
	}
	inline void WriteUInt32(UINT32 data) {
		w_u32(_raw, data); _pos += 4;
	}
	inline void WriteInt64(INT64 data) {
		w_64(_raw, data); _pos += 8;
	}
	inline void WriteUInt64(UINT64 data) {
		w_u64(_raw, data); _pos += 8;
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

	inline INT8 ReadInt8() {
		return _raw[_pos++];
	}
	inline UINT8 ReadUInt8()
	{
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
};
#endif
