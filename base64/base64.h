//
// Created by xiaobai on 2021/3/6.
//

#ifndef BASE64_BASE64_H
#define BASE64_BASE64_H

//base64编码
int base64_encode(char **b64, char *src, int size);

//base64解码
int base64_decode(char **src, char *b64, int size);

#endif //BASE64_BASE64_H
