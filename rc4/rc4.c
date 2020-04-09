#include "./rc4.h"

void rc4_swap(RC4*, int , int);

void rc4_reset(RC4* rc, uint8* key, int len) {
	if (len < RC4_KEY_LEN_MIN || len > RC4_KEY_LEN_MAX) {
		return;
	}
	int i;
	for (i = 0; i < RC4_S_SIZE; i++) {
		rc->S[i] = (uint8)i;
	}
	uint8 j = 0;
	for (i = 0; i < RC4_S_SIZE; i++) {
		j += rc->S[(uint8)i] + key[i % len];
		rc4_swap(rc, i, j);
	}
}

void rc4_xor(RC4* rc, uint8* src, uint8* dst, int len) {
	uint8 i = 0, j = 0;
	int k;
	for (k = 0; k < len; k++) {
		i += 1;
		j += rc->S[i];
		rc4_swap(rc, i, j);
		dst[k] = src[k] ^ rc->S[(uint8)(rc->S[i] + rc->S[j])];
	}	
}

void rc4_swap(RC4* rc, int i, int j) {
	rc->S[i] = rc->S[i] ^ rc->S[j];
	rc->S[j] = rc->S[i] ^ rc->S[j];
	rc->S[i] = rc->S[i] ^ rc->S[j];
}
