#ifndef SENDSTREAM_H
#define SENDSTREAM_H

#include "../Base/typeDefs.h"
#include "WorkItems.h"

#define SEND_STREAM_MAX_SIZE 0xffffui16
struct SendStream :Work {
	UINT8 * _raw;
	UINT16  _size;
	UINT16  _pos;

	SendStream() :Work(WorkItemType_SendStream), _raw(nullptr), _size(0), _pos(0) { }
	SendStream(UINT16 size) :Work(WorkItemType_SendStream), _size(size), _pos(0) { _raw = new UINT8[size]; }
	SendStream(UINT8* data, UINT16 size) : Work(WorkItemType_SendStream), _raw(data), _size(size), _pos(0) { }

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
};

struct DataStream : SendStream {
	DataStream() : SendStream() {}
	DataStream(UINT16 size) :SendStream(size) {}
	DataStream(UINT8* data, UINT16 size) : SendStream(data, size) {}

	void Read(UINT8 * out_buffer, UINT16 size)
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

	inline INT8 ReadInt8(){
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
		float out = r_double(_raw + _pos);
		_pos += 8;
		return out;
	}
};

#endif
