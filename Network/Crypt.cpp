#include "Crypt.h"

#define SHA_DIGEST_LENGTH 20


UINT32 Sha_l::CircularShift(int bits, UINT32 word)
{
	return ((((word) << bits) & 0xFFFFFFFF) | ((word) >> (32 - bits)));
}
int Sha_l::Result()
{
	if (Corrupted != 0)
		return 0;

	if (Computed == 0) {
		PadMessage();
		Computed = 1;
	}

	return 1;
}
void Sha_l::Input(UINT8 *messageArray, int Length)
{
	if (Length == 0)
		return;

	if (Computed > 0 || Corrupted > 0) {
		Corrupted = 1;
		return;
	}

	int counter = 0;
	while (counter < Length && Corrupted == 0) {
		MessageBlock[MessageBlockIndex++] = messageArray[counter];
		LengthLow += 8;
		LengthLow &= 0xFFFFFFFF; //Force it to 32 bits

		if (LengthLow == 0) {
			LengthHigh++;
			LengthHigh &= 0xFFFFFFFF; //Force it to 32 bits
			if (LengthHigh == 0) //Message is too long
				Corrupted = 1;
		}

		if (MessageBlockIndex == 64)
			ProcessMessageBlock();
		counter++;
	}
}
void Sha_l::ProcessMessageBlock()
{
	// Constants defined in SHA
	UINT32 k[4] = {
		0x5A827999,
		0x6ED9EBA1,
		0x8F1BBCDC,
		0xCA62C1D6
	};

	int t; // Loop counter
	UINT32 temp; // Temporary word value
	UINT32 w[80]; // Word sequence
				  // ReSharper disable JoinDeclarationAndInitializer
	UINT32 a, b, c, d, e; // Word buffers
						  // ReSharper restore JoinDeclarationAndInitializer

						  // Initialize the first 16 words in the array W
	for (t = 0; t < 16; t++) {
		w[t] = ((UINT32)MessageBlock[t * 4]) << 24;
		w[t] |= ((UINT32)MessageBlock[t * 4 + 1]) << 16;
		w[t] |= ((UINT32)MessageBlock[t * 4 + 2]) << 8;
		w[t] |= MessageBlock[t * 4 + 3];
	}

	for (t = 16; t < 80; t++)
		w[t] = w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16];

	a = MessageDigest[0];
	b = MessageDigest[1];
	c = MessageDigest[2];
	d = MessageDigest[3];
	e = MessageDigest[4];

	for (t = 0; t < 20; t++) {
		temp = CircularShift(5, a) + ((b & c) | ((~b) & d)) + e + w[t] + k[0];
		temp &= 0xFFFFFFFF;
		e = d;
		d = c;
		c = CircularShift(30, b);
		b = a;
		a = temp;
	}
	for (t = 20; t < 40; t++) {
		temp = CircularShift(5, a) + (b ^ c ^ d) + e + w[t] + k[1];
		temp &= 0xFFFFFFFF;
		e = d;
		d = c;
		c = CircularShift(30, b);
		b = a;
		a = temp;
	}
	for (t = 40; t < 60; t++) {
		temp = CircularShift(5, a) + ((b & c) | (b & d) | (c & d)) + e + w[t] + k[2];
		temp &= 0xFFFFFFFF;
		e = d;
		d = c;
		c = CircularShift(30, b);
		b = a;
		a = temp;
	}
	for (t = 60; t < 80; t++) {
		temp = CircularShift(5, a) + (b ^ c ^ d) + e + w[t] + k[3];
		temp &= 0xFFFFFFFF;
		e = d;
		d = c;
		c = CircularShift(30, b);
		b = a;
		a = temp;
	}
	MessageDigest[0] = (UINT32)((MessageDigest[0] + a) & 0xFFFFFFFF);
	MessageDigest[1] = (UINT32)((MessageDigest[1] + b) & 0xFFFFFFFF);
	MessageDigest[2] = (UINT32)((MessageDigest[2] + c) & 0xFFFFFFFF);
	MessageDigest[3] = (UINT32)((MessageDigest[3] + d) & 0xFFFFFFFF);
	MessageDigest[4] = (UINT32)((MessageDigest[4] + e) & 0xFFFFFFFF);

	MessageBlockIndex = 0;
}
void Sha_l::PadMessage()
{
	/*
	*  Check to see if the current message block is too small to hold
	*  the initial padding bits and length.  If so, we will pad the
	*  block, process it, and then continue padding into a second
	*  block.
	*/
	if (MessageBlockIndex > 55) {
		MessageBlock[MessageBlockIndex++] = 0x80;
		while (MessageBlockIndex < 64)
			MessageBlock[MessageBlockIndex++] = 0;
		ProcessMessageBlock();
		while (MessageBlockIndex < 56)
			MessageBlock[MessageBlockIndex++] = 0;
	}
	else {
		MessageBlock[MessageBlockIndex++] = 0x80;
		while (MessageBlockIndex < 56)
			MessageBlock[MessageBlockIndex++] = 0;
	}

	// Store the message length as the last 8 octets
	MessageBlock[56] = (UINT8)(LengthHigh >> 24);
	MessageBlock[57] = (UINT8)(LengthHigh >> 16);
	MessageBlock[58] = (UINT8)(LengthHigh >> 8);
	MessageBlock[59] = (UINT8)(LengthHigh);
	MessageBlock[60] = (UINT8)(LengthLow >> 24);
	MessageBlock[61] = (UINT8)(LengthLow >> 16);
	MessageBlock[62] = (UINT8)(LengthLow >> 8);
	MessageBlock[63] = (UINT8)(LengthLow);

	ProcessMessageBlock();
}
Sha_l::Sha_l(UINT8 *src, int size)
{
	LengthLow = 0;
	LengthHigh = 0;
	MessageBlockIndex = 0;
	Computed = 0;
	Corrupted = 0;
	memset(MessageBlock, 0, sizeof(UINT8) * 64);
	MessageDigest[0] = 0x67452301;
	MessageDigest[1] = 0xEFCDAB89;
	MessageDigest[2] = 0x98BADCFE;
	MessageDigest[3] = 0x10325476;
	MessageDigest[4] = 0xC3D2E1F0;
	Input(src, size);
	Result();
}

