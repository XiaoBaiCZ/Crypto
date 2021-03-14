//
// Created by xiaobai on 2021/3/6.
//

#include "base64.h"
#include <stdlib.h>

//单个原数据长度
#ifdef BASE64_SRC_LEN
#undef BASE64_SRC_LEN
#endif
#define BASE64_SRC_LEN 3

//单个base64单元长度
#ifdef BASE64_UNIT_LEN
#undef BASE64_UNIT_LEN
#endif
#define BASE64_UNIT_LEN 4

//base64转码字符集
const char base64_charset[64] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
        'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
        'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
        'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
        'w', 'x', 'y', 'z', '0', '1', '2', '3',
        '4', '5', '6', '7', '8', '9', '+', '/',
};

//对应关系： b3  b2  b1  b0
//            c2  c1  c0
//base64单元
typedef union {
    struct {
        unsigned int b3 : 6;
        unsigned int b2 : 6;
        unsigned int b1 : 6;
        unsigned int b0 : 6;
    } unit;
    struct {
        unsigned int c2 : 8;
        unsigned int c1 : 8;
        unsigned int c0 : 8;
        unsigned int    : 8;
    } src;
} base64_unit;

//初始化base64_unit
void base64_init_unit(base64_unit *unit, char *src);
//初始化base64_src
void base64_init_src(base64_unit *unit, char *src);
char base64_val2key(char val);

int base64_encode(char **b64, char *src, int size) {
    //补位
    const int fill = (BASE64_SRC_LEN - (size % BASE64_SRC_LEN)) % BASE64_SRC_LEN;
    //base64字符串内存分配
    const int b64_len = (size + fill) / BASE64_SRC_LEN * BASE64_UNIT_LEN;
    *b64 = calloc(b64_len + 1, sizeof(char));
    (*b64)[b64_len] = '\0';
    //循环处理次数
    const int count = (size + fill) / BASE64_SRC_LEN;
    for (int i = 0; i < count; ++i) {
        //根据原数据，构建单个b64_src数据
        base64_unit unit;
        base64_init_src(&unit, src + i * BASE64_SRC_LEN);
        //base64转换并赋值
        const int index = i * BASE64_UNIT_LEN;
        (*b64)[index] = base64_charset[unit.unit.b0];
        (*b64)[index + 1] = base64_charset[unit.unit.b1];
        (*b64)[index + 2] = base64_charset[unit.unit.b2];
        (*b64)[index + 3] = base64_charset[unit.unit.b3];
    }
    //补位赋值=
    if (fill > 0) {
        (*b64)[b64_len - 1] = '=';
    }
    if (fill > 1) {
        (*b64)[b64_len - 2] = '=';
    }
    return b64_len;
}

int base64_decode(char **src, char *b64, int size) {
    //补位
    int fill = 0;
    if (b64[size - 1] == '=') {
        fill++;
    }
    if (b64[size - 2] == '=') {
        fill++;
    }
    //原数据长度
    const int src_len = size / BASE64_UNIT_LEN * BASE64_SRC_LEN;
    *src = calloc(src_len + 1, sizeof(char));
    //循环处理次数
    const int count = size / BASE64_UNIT_LEN;
    for (int i = 0; i < count; ++i) {
        //根据base64单元数据
        base64_unit unit;
        base64_init_unit(&unit, b64 + i * BASE64_UNIT_LEN);
        //base64转换并赋值
        const int index = i * BASE64_SRC_LEN;
        (*src)[index] = unit.src.c0;
        (*src)[index + 1] = unit.src.c1;
        (*src)[index + 2] = unit.src.c2;
    }
    (*src)[src_len - fill] = '\0';
    return src_len - fill;
}

void base64_init_src(base64_unit *unit, char *src) {
    unit->src.c0 = src[0];
    unit->src.c1 = src[1];
    unit->src.c2 = src[2];
}

void base64_init_unit(base64_unit *unit, char *src) {
    unit->unit.b0 = base64_val2key(src[0]);
    unit->unit.b1 = base64_val2key(src[1]);
    unit->unit.b2 = base64_val2key(src[2]);
    unit->unit.b3 = base64_val2key(src[3]);
}

char base64_val2key(char val) {
    if (val == '/') {
        return 63;
    }
    if (val == '+') {
        return 62;
    }
    if (val >= 'a') {
        return val - 'a' + 26;
    }
    if (val >= 'A') {
        return val - 'A';
    }
    return val - '0' + 52;
}
