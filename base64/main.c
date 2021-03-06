#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <base64.h>

int main() {

    char *str = "https://www.baidu.com";

    char *b64;
    //b64编码
    int b64_size = base64_encode(&b64, str, strlen(str));

    printf("%s\nsize: %d\n", b64, b64_size);

    char *dest;
    //b64解码
    int dest_size = base64_decode(&dest, b64, strlen(b64));
    printf("%s\nsize: %d\n", dest, dest_size);

    printf("%d\n", strcmp(str, dest));

    free(b64);
    free(dest);

    return 0;
}
