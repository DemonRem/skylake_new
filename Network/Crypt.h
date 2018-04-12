#ifndef CRYPT_H
#define CRYPT_H

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>

#include "../Base/typeDefs.h"
#include "../Base/Random.h"

class Sha_l
{
protected:
	UINT32 LengthLow;
	UINT32 LengthHigh;
	UINT8 MessageBlock[64];
	int MessageBlockIndex;
	int Computed;
	int Corrupted;
	UINT32 CircularShift(int bits, UINT32 word);
	int Result();
	void Input(UINT8 *messageArray, int size);
	void ProcessMessageBlock();
	void PadMessage();

public:
	UINT32 MessageDigest[5];
	Sha_l(UINT8 *src, int size);
};
class CryptorKey
{
public:
	int Size;
	int Pos1;
	int Pos2;
	int MaxPos;
	int Key;
	UINT8 Buffer[58 * 4];
	UINT32 Sum;
	void set(int size, int maxPos);
};
class Cryptor
{
protected:
	int ChangeLen;
	int ChangeData;
	CryptorKey Key[3];

public:
	Cryptor();
	void FillKey(UINT8 *src, UINT8 *buf);
	void GenerateKey(UINT8 *src);
	void ApplyCryptor(UINT8 *buf, int size);
};
class Session
{
protected:
	Cryptor Encryptor;
	Cryptor Decryptor;
	//std::mutex _lockMutex;
public:
	//void Lock();
	//void Unlock();

	UINT8 EncryptKey[128];
	UINT8 DecryptKey[128];
	UINT8 ClientKey1[128];
	UINT8 ClientKey2[128];
	UINT8 ServerKey1[128];
	UINT8 ServerKey2[128];
	Session();

	bool fill_key(UINT8 key[128], UINT8 key_id);
	bool init_session();

	inline void Encrypt(UINT8 *data, int length) {
		Encryptor.ApplyCryptor(data, length);
	}
	inline void Decrypt(UINT8 *data, int length) {
		Decryptor.ApplyCryptor(data, length);
	}

	inline void GenerateSeverKeys() {
		for (UINT16 i = 0; i < 128; i++) {
			ServerKey1[i] = (UINT8)random_range(0, 0xff);
			ServerKey2[i] = (UINT8)random_range(0, 0xff);
		}
	}
	inline void SetClientKey1(UINT8 *key) {
		memcpy_s(ClientKey1, 128, key, 128);
	}
	inline void SetClientKey2(UINT8 *key) {
		memcpy_s(ClientKey2, 128, key, 128);
	}
};

void XorKey(UINT8 *result, UINT8 *key1, int Length1, UINT8 *key2, int Length2);
void ShiftKey(UINT8 *result, UINT8 *src, int n, bool direction = true);

#endif 
