////////////////////////////////////////////////////////////
/////////////////Writed by Balan Narcis/////////////////////
////////Created to be used with Tera Server [Sky Lake]//////
////////////////////////////////////////////////////////////

//use only for big-edian

#ifndef FILESTREAM_H
#define FILESTREAM_H

#include "typeDefs.h"

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "typeDefs.h"

class FileStream
{

public:
	FileStream();
	FileStream(UINT64 size);
	FileStream(UINT8* data, UINT64 size);
	FileStream(std::istream * str);

	FileStream(FileStream&);
	~FileStream();

	bool				load_from_file(const char*);


	//WRITE_*******************************************************
	void				Resize(UINT64 size);

	void				Write(UINT8* data, UINT64 size);

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



	//READ_********************************************************
	void				Read(UINT8* out_buffer, UINT64 size);

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
	void				Zero();
	UINT64				SetEnd();
	UINT64				SetFront();
	UINT64				NextPos();


	//MEMBER_VAR_**************************************************
	UINT8*				_raw;
	UINT64				_size;
	UINT64				_pos;
};

#endif



