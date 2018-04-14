////////////////////////////////////////////////////////////
/////////////////Writed by Balan Narcis/////////////////////
////////Created to be used with Tera Server [Sky Lake]//////
////////////////////////////////////////////////////////////

//big-edian
#ifndef STREAM_H
#define STREAM_H

#include "../Base/typeDefs.h"
#include "../Base/win32.h"

#include <iostream>
#include <memory>
#include <string>

#ifndef STREAM_MAX_SIZE
#define STREAM_MAX_SIZE 0xffffu //max size of tera packet
#endif

struct Stream
{
	Stream();
	Stream(UINT16 size);
	Stream(UINT8* data, UINT16 size);
	Stream(UINT8* data, UINT16 size,const UINT8 santinel = 0);
	Stream(std::istream * str);

	Stream(Stream&);
	~Stream();


	//WRITE_*******************************************************
	void				Resize(UINT16 size);

	void				Write(UINT8* data, UINT16 size);

	void				WriteStringRef(std::string& s, bool L_ED = false);
	void				WriteString(std::string s, bool L_ED = false);

	void				WriteUInt8(UINT8);

	void				WriteInt16(INT16);
	void				WriteUInt16(UINT16);

	void				WriteInt32(INT32);
	void				WriteUInt32(INT32);

	void				WriteInt64(INT64);
	void				WriteUInt64(UINT64);

	void				WriteFloat(float);
	void				WriteDouble(double);

	void				WritePos(UINT16, INT16 offset = 0);
	void				WriteNext(UINT16 next, UINT16 value);


	//READ_********************************************************
	void				Read(UINT8* out_buffer, UINT16 size);

	char				ReadInt8();
	UINT8				ReadUInt8();

	INT16				ReadInt16();
	UINT16				ReadUInt16();

	INT32				ReadInt32();
	UINT32				ReadUInt32();

	INT64				ReadInt64();
	UINT64				ReadUInt64();

	float				ReadFloat();
	double				ReadDouble();

	std::string			ReadUTF16StringLittleEdianToASCII();
	std::string			ReadUTF16StringBigEdianToASCII();
	std::string			ReadASCIIString();
	bool				ReadASCIIStringTo(UINT8 * out, UINT16 max_len);

	

	
	//MISC_**************************************************
	void				Clear();
	void				Free();
	void				SetEnd();
	void				SetFront(UINT16 offset =0);
	UINT16				NextPos();


	//MEMBER_VAR_**************************************************
	UINT8*				_raw;
	UINT16				_size;
	UINT16				_pos;
	BOOL				_isGet = FALSE;

	char				pad[4];
};
#endif



