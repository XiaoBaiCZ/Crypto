#ifndef CRYPTO_RC4_H
#define CRYPTO_RC4_H

#define RC4_S_SIZE 256
#define RC4_KEY_LEN_MAX 256
#define RC4_KEY_LEN_MIN 1

#include"../type/type.h"

typedef struct RC4 {
	uint8 S[RC4_S_SIZE];
} RC4;

//初始化 RC4 S池
void rc4_reset(RC4*, uint8*, int);

//数据源 xor RC4 S池
void rc4_xor(RC4*, uint8*, uint8*, int);

#endif
