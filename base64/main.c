#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "base64.h"

int main() {

    char *str = "hello gogo!! ";

    //计算b64字符串大小，分配该大小空字符串
    char b64[base64_b64_len(str, strlen(str))];
    //b64编码，赋值到b64字符串
    base64_encode(b64, str, strlen(str));

    printf("%s\n", b64);

    //计算原数据大小，分配该大小空字符数组
    char dest[base64_src_len(b64, strlen(b64))];
    //b64解码，赋值到原数据数组
    base64_decode(dest, b64, strlen(b64));

    printf("%s\n", dest);

    printf("%d\n", strcmp(str, dest));

    return 0;
}
