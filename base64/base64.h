//
// Created by xiaobai on 2021/3/6.
//

#ifndef BASE64_BASE64_H
#define BASE64_BASE64_H

//计算base64字符串长度
int base64_b64_len(char *src, int size);

//计算原数据长度
int base64_src_len(char *b64, int size);

//base64编码
void base64_encode(char *b64, char *src, int size);

//base64解码
void base64_decode(char *src, char *b64, int size);

#endif //BASE64_BASE64_H
