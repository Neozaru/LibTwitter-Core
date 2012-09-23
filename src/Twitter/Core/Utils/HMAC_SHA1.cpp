//******************************************************************************
//* HMAC_SHA1.cpp : Implementation of HMAC SHA1 algorithm
//*                 Comfort to RFC 2104
//*
//******************************************************************************
#include "HMAC_SHA1.h"
#include <iostream>
#include <memory>


void CHMAC_SHA1::HMAC_SHA1(BYTE *text, int text_len, BYTE *key, int key_len, BYTE *digest)
{
	memset(SHA1_Key, 0, SHA1_BLOCK_SIZE);

	/* repeated 64 times for values in ipad and opad */
	memset(_ipad, 0x36, sizeof(_ipad));
	memset(_opad, 0x5c, sizeof(_opad));

	/* STEP 1 */
	if (key_len > SHA1_BLOCK_SIZE)
	{
		CSHA1::Reset();
		CSHA1::Update((UINT_8 *)key, key_len);
		CSHA1::Final();

		CSHA1::GetHash((UINT_8 *)SHA1_Key);
	}
	else
		memcpy(SHA1_Key, key, key_len);

	/* STEP 2 */
	for (size_t i=0; i<sizeof(_ipad); i++)
	{
		_ipad[i] ^= SHA1_Key[i];		
	}

	/* STEP 3 */
	memcpy(AppendBuf1, _ipad, sizeof(_ipad));
	memcpy(AppendBuf1 + sizeof(_ipad), text, text_len);

	/* STEP 4 */
	CSHA1::Reset();
	CSHA1::Update((UINT_8 *)AppendBuf1, sizeof(_ipad) + text_len);
	CSHA1::Final();

	CSHA1::GetHash((UINT_8 *)szReport);

	/* STEP 5 */
	for (size_t j=0; j<sizeof(_opad); j++)
	{
		_opad[j] ^= SHA1_Key[j];
	}

	/* STEP 6 */
	memcpy(AppendBuf2, _opad, sizeof(_opad));
	memcpy(AppendBuf2 + sizeof(_opad), szReport, SHA1_DIGEST_LENGTH);

	/*STEP 7 */
	CSHA1::Reset();
	CSHA1::Update((UINT_8 *)AppendBuf2, sizeof(_opad) + SHA1_DIGEST_LENGTH);
	CSHA1::Final();

	CSHA1::GetHash((UINT_8 *)digest);
}