void XorKey(UINT8 *result, UINT8 *key1, int Length1, UINT8 *key2, int Length2)
{
	int Length = Length1 < Length2 ? Length1 : Length2;
	for (int i = 0; i < Length; i++)
		result[i] = (UINT8)(key1[i] ^ key2[i]);
}
void ShiftKey(UINT8 *result, UINT8 *src, int n, bool direction)
{
	int Length = 128;
	for (int i = 0; i < Length; i++)
		if (direction)
			result[(i + n) % Length] = src[i];
		else
			result[i] = src[(i + n) % Length];
}

void CryptorKey::set(int size, int maxPos)
{
	Pos1 = Key = Sum = 0;
	Size = size;
	Pos2 = MaxPos = maxPos;
}

Cryptor::Cryptor()
{
	ChangeLen = 0;
	ChangeData = 0;
	Key[0].set(55, 31);
	Key[1].set(57, 50);
	Key[2].set(58, 39);
}

void Cryptor::FillKey(UINT8 *src, UINT8 *buf)
{
	for (int i = 0; i < 680; i++)
		buf[i] = src[i % 128];
	buf[0] = 128;
}
void Cryptor::GenerateKey(UINT8 *src)
{
	UINT8 buf[680];
	FillKey(src, buf);
	for (int i = 0; i < 680; i += 20)
	{
		Sha_l *sha = new Sha_l(buf, 680);
		memcpy(buf + i, sha->MessageDigest, SHA_DIGEST_LENGTH);
		delete sha;
	}
	memcpy(Key[0].Buffer, buf + 000, 220 - 000);
	memcpy(Key[1].Buffer, buf + 220, 448 - 220);
	memcpy(Key[2].Buffer, buf + 448, 680 - 448);
}
void Cryptor::ApplyCryptor(UINT8 *buffer, int size)
{
	int pre = (size >= ChangeLen) ? ChangeLen : size;
	char *containerInt2;

	if (pre != 0)
	{
		if (pre > 0)
		{
			containerInt2 = (char*)&ChangeData;
			for (int j = 0; j < pre; j++)
				buffer[j] ^= containerInt2[(4 - ChangeLen) + j];
		}
		ChangeLen -= pre;
		size -= pre;
	}

	int offset = pre;
	for (int i = 0; i < size / 4; i++)
	{
		int result = (((Key[0].Key & Key[1].Key) | Key[2].Key) & (Key[0].Key | Key[1].Key));
		for (int j = 0; j < 3; j++)
		{
			if (result == Key[j].Key)
			{
				UINT32 *t1, *t2;
				t1 = (UINT32*)(Key[j].Buffer + Key[j].Pos1 * 4);
				t2 = (UINT32*)(Key[j].Buffer + Key[j].Pos2 * 4);
				UINT32 t3 = *t1 > *t2 ? *t2 : *t1;

				UINT32 sum = *t1 + *t2;
				sum = sum > 0xFFFFFFFFL ? (UINT32)((UINT32)*t1 + (UINT32)*t2) & 0xFFFFFFFFL : sum;
				Key[j].Sum = sum;
				Key[j].Key = t3 <= sum ? 0 : 1;

				Key[j].Pos1 = (Key[j].Pos1 + 1) % Key[j].Size;
				Key[j].Pos2 = (Key[j].Pos2 + 1) % Key[j].Size;
			}
			if (i + 4 <= size) {
				UINT32 *unsBuf = (UINT32*)&buffer[offset + i * 4];
				*unsBuf ^= Key[j].Sum;
			}
			else {
				UINT32 unsBuf;
				memcpy(&unsBuf, buffer + offset + i * 4, 4);
				unsBuf ^= Key[j].Sum;
				memcpy(buffer + offset + i * 4, &unsBuf, 4);
			}
		}
	}

	int remain = size & 3;
	if (remain != 0)
	{
		int result = (((Key[0].Key & Key[1].Key) | Key[2].Key) & (Key[0].Key | Key[1].Key));
		ChangeData = 0;
		for (int j = 0; j < 3; j++)
		{
			if (result == Key[j].Key)
			{
				UINT32 *t1, *t2;
				t1 = (UINT32*)(Key[j].Buffer + Key[j].Pos1 * 4);
				t2 = (UINT32*)(Key[j].Buffer + Key[j].Pos2 * 4);
				UINT32 t3 = *t1 > *t2 ? *t2 : *t1;

				UINT32 sum = *t1 + *t2;
				sum = sum > 0xFFFFFFFFL ? (UINT32)((UINT32)*t1 + (UINT32)*t2) & 0xFFFFFFFFL : sum;
				Key[j].Sum = sum;
				Key[j].Key = t3 <= sum ? 0 : 1;

				Key[j].Pos1 = (Key[j].Pos1 + 1) % Key[j].Size;
				Key[j].Pos2 = (Key[j].Pos2 + 1) % Key[j].Size;
			}
			ChangeData ^= Key[j].Sum;
		}

		containerInt2 = (char*)&ChangeData;
		for (int j = 0; j < remain; j++)
			buffer[((size + pre) - remain) + j] ^= containerInt2[j];

		ChangeLen = 4 - remain;
	}
}

