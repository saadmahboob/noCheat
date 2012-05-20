#include <windows.h>

#include "defines.hpp"
#include "crypt.hpp"
#include "key.hpp"
#include "roll.hpp"

NC_LIBEXPORT(VOID) ncEncrypt1(unsigned char* outbuf, int len, unsigned char* key, const int klen)
{
	// 	Get usage key
	unsigned char akey[NC_KEY_MAX_LENGTH];
	ncCreateUsageKey(&akey[0], key, klen, 2);

	// Do NC_ENC_PASSES times:
	int kp;
	for(int pass = 0; pass < NC_ENC_PASSES; pass++)
	{
		for(int i = 0; i < len; i++)
		{
			// Get key position
			kp = (i > 0 ? i % NC_KEY_MAX_LENGTH : 0);
			// Xor
			outbuf[i] ^= akey[kp];
			// Shift left 4
			rol8(&outbuf[i], 4);
			// xor 
			outbuf[i] ^= akey[kp];
			// shift right 5
			ror8(&outbuf[i], 4);
		}
	}
}