Session::Session()
{
	memset(ClientKey1, 0, 128);
	memset(ClientKey2, 0, 128);
	memset(ServerKey1, 0, 128);
	memset(ServerKey2, 0, 128);
}


//bool Crypt::Session::send_server_key(Connection * c, UINT8 key_no)
//{
//	auto packet = std::make_unique<iocp_send_key>();
//	packet->keyNo = key_no;
//	packet->copy((char*)(key_no == 1 ? ServerKey1 : ServerKey2));
//	packet->connectionIndex = c->id;
//
//	DWORD sentBytes = 0;
//	auto result = WSASend(c->socket, &packet->sendBuff, 1, &sentBytes, 0, (OVERLAPPED*)packet.get(), NULL);
//	if (result == SOCKET_ERROR && WSA_IO_PENDING != (result = WSAGetLastError())) {
//		std::cout << "::ARBITER::FAILED TO SEND KEY NO[" << key_no << "]  WSA-ERR[" << result << "]\n";
//		return false;
//	}
//
//	packet.release();
//	return true;
//}

bool Session::fill_key(UINT8 key[128], UINT8 key_id)
{
	if (key_id == 1) {
		return memcpy(ClientKey1, key, 128) ? true : false;
	}
	else if (key_id == 2 || key_id == 4)
	{
		for (UINT8 i = 0; i < 128; i++)
		{
			ServerKey1[i] = rand() % 0xff;
			ServerKey2[i] = rand() % 0xff;
		}

		return true;
	}
	else if (key_id == 3) {
		return memcpy(ClientKey2, key, 128) ? true : false;
	}

	return false;
}

bool Session::init_session()
{
	UINT8 TmpKey1[128], TmpKey2[128];
	Encryptor = Cryptor();
	Decryptor = Cryptor();


	ShiftKey(TmpKey1, ServerKey1, 67, true);
	XorKey(TmpKey2, TmpKey1, 128, ClientKey1, 128);

	ShiftKey(TmpKey1, ClientKey2, 29, false);
	XorKey(DecryptKey, TmpKey1, 128, TmpKey2, 128);

	Decryptor.GenerateKey(DecryptKey);

	ShiftKey(EncryptKey, ServerKey2, 41, true);
	Decryptor.ApplyCryptor(EncryptKey, 128);

	Encryptor.GenerateKey(EncryptKey);

	return true;
}